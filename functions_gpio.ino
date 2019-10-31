//This function will pull all the MCP's pin status and just return the one pin.  
//Will store the value for additinal calls
uint8_t do_sensor_pull(uint8_t pin, int address)
{
  uint8_t pin_bit=pin%8;
  uint8_t regAddr=(pin<8) ?MCP23017_GPIOA:MCP23017_GPIOB;
  bool need_refresh = ((gpio_last_read+50) < millis());
  
  if(address == 20  && (gpio_last_address != address || need_refresh))
  {
   gpio_last_address = address;
   gpio_last_read = millis();
    if(MCP_online_20 == true)
    {
       gpio_last_reading_A = mcp_20.readGPIO(0);
       gpio_last_reading_B = mcp_20.readGPIO(1);
    }else{
       //Chip Offline, Trigger a low on all sensor inputs       gpio_last_reading_A = 0;
       gpio_last_reading_B = 0b00000001;
    }

  }
  #if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 2
  if(address == 21 && MCP_enabled_21==true && (gpio_last_address != address || need_refresh))
  {
   gpio_last_address = address;
   gpio_last_read = millis();
    if(MCP_online_21 == true)
    {
       gpio_last_reading_A = mcp_21.readGPIO(0);
       gpio_last_reading_B = mcp_21.readGPIO(1);
    }else{
       //Chip Offline, Trigger a low on all sensor inputs       
       gpio_last_reading_A = 0;
       gpio_last_reading_B = 0b00000001;
    }

  }
  #endif  
  if(pin>8)
  {
    return (gpio_last_reading_B >> pin_bit) & 0x1;
  }else{
    return (gpio_last_reading_A >> pin_bit) & 0x1;
  }
}

//This function will check each sensor of the MCP and decide is the system should turn
// the blower on/off, function relays should be on/or and preform some debouncing 
void do_sensor_control(){
  uint16_t ba=0; //all 16 pins (port A and B) into a single 16 bits variable.
  gpio_task_time_start = millis();
  gpio_task_time_ran++;
  master_blower_off = false;
  master_blower_on = false;
  master_f1_on = false;
  master_f2_on = false;
  
  read_button_green();
  read_button_black();
  read_button_blue();
  read_button_yellow();
  
  //Read MCP at address 0x20
  for (int i = 0; i <= gpio_max_read; i++) {
    //Loop tho each pin on the MCP and preform the logic
    if(sensors[i].enable == true)
    {
	  //Controller is setup for dual control boards, must check them all based on gpio_max_read!
	  #if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 2
      //Sensor is enabled let see what it is doing
	  if( i <=15)
	  {
        //sensors[i].current = mcp_20.digitalRead(i);
        sensors[i].current = do_sensor_pull(i,20);
        //delay(5);
	  }else if(i >=16  && i <=31)
	  {
        //sensors[i].current = mcp_21.digitalRead(i-16);
        sensors[i].current = do_sensor_pull(i-16,21);
        //delay(5);
	  }else if(i >=32  && i <=47)
	  {
		//is the system is setup for 3 control boards
		#if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 3
        //sensors[i].current = mcp_22.digitalRead(i-32);
        sensors[i].current = do_sensor_pull(i-32,22);
        //delay(5);
	    #else
		  sensors[i].current = false;
        #endif
	  }else if(i >=48  && i <=63)
	  {
		//is the system is setup for 4 control boards
		#if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 4
        //sensors[i].current = mcp_22.digitalRead(i-48);
        sensors[i].current = do_sensor_pull(i-48,23);
        //delay(5);
	    #else
		  sensors[i].current = false;
        #endif
	  }else {
		  sensors[i].current = false;
      }
	  #else
	  //Controller is setup for single control board
    //sensors[i].current = mcp_20.digitalRead(i);
    sensors[i].current = do_sensor_pull(i,20);
    //delay(5);
    #endif
      //verify that the sensor has not flipped
      if(sensors[i].current != sensors[i].last)
      {
        //the sensor has flip, set the sensor to verification mode
        sensors[i].times = 0;
        sensors[i].last = sensors[i].current;
        sensors[i].processed_h=false;
        sensors[i].processed_l=false;
      }
      
      if(sensors[i].times >= sensors[i].times_required)
      {
        //the sensor has been verified store that value as the confirmed value
        if(sensors[i].invert == true)
        {
          sensors[i].confirmed = !sensors[i].current;
        }else{
          sensors[i].confirmed = sensors[i].current;
        }
      }else{
         //sensors has not been fully verified, increase the trust counter
         sensors[i].times++;
      }
  
      //see if the sensor should be used to turn the blower on and the sensor is in a on state
      if(sensors[i].turn_on == true && sensors[i].confirmed == true)
      {
        master_blower_on = true;
      }
      //see if the sensor should be used to turn the blower off and the sensor is in a on state
      if(sensors[i].turn_off == true && sensors[i].confirmed == true)
      {
        master_blower_off = true;
        if(require_green == true || i == 15)
        {
          //if the system requires the green button press to start the blower 
          //up again from a interlocking sensor or the stop button is pressed
          //trigger a system halt until the green button is pressed
          master_stop = true;
        }
      }
      if(sensors[i].confirmed==true && sensors[i].processed_h == false)
      {
        sensors[i].processed_h=true;
        sensors[i].time_on = millis();
      }else if(sensors[i].confirmed==false && sensors[i].processed_l == false){ 
        sensors[i].processed_l=true;
        sensors[i].time_off = millis();
        sensors[i].time_total = sensors[i].time_off - sensors[i].time_on;
        
      }
      //see if the sensor should be used to turn the Function 1 relay on and the sensor is in a on state
      if(sensors[i].f1 == true && sensors[i].confirmed == true)
      {
        master_f1_on = true;
      }
      //see if the sensor should be used to turn the Function 2 relay on and the sensor is in a on state
      if(sensors[i].f2 == true && sensors[i].confirmed == true)
      {
        master_f2_on = true;
      }
  
    
        if(gpio_debug){
        Serial.print ( "Checking Sensor: (" );
        Serial.print ( i );
        Serial.print ( ") -  is N:" );
        Serial.print ( sensors[i].current );
        Serial.print ( " L:" );
        Serial.print ( sensors[i].last );
        Serial.print ( " C:" );
        Serial.print ( sensors[i].confirmed );
        Serial.print ( "* - '" );
        Serial.print ( sensors[i].c_name );
        Serial.print ( "'" );
        if(sensors[i].invert == true)
        {
          Serial.print ( " (Inverted)" );
        }
        if(sensors[i].chip_online == false)
        {
          Serial.print ( " (Read Error)" );
          master_blower_off = true;
        }
        if(sensors[i].times < sensors[i].times_required)
        {
          Serial.print ( " (Needs Verification of " );
          Serial.print ( sensors[i].times_required );
          Serial.print ( "  times @ " );
          Serial.print ( sensors[i].times );
          Serial.print ( ")" );
        }
          Serial.println ( " " );
        }  
    }else{
        if(gpio_debug){
        Serial.print ( "Sensor: (" );
        Serial.print ( i );
        Serial.println ( ") -  is DISABLED ignoring" );
        }
    }
  }
  gpio_task_time_stop = millis();
}


void read_button_green(){
  int current_read = 0;

  //read the green button
  gpio_button_green.current = !digitalRead(GPIO_START);
  if(gpio_button_green.current != gpio_button_green.last)
  {
    //the sensor has flip, set the sensor to verification mode
    gpio_button_green.times = 0;
    gpio_button_green.processed_h=false;
    gpio_button_green.processed_l=false;
    gpio_button_green.last = gpio_button_green.current;
  }
  if(gpio_button_green.times > gpio_button_green.times_required)
  {
    //the sensor has been verified store that value as the confirmed value
    gpio_button_green.confirmed = gpio_button_green.current;
    if(gpio_button_green.confirmed==true)
    {
      master_stop = false;
    }
    //Figure how long the btton was pressed to be used to "unlock" hidden functions
    if(gpio_button_green.confirmed==true && gpio_button_green.processed_h==false)
    {
      gpio_button_green.processed_h=true;
      gpio_button_green.time_on = millis();
    }else if(gpio_button_green.confirmed==false && gpio_button_green.processed_l==false){
      gpio_button_green.processed_l=true;
      gpio_button_green.time_off = millis();
      gpio_button_green.time_total = gpio_button_green.time_off - gpio_button_green.time_on;
      
    }
  }else{
     //sensos has not been fully verifed, increase the trust conuter
     gpio_button_green.times++;
  }
  if(gpio_debug){
  Serial.print ( "Checking GPIO: N:" );
  Serial.print ( gpio_button_green.current );
  Serial.print ( " L:" );
  Serial.print ( gpio_button_green.last );
  Serial.print ( " C:" );
  Serial.print ( gpio_button_green.confirmed );
  Serial.print ( "* - 'GREEN BUTTON'" );
  if(gpio_button_green.times < gpio_button_green.times_required)
  {
    Serial.print ( " (Needs Nerifaction of " );
    Serial.print ( gpio_button_green.times_required );
    Serial.print ( "  times @ " );
    Serial.print ( gpio_button_green.times );
    Serial.print ( ")" );
  }
  Serial.println ( " " );    
  }  
}



void read_button_blue(){
  int current_read = 0;

  //read the blue button
  gpio_button_blue.current = !digitalRead(GPIO_B1);
  if(gpio_button_blue.current != gpio_button_blue.last)
  {
    //the sensor has flip, set the sensor to verification mode
    gpio_button_blue.times = 0;
    gpio_button_blue.last = gpio_button_blue.current;
  }
  if(gpio_button_blue.times > gpio_button_blue.times_required)
  {
    //the sensor has been verified store that value as the confirmed value
    gpio_button_blue.confirmed = gpio_button_blue.current;
  }else{
     //sensos has not been fully verifed, increase the trust conuter
     gpio_button_blue.times++;
  }
  if(gpio_debug){
  Serial.print ( "Checking GPIO: N:" );
  Serial.print ( gpio_button_blue.current );
  Serial.print ( " L:" );
  Serial.print ( gpio_button_blue.last );
  Serial.print ( " C:" );
  Serial.print ( gpio_button_blue.confirmed );
  Serial.print ( "* - 'BLUE BUTTON'" );
  if(gpio_button_blue.times < gpio_button_blue.times_required)
  {
    Serial.print ( " (Needs Nerifaction of " );
    Serial.print ( gpio_button_blue.times_required );
    Serial.print ( "  times @ " );
    Serial.print ( gpio_button_blue.times );
    Serial.print ( ")" );
  }
  Serial.println ( " " );    
  }  
}

void read_button_black(){
  int current_read = 0;

  //read the black button
  gpio_button_black.current = !digitalRead(GPIO_B2);
  if(gpio_button_black.current != gpio_button_black.last)
  {
    //the sensor has flip, set the sensor to verification mode
    gpio_button_black.times = 0;
    gpio_button_black.last = gpio_button_black.current;
  }
  if(gpio_button_black.times > gpio_button_black.times_required)
  {
    //the sensor has been verified store that value as the confirmed value
    gpio_button_black.confirmed = gpio_button_black.current;
  }else{
     //sensos has not been fully verifed, increase the trust conuter
     gpio_button_black.times++;
  }
  if(gpio_debug){
  Serial.print ( "Checking GPIO: N:" );
  Serial.print ( gpio_button_black.current );
  Serial.print ( " L:" );
  Serial.print ( gpio_button_black.last );
  Serial.print ( " C:" );
  Serial.print ( gpio_button_black.confirmed );
  Serial.print ( "* - 'BLACK BUTTON'" );
  if(gpio_button_black.times < gpio_button_black.times_required)
  {
    Serial.print ( " (Needs Nerifaction of " );
    Serial.print ( gpio_button_black.times_required );
    Serial.print ( "  times @ " );
    Serial.print ( gpio_button_black.times );
    Serial.print ( ")" );
  }
  Serial.println ( " " );    
  }  
}

void read_button_yellow(){
  int current_read = 0;

  //read the yellow button
  gpio_button_yellow.current = !digitalRead(GPIO_START);
  if(gpio_button_yellow.current != gpio_button_yellow.last)
  {
    //the sensor has flip, set the sensor to verification mode
    gpio_button_yellow.times = 0;
    gpio_button_yellow.last = gpio_button_yellow.current;
  }
  if(gpio_button_yellow.times > gpio_button_yellow.times_required)
  {
    //the sensor has been verified store that value as the confirmed value
    gpio_button_yellow.confirmed = gpio_button_yellow.current;
  }else{
     //sensos has not been fully verifed, increase the trust conuter
     gpio_button_yellow.times++;
  }
  if(gpio_debug){
  Serial.print ( "Checking GPIO: N:" );
  Serial.print ( gpio_button_yellow.current );
  Serial.print ( " L:" );
  Serial.print ( gpio_button_yellow.last );
  Serial.print ( " C:" );
  Serial.print ( gpio_button_yellow.confirmed );
  Serial.print ( "* - 'YELLOW BUTTON'" );
  if(gpio_button_yellow.times < gpio_button_yellow.times_required)
  {
    Serial.print ( " (Needs Nerifaction of " );
    Serial.print ( gpio_button_yellow.times_required );
    Serial.print ( "  times @ " );
    Serial.print ( gpio_button_yellow.times );
    Serial.print ( ")" );
  }
  Serial.println ( " " );    
  }  
}
