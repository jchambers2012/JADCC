
//This funtion will control the logic on weather the blower should be on of off
void run_blower_control(){
  motor_task_time_start = millis();
  motor_task_time_ran++;
  //Current state of the logic flags, set by the GPIO control
  if(motor_debug){
  Serial.println ( "===========================================" );
  Serial.println ( "run_blower_control()" );
  Serial.println ( "===========================================" );
  Serial.println ( "Current state of the system:" );
  Serial.print ( " - Blower Error = " );
  Serial.println ( master_error );
  Serial.print ( " - Master Stop = " );
  Serial.println ( master_stop );
  Serial.print ( " - Blower Off = " );
  Serial.println ( master_blower_off );
  Serial.print ( " - Blower On = " );
  Serial.println ( master_blower_on );
  Serial.print ( " - Blower Function 1 = " );
  Serial.println ( master_f1_on );
  Serial.print ( " - Blower Function 2 = " );
  Serial.println ( master_f2_on );
  Serial.print ( " - motor_logic_state = " );
  Serial.println ( motor_logic_state );
  Serial.print ( " - motor_sent_state = " );
  Serial.println ( motor_sent_state );
  Serial.print ( " - motor_force_state = " );
  Serial.println ( motor_force_state );
  Serial.print ( " - gpio_button_green.current = " );
  Serial.println ( gpio_button_green.current );
  Serial.println ( "===========================================" );
  } 

  //Check to see if the motor should be stopped
  if(master_error == true || master_stop == true || master_blower_off  == true)
  {
    //Motor should be stopped
    motor_logic_state = MOTOR_STOP;  // the LOGIC thinks the motor should be stopped, save this state to verify that the stop command has been issued
    if(motor_logic_state != motor_sent_state || motor_force_state == true )
    {
      //motor state mismatch, run the motor control function 
      Serial.println ( "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" );
      Serial.println ( "Setting Motot to STOP" );
      Serial.println ( "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" );
      digitalWrite(RELAY_LED_RED, MOTOR_STOP);
      digitalWrite(RELAY_LED_GREEN, !MOTOR_STOP);
      do_motor_control(MOTOR_STOP);
    }
  }else if(master_blower_on == false && motor_sent_state == MOTOR_STOP)
  {
    motor_logic_state = MOTOR_STOP;  // the LOGIC thinks the motor should be STOPPED, save this state to verify that the stop command has been issued
    if(motor_logic_state != motor_sent_state || motor_force_state == true)
    {
      //motor state mismatch, run the motor control function 
      Serial.println ( "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" );
      Serial.println ( "Setting Motot to STOP - Standby" );
      Serial.println ( "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" );
      digitalWrite(RELAY_LED_RED, !MOTOR_STOP);
      digitalWrite(RELAY_LED_GREEN, MOTOR_STOP);
      do_motor_control(MOTOR_STOP);
    }
  }else if(master_blower_on == true)
  {
    motor_logic_state = MOTOR_START;  // the LOGIC thinks the motor should be STARTED, save this state to verify that the stop command has been issued
    if(motor_logic_state != motor_sent_state || motor_force_state == true)
    {
      //motor state mismatch, run the motor control function 
      Serial.println ( "+++++++++++++++++++++++++++++++++++++++++++" );
      Serial.println ( "Setting Motot to started" );
      Serial.println ( "+++++++++++++++++++++++++++++++++++++++++++" );
      digitalWrite(RELAY_LED_RED, !MOTOR_STOP);
      digitalWrite(RELAY_LED_GREEN, MOTOR_STOP);
      do_motor_control(MOTOR_START);
    }
  }
  motor_force_state = false;
  motor_task_time_stop = millis();
}



//This funtion will prefrom the needed steps to turn on/off the motor
void do_motor_control(bool toState)
{
  //Logic to stop the motor here
  if(motor_ir ==true)
  {
    //prefrom an IR pulse out to motor
    //if a loop or muliple IP pulses are needed to be sent, dont set the state yet so we keep getting called
     motor_sent_state = toState;
  }
  if(motor_rf ==true)
  {
    //prefrom an IR pulse out to motor
    //if a loop or muliple IP pulses are needed to be sent, dont set the state yet so we keep getting called
     motor_sent_state = toState;
     //motorRF.setProtocol(1);
     //motorRF.setPulseLength(175);
     //motorRF.setRepeatTransmit(7);
     //motorRF.send("010101010001010100110011");
  }
  if(motor_f2 ==true)
  {
      digitalWrite(RELAY_F2, toState);    
      motor_sent_state = toState;
  }
  
  Serial.println ( "===========================================" );
  Serial.println ( "do_motor_control()" );
  Serial.print   ( "I did something set it to: " );
  Serial.println ( toState );
  Serial.println ( "===========================================" );
  motor_sent_state = toState;
}
