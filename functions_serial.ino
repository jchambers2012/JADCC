
//This funtion will control the logic on weather the blower should be on of off
void run_debug(){
  //Current state of the logic flags, set by the GPIO control
  if(debug_debug){
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
    Serial.print ( " - lcd_screen = " );
    Serial.println ( lcd_screen );
    Serial.print ( " - lcd_screen_next = " );
    Serial.println ( lcd_screen_next );
    Serial.print ( " - lcd_screen_delay = " );
    Serial.println ( lcd_screen_delay );
    Serial.print ( " - lcd_redraw = " );
    Serial.println ( lcd_redraw );
    Serial.print ( " - lcd_last_sensor_flag_b = " );
    Serial.println ( lcd_last_sensor_flag_b );
    Serial.println ( "===========================================" );
    
  
    for (int i = 0; i <= 15; i++) {
      if(sensors[i].enable == true)
      {
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
      }else{
          Serial.print ( "Sensor: (" );
          Serial.print ( i );
          Serial.println ( ") -  is DISABLED ignoring" );
      }
    }
  Serial.println ( "===========================================" );
  Serial.println ( "===========================================" );
  } 
}
