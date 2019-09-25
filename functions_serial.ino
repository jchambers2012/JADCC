
//This funtion will control the logic on weather the blower should be on of off
void run_debug(){
  unsigned long now = millis();
  debug_debug_ran++;
  //Current state of the logic flags, set by the GPIO control
  if(debug_debug){
    Serial.println ( "===========================================" );
    Serial.println ( "Timing:" );
    Serial.println ( "===========================================" );
    Serial.print ( " - System LOOP() took " );
    Serial.print ( system_loop_stop-system_loop_start );
    Serial.println ( " ms" );
    
    Serial.print ( " - Last debug (this) took " );
    Serial.print ( debug_debug_time );
    Serial.print ( " ms called: " );
    Serial.print ( debug_debug_ran );
    Serial.println ( " times" );
    
    Serial.print ( " - Last LCD display took " );
    Serial.print ( lcd_d_task_time_stop-lcd_d_task_time_start );
    Serial.print ( " ms called: " );
    Serial.print ( lcd_d_task_time_ran );
    Serial.println ( " times" );
    
    Serial.print ( " - Last LCD Control took " );
    Serial.print ( lcd_c_task_time_stop-lcd_c_task_time_start );
    Serial.print ( " ms called: " );
    Serial.print ( lcd_c_task_time_ran );
    Serial.println ( " times" );
    
    Serial.print ( " - Last GPIO took " );
    Serial.print ( gpio_task_time_stop-gpio_task_time_start );
    Serial.print ( " ms called: " );
    Serial.print ( gpio_task_time_ran );
    Serial.println ( " times" );
    
    Serial.print ( " - Last Motor took " );
    Serial.print ( motor_task_time_stop-motor_task_time_start );
    Serial.print ( " ms called: " );
    Serial.print ( motor_task_time_ran );
    Serial.println ( " times" );
    Serial.println ( "===========================================" );
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
    Serial.print ( " - gpio_max_read = " );
    Serial.println ( gpio_max_read );
    Serial.print ( " - MCP_online_20 = " );
    Serial.println ( MCP_online_20 );
   #if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 2
    Serial.print ( " - MCP_online_21 = " );
    Serial.println ( MCP_online_21 );
    Serial.print ( " - MCP_enabled_21 = " );
    Serial.println ( MCP_enabled_21 );
    #endif
   #if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 3
    Serial.print ( " - MCP_online_22 = " );
    Serial.println ( MCP_online_22 );
    Serial.print ( " - MCP_enabled_22 = " );
    Serial.println ( MCP_enabled_22 );
    #endif
   #if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 4
    Serial.print ( " - MCP_online_23 = " );
    Serial.println ( MCP_online_23 );
    Serial.print ( " - MCP_enabled_23 = " );
    Serial.println ( MCP_enabled_23 );
    #endif
	
    Serial.println ( "===========================================" );
    
  
    for (int i = 0; i <= gpio_max_read; i++) {
      if(sensors[i].enable == true)
      {
          if(sensors[i].confirmed )
          {
            if(sensors[i].turn_off )
            {
              Serial.print ( "--" );
            }else{
              Serial.print ( ">>" );
            }
          }else{
            Serial.print ( "  " );
          }
          Serial.print ( " Sensor: (" );
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
          Serial.print ( "  Sensor: (" );
          Serial.print ( i );
          Serial.println ( ") -  is DISABLED ignoring" );
      }
    }
  Serial.println ( "===========================================" );
  Serial.println ( "===========================================" );
  } 
  debug_debug_time = millis()-now;
}
