
//This function will check to make sure the MCP chip is responding, if not shutdown the system
void check_MCP(){
   bool online = true;
    Wire.beginTransmission(0x20);
    switch (Wire.endTransmission()) {
      case 0:
        //success
        if(MCP_debug){Serial.println ( "success 00" );}
        break;
      case 1:
        //data too long to fit in transmit buffer
        if(MCP_debug){Serial.println ( "data too long to fit in transmit buffer 01" );}
        online = false;
        break;
      case 2:
        //received NACK on transmit of address
        if(MCP_debug){Serial.println ( "received NACK on transmit of address 02" );}
        online = false;
        break;
      case 3:
        //received NACK on transmit of data
        if(MCP_debug){Serial.println ( "received NACK on transmit of data 03" );}
        online = false;
        break;
      case 4:
        // error
        online = false;
        if(MCP_debug){Serial.println ( "Error 04" );}
        break;
      default:
        //Unknown error
        online = false;
        if(MCP_debug){Serial.println ( "Unknown Error" );}
    }
    for (int i = 0; i <= 15; i++) {
      sensors[i].chip_online = online;
    }
    if(online == false)
    {
      master_error = true;
      Serial.println ( "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" );
      Serial.println ( "MCP23017 at Address 0x20 is OFFLINE" );
      Serial.println ( "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" );
      lcd_error = true;
      MCP_online_20=false;
      //lcd_error[0][] = "   MCP23017 Error   ";
      //lcd_error[1][] = "See Manual for info ";
    }else{
      master_error = false;
      MCP_online_20=true;
      if(MCP_debug){
      Serial.println ( "===========================================" );
      Serial.println ( "MCP23017 at Address 0x20 is ONLINE" );
      Serial.println ( "===========================================" );
      }

    }
    
}
//This function will check each sensor of the MCP and decide is the system should turn
// the blower on/off, funtion relays should be on/or and prefrom some debouncing 
void do_sensor_control(){
  master_blower_off = false;
  master_blower_on = false;
  master_f1_on = false;
  master_f2_on = false;
  int current_read = 0;
  
  read_button_green();
  read_button_black();
  read_button_blue();
  read_button_yellow();
  
  for (int i = 0; i <= 15; i++) {
    //Loop tho each pin on the MCP and prefrom the logic
    if(sensors[i].enable == true)
    {
      //Sensor is enabled let see what it is doing
      current_read = mcp.digitalRead(i);
      sensors[i].current = current_read;
      //verify that the senosr has no flipped
      if(sensors[i].current != sensors[i].last)
      {
        //the sensor has flip, set the sensor to verification mode
        sensors[i].times = 0;
        sensors[i].last = sensors[i].current;
      }
      
      if(sensors[i].times > sensors[i].times_required)
      {
        //the sensor has been verified store that value as the confirmed value
        if(sensors[i].invert == true)
        {
          sensors[i].confirmed = !sensors[i].current;
        }else{
          sensors[i].confirmed = sensors[i].current;
        }
      }else{
         //sensos has not been fully verifed, increase the trust conuter
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
      //see if the sensor should be used to turn the Funtion 1 relay on and the sensor is in a on state
      if(sensors[i].f1 == true && sensors[i].confirmed == true)
      {
        master_f1_on = true;
      }
      //see if the sensor should be used to turn the Funtion 2 relay on and the sensor is in a on state
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
