void run_chip_dump(){
  Serial.printf("Core Version: %s\n", ESP.getCoreVersion().c_str());
  Serial.printf("CPU Frequency: %u MHz\n", ESP.getCpuFreqMHz());
  Serial.printf("Reset reason: %s\n", ESP.getResetReason().c_str());
  Serial.print("ESP.getBootMode(); ");Serial.println(ESP.getBootMode());
  Serial.print("ESP.getSdkVersion(); ");Serial.println(ESP.getSdkVersion());
  Serial.print("ESP.getBootVersion(); ");Serial.println(ESP.getBootVersion());
  Serial.print("ESP.getChipId(); ");Serial.println(ESP.getChipId());
  Serial.print("ESP.getFlashChipSize(); ");Serial.println(ESP.getFlashChipSize());
  Serial.print("ESP.getFlashChipRealSize(); ");Serial.println(ESP.getFlashChipRealSize());
  Serial.print("ESP.getFlashChipSizeByChipId(); ");Serial.println(ESP.getFlashChipSizeByChipId());
  Serial.print("ESP.getFlashChipId(); ");Serial.println(ESP.getFlashChipId());
  Serial.print("ESP.getFreeHeap(); ");Serial.println(ESP.getFreeHeap());
}



//This funtion will control the logic on weather the blower should be on of off
void run_debug(){
  unsigned long now = millis();
  unsigned long function_called = 0;
  unsigned long function_called_total = 0;
  debug_debug_ran++;
  //Current state of the logic flags, set by the GPIO control
  if(debug_debug){
    run_chip_dump();
    Serial.println ( F("===========================================" ));
    Serial.println ( "Timing:" );
    Serial.println ( F("===========================================" ));
    Serial.print ( F(" - Last debug (this) took " ));
    Serial.print ( debug_debug_time );
    Serial.print ( F(" ms called: ") );
    Serial.print ( debug_debug_ran );
    Serial.print ( F(" times total - ") );
    function_called = debug_debug_ran-debug_debug_times[0];
    Serial.print ( function_called );
    debug_debug_times[0]=debug_debug_ran; 
    Serial.println ( F(" since last seen" ));
    Serial.print ( F(" - I run every  ") );
    Serial.print ( debug_debug_task_time);
    Serial.println ( F(" ms") );
    
    Serial.print ( F(" - System LOOP() MAX took ") );
    Serial.print ( system_loop_max );
    Serial.print ( F(" ms - called " ));
    function_called = system_loop_run-debug_debug_times[1];
    Serial.print ( function_called );
    function_called_total = function_called_total+function_called;
    debug_debug_times[1]=system_loop_run; 
    Serial.println ( F(" since last seen") );

    
    Serial.print ( F(" - Last LCD display takes ") );
    Serial.print ( lcd_d_task_time_max );
    Serial.print ( F(" ms called: ") );
    Serial.print ( lcd_d_task_time_ran );
    Serial.print ( F(" times total - ") );
    function_called = lcd_d_task_time_ran-debug_debug_times[2];
    Serial.print ( function_called );
    function_called_total = function_called_total+function_called;
    debug_debug_times[2]=lcd_d_task_time_ran; 
    Serial.println ( F(" since last seen") );
    
    Serial.print ( F(" - Last LCD Control takes ") );
    Serial.print ( lcd_c_task_time_max );
    Serial.print ( F(" ms called: ") );
    Serial.print ( lcd_c_task_time_ran );
    Serial.print ( F(" times total - " ));
    function_called = lcd_c_task_time_ran-debug_debug_times[3];
    Serial.print ( function_called );
    function_called_total = function_called_total+function_called;
    debug_debug_times[3]=lcd_c_task_time_ran; 
    Serial.println ( F(" since last seen") );
    
    Serial.print ( F(" - Last GPIO takes ") );
    Serial.print ( gpio_task_time_max );
    Serial.print ( F(" ms called: " ));
    Serial.print ( gpio_task_time_ran );
    Serial.print ( F(" times total - ") );
    function_called = gpio_task_time_ran-debug_debug_times[4];
    Serial.print ( function_called );
    function_called_total = function_called_total+function_called;
    debug_debug_times[4]=gpio_task_time_ran; 
    Serial.println ( F(" since last seen") );
    
    Serial.print ( F(" - Last Motor takes ") );
    Serial.print ( motor_task_time_max);
    Serial.print ( F(" ms called: ") );
    Serial.print ( motor_task_time_ran );
    Serial.print ( F(" times total - ") );
    function_called = motor_task_time_ran-debug_debug_times[5];
    Serial.print ( function_called );
    function_called_total = function_called_total+function_called;
    debug_debug_times[5]=motor_task_time_ran; 
    Serial.println ( F(" since last seen") );
    
    Serial.print ( F(" - Last MCP Check takes ") );
    Serial.print ( MCP_task_time_max);
    Serial.print ( F(" ms called: ") );
    Serial.print ( MCP_task_time_ran );
    Serial.print ( F(" times total - ") );
    function_called = MCP_task_time_ran-debug_debug_times[6];
    Serial.print ( function_called );
    function_called_total = function_called_total+function_called;
    debug_debug_times[6]=MCP_task_time_ran; 
    Serial.println ( F(" since last seen") );
    #ifdef BLOWER_CONTROL_WIFI
    Serial.println ( F("===========================================" ));
    Serial.println ( F("WiFi:") );
    Serial.println ( F("===========================================" ));
    Serial.print("MAC ADDRESS: ");
    Serial.println(WiFi.macAddress());
    switch(WiFi.status()){
      case WL_CONNECTED:
       Serial.print ( F("WL_CONNECTED: WiFi connected to '") );
       Serial.print ( WiFi.SSID() );
       Serial.print (F( "' IP: '") );
       Serial.print ( WiFi.localIP());
       Serial.println ( "'" );
      break; 
      case WL_NO_SSID_AVAIL:
       Serial.print ( F("WL_NO_SSID_AVAIL: Failed to find '") );
       Serial.print ( WiFi.SSID() );
       Serial.println ( F("'") );
      break;
      case WL_CONNECT_FAILED:
       Serial.print ( F("WL_CONNECT_FAILED: Filed to connected to '") );
       Serial.print ( WiFi.SSID() );
       Serial.println ( F("'") );
      break;
      case WL_CONNECTION_LOST:
       Serial.print ( F("WL_CONNECTION_LOST: Connection lost to '") );
       Serial.print ( WiFi.SSID() );
       Serial.println ( "'" );
      break;
      case WL_DISCONNECTED:
       Serial.print ( F("WL_DISCONNECTED: Disconnected from '" ));
       Serial.print ( WiFi.SSID() );
       Serial.println (F("'") );
      break;
      default:
       Serial.print ( F("UNKNOWN ISSUE") );
    }
   #endif
    Serial.println ( F("===========================================" ));
    Serial.println ( F("run_blower_control()") );
    Serial.println ( F("===========================================" ));
    Serial.println ( F("Current state of the system:") );
    Serial.print (F(" - Blower Error = ") );
    Serial.println ( master_error );
    Serial.print ( F(" - Master Stop = ") );
    Serial.println ( master_stop );
    Serial.print ( F(" - Blower Off = ") );
    Serial.println ( master_blower_off );
    Serial.print ( F(" - Blower On = ") );
    Serial.println ( master_blower_on );
    Serial.print ( F(" - Blower Function 1 = ") );
    Serial.println ( master_f1_on );
    Serial.print ( F(" - Blower Function 2 = ") );
    Serial.println ( master_f2_on );
    Serial.print ( F(" - motor_logic_state = ") );
    Serial.println ( motor_logic_state );
    Serial.print ( F(" - motor_sent_state = ") );
    Serial.println ( motor_sent_state );
    Serial.print ( F(" - motor_force_state = ") );
    Serial.println ( motor_force_state );
    Serial.print ( F(" - gpio_button_green.current = ") );
    Serial.print ( gpio_button_green.current );
    Serial.print ( F(" - Held for = ") );
    Serial.println ( gpio_button_green.time_total );
    //Serial.println ( gpio_button_green.time_on );
    //Serial.println ( gpio_button_green.time_off );
    //Serial.println ( gpio_button_green.processed_h );
    Serial.println ( F("===========================================" ));
    Serial.print ( F(" - lcd_loop_c = "));
    Serial.println ( lcd_loop_c );
    Serial.print ( F(" - lcd_loop_i = ") );
    Serial.println ( lcd_loop_i );
    Serial.print ( F(" - lcd_loop[lcd_loop_c] = ") );
    Serial.println ( lcd_loop[lcd_loop_c] );
    Serial.print ( F(" - lcd_loop[] = ") );
    for (int i = 0; i <= lcd_loop_i; i++) {
      Serial.print ( lcd_loop[i] );
      Serial.print ( F(" (delay ") );
      Serial.print ( lcd_loop_delay[i] );
      Serial.print ( F("), ") );
    }
      Serial.println ( );
    Serial.println ( F("===========================================" ));
    Serial.print ( F(" - gpio_max_read = ") );
    Serial.println ( gpio_max_read );
    Serial.print ( F(" - MCP_online_20 = ") );
    Serial.println ( MCP_online_20 );
   #if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 2
    Serial.print ( F(" - MCP_online_21 = ") );
    Serial.println ( MCP_online_21 );
    Serial.print ( F(" - MCP_enabled_21 = ") );
    Serial.println ( MCP_enabled_21 );
    #endif
   #if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 3
    Serial.print ( F(" - MCP_online_22 = ") );
    Serial.println ( MCP_online_22 );
    Serial.print ( F(" - MCP_enabled_22 = ") );
    Serial.println ( MCP_enabled_22 );
    #endif
   #if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 4
    Serial.print ( F(" - MCP_online_23 = ") );
    Serial.println ( MCP_online_23 );
    Serial.print ( F(" - MCP_enabled_23 = ") );
    Serial.println ( MCP_enabled_23 );
    #endif
	
    Serial.println ( F("===========================================" ));
    
  
    for (int i = 0; i <= gpio_max_read; i++) {
      if(sensors[i].enable == true)
      {
          if(sensors[i].confirmed )
          {
            if(sensors[i].turn_off )
            {
              Serial.print (F( "!!") );
            }else{
              Serial.print (F( ">>" ));
            }
          }else{
            Serial.print ( F("  " ));
          }
          Serial.print (F(" Sensor: (") );
          Serial.print ( i );
          Serial.print ( F(") -  is N:") );
          Serial.print ( sensors[i].current );
          Serial.print ( F(" L:") );
          Serial.print ( sensors[i].last );
          Serial.print (F( " C:") );
          Serial.print ( sensors[i].confirmed );
          Serial.print ( F("* - '") );
          Serial.print ( sensors[i].c_name );
          Serial.print ( F("'"));
          if(sensors[i].invert == true)
          {
            Serial.print ( F(" (Inverted)" ));
          }
          if(sensors[i].chip_online == false)
          {
            Serial.print (F(" (Read Error)") );
            master_blower_off = true;
          }
          if(sensors[i].processed_l = false)
          {
            Serial.print ( F(" being held high for ") );
            Serial.print (  millis() - sensors[i].time_on );
          }else if(sensors[i].processed_h = false){
            Serial.print ( F(" was held high for ") );
            Serial.print (  sensors[i].time_total );
          }
          if(sensors[i].times < sensors[i].times_required)
          {
            Serial.print ( F(" (Needs Verification of ") );
            Serial.print ( sensors[i].times_required );
            Serial.print ( F("  times @ ") );
            Serial.print ( sensors[i].times );
            Serial.print ( F(")" ));
          }
            Serial.println ( F(" ") );
      }else{
          Serial.print (F( "  ~Sensor: (" ));
          Serial.print ( i );
          Serial.println (F( ") -  is DISABLED ignoring") );
      }
    }
  #ifdef BLOWER_CONTROL_WIFI
  Serial.println ( F("===========================================" ));
  Serial.println ( F("NTP") );  
  Serial.println ( F("===========================================" ));
  printTime(0);  
  Serial.print(F("Next NTP Update: "));
  printTime(tick);
  Serial.println ( F("===========================================") );
  #endif
  run_chip_dump();
  debug_debug_time = millis()-now;
}
}
