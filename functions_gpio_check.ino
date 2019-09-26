
//This function will check to make sure the MCP chip is responding, if not shutdown the system
void check_MCP(){
   MCP_task_time_start = millis();
   MCP_task_time_ran++;
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
    //I2C bus error, set the system to disable and lockout the system.
      Serial.println ( "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" );
      Serial.println ( "MCP23017 at Address 0x20 is OFFLINE" );
      Serial.println ( "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" );
      master_error = true;
      lcd_error = true;
      MCP_online_20=false;
    }else{
      MCP_online_20=true;
      if(MCP_debug){
      Serial.println ( "===========================================" );
      Serial.println ( "MCP23017 at Address 0x20 is ONLINE" );
      Serial.println ( "===========================================" );
      }

    }
  //This board is a daul control board model
  #if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 2

  //Dual controller board is enabled
    Wire.beginTransmission(0x21);
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
    for (int i = 16; i <= 31; i++) {
      sensors[i].chip_online = online;
    }
    if(online == false)
    {
    //I2C bus error, set the system to disable and lockout the system.
      if(MCP_enabled_21==true)
      {
        Serial.println ( "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" );
        Serial.println ( "MCP23017 at Address 0x21 is OFFLINE" );
        Serial.println ( "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" );
        master_error = true;
        lcd_error = true;
      }
      MCP_online_21=false;
    }else{
      MCP_online_21=true;
      if(MCP_debug){
      Serial.println ( "===========================================" );
      Serial.println ( "MCP23017 at Address 0x21 is ONLINE" );
      Serial.println ( "===========================================" );
      }
    }
  #endif
    
  //This board has 3 control board model
  #if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 3

  //Dual controller board is enabled
    Wire.beginTransmission(0x22);
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
    for (int i = 32; i <= 47; i++) {
      sensors[i].chip_online = online;
    }
    if(online == false)
    {
    //I2C bus error, set the system to disable and lockout the system.
      if(MCP_enabled_22==true)
      {
        Serial.println ( "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" );
        Serial.println ( "MCP23017 at Address 0x22 is OFFLINE" );
        Serial.println ( "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" );
        master_error = true;
        lcd_error = true;
      }
      MCP_online_22=false;
    }else{
      MCP_online_22=true;
      if(MCP_debug){
      Serial.println ( "===========================================" );
      Serial.println ( "MCP23017 at Address 0x22 is ONLINE" );
      Serial.println ( "===========================================" );
      }
    }
  #endif
    
  //This board has 4 control board model
  #if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 4 

  //Dual controller board is enabled
    Wire.beginTransmission(0x23);
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
    for (int i = 48; i <= 63; i++) {
      sensors[i].chip_online = online;
    }
    if(online == false)
    {
    //I2C bus error, set the system to disable and lockout the system.
      if(MCP_enabled_23==true)
      {
        Serial.println ( "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" );
        Serial.println ( "MCP23017 at Address 0x23 is OFFLINE" );
        Serial.println ( "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" );
        master_error = true;
        lcd_error = true;
      }
      MCP_online_23=false;
    }else{
      MCP_online_23=true;
      if(MCP_debug){
      Serial.println ( "===========================================" );
      Serial.println ( "MCP23017 at Address 0x23 is ONLINE" );
      Serial.println ( "===========================================" );
      }
    }
  #endif
    
   MCP_task_time_stop = millis();
}
