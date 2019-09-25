//This function will check each sensor of the MCP and decide is the system should turn
// the blower on/off, function relays should be on/or and preform some debouncing 
void do_sensor_control(){
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
        sensors[i].current = mcp_20.digitalRead(i);
	  }else if(i >=16  && i <=31)
	  {
        sensors[i].current = mcp_21.digitalRead(i-16);
	  }else if(i >=32  && i <=47)
	  {
		//is the system is setup for 3 control boards
		#if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 3
        sensors[i].current = mcp_22.digitalRead(i-32);
	    #else
		  sensors[i].current = false;
        #endif
	  }else if(i >=48  && i <=63)
	  {
		//is the system is setup for 4 control boards
		#if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 4
        sensors[i].current = mcp_22.digitalRead(i-48);
	    #else
		  sensors[i].current = false;
        #endif
	  }else {
		  sensors[i].current = false;
      }
	  #else
	    //Controller is setup for single control board
        sensors[i].current = mcp_20.digitalRead(i);
      #endif
      //verify that the sensor has not flipped
      if(sensors[i].current != sensors[i].last)
      {
        //the sensor has flip, set the sensor to verification mode
        sensors[i].times = 0;
        sensors[i].last = sensors[i].current;
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
