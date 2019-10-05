void run_lcd_control()
{
  lcd_c_task_time_start = millis();
  lcd_c_task_time_ran++;
  lcd_loop_i = 0;

  if(master_error == true)
  {
    //System Error - screens 500-599
    if(lcd_screen <= 500 || lcd_screen >= 599 )
    {
          if(lcd_loop_i<=lcd_loop_m)
          {
            lcd_loop[lcd_loop_i] = 500;
            lcd_loop_delay[lcd_loop_i]=0+lcd_loop_delay_add;
            lcd_loop_i++;
          }
    }
    if(MCP_online_20==false){
          if(lcd_loop_i<=lcd_loop_m)
          {
            lcd_loop[lcd_loop_i] = 510;
            lcd_loop_delay[lcd_loop_i]=0+lcd_loop_delay_add; 
            lcd_loop_i++;
          }
    }
    
    #if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 2
    if(MCP_enabled_21 == true && MCP_online_21 == false)
    {
          if(lcd_loop_i<=lcd_loop_m){
            lcd_loop[lcd_loop_i] = 511; 
            lcd_loop_delay[lcd_loop_i]=0+lcd_loop_delay_add;
            lcd_loop_i++;
          }
    }
   #endif
    #if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 3
    if(MCP_enabled_22 == true && MCP_online_22 == false)
    {
          if(lcd_loop_i<=lcd_loop_m)
          {
            lcd_loop[lcd_loop_i] = 512;
            lcd_loop_delay[lcd_loop_i]=0+lcd_loop_delay_add;
            lcd_loop_i++;
          }
    }
   #endif
    #if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 4
    if(MCP_enabled_23 == true && MCP_online_23 == false)
    {
          if(lcd_loop_i<=lcd_loop_m)
          {
            lcd_loop[lcd_loop_i] = 513; 
            lcd_loop_delay[lcd_loop_i]=0+lcd_loop_delay_add;
            lcd_loop_i++;
          }
    }
   #endif
  }else if(master_stop){
    //System in standby - screens 400-499
    if(lcd_loop_i<=lcd_loop_m)
    {
      lcd_loop[lcd_loop_i] = 400; 
      lcd_loop_delay[lcd_loop_i]=0+lcd_loop_delay_add;
      lcd_loop_i++;
    }
  }else if(master_blower_on == true && master_blower_off == false){
    //Motor sensor on/running - screens 200-299
      lcd_sensor_i = 0;
      lcd_sensor_flip = true;
      for (int i = 0; i <= 14; i++) {
        if(sensors[i].enable == true && sensors[i].confirmed == true)
        {
          if(lcd_sensor_flip==true)
          {
            if(lcd_loop_i<=lcd_loop_m)
            {
              lcd_loop[lcd_loop_i] = 200; 
              lcd_loop_delay[lcd_loop_i]=2+lcd_loop_delay_add;
              lcd_loop_i++;
            }else{
              break;
            }
            lcd_sensor_flip = false;
          }else{
            lcd_sensor_flip = true;
          }
          if(lcd_sensor_i<=lcd_sensor_m)
          {
            lcd_sensor[lcd_sensor_i]=i+lcd_loop_delay_add;
            lcd_sensor_i++;
          }else{
            break;
          }
        }
      }
  }else if(master_blower_on == false && master_blower_off == false){
    //Motor sensor on/running - screens 200-299
    if(lcd_loop_i<=lcd_loop_m)
    {
      lcd_loop[lcd_loop_i] = 250; 
      lcd_loop_delay[lcd_loop_i]=0+lcd_loop_delay_add;
      lcd_loop_i++;
    }
  }
  #ifdef BLOWER_CONTROL_WIFI
  if(WiFi.status()!= WL_CONNECTED)
  {
    if(lcd_loop_i<=lcd_loop_m)
    {
      lcd_loop[lcd_loop_i] = 540; 
      lcd_loop_delay[lcd_loop_i]=0+lcd_loop_delay_add;
      lcd_loop_i++;
    }
    
  }
  if(ntp_enabled==true)
  {
    if(lcd_loop_i<=lcd_loop_m)
    {
      lcd_loop[lcd_loop_i] = 230; 
      lcd_loop_delay[lcd_loop_i]=0+lcd_loop_delay_add;
      lcd_loop_i++;
    }
    
  }
  #endif
  lcd_c_task_time_stop = millis();
}
void run_lcd_draw()
{
  lcd_d_task_time_start = millis();
  lcd_d_task_time_ran++;
  if(lcd_loop_c>=lcd_loop_i){
    lcd_loop_c = 0;
  }
  if(lcd_loop[lcd_loop_c] == lcd_screen  && lcd_redraw < LCD_REDRAW_TIMES )
  {
      //The screen does not need to be refreshed, increase the re-draw counter and end early
      lcd_redraw++;
  }else{
    lcd_screen = lcd_loop[lcd_loop_c];
    lcd_redraw = 0;
  // see if the LCD screen needs to be updated or force an update every XX times
        switch(lcd_loop[lcd_loop_c])
        {
          case 0:    // your hand is on the sensor
            if(lcd_debug){Serial.println("LCD Screen 0: starting the LCD screen");}
            lcd.clear();
            lcd.print("System booting...");
            lcd.createChar(8, lcd_wifi_none);
            lcd.createChar(4, lcd_exclam_0_0);
            lcd.createChar(5, lcd_exclam_0_1);
            lcd.createChar(6, lcd_exclam_1_0);
            lcd.createChar(7, lcd_exclam_1_1);
            break;
          case 1:
            if(lcd_debug){Serial.println("LCD Screen 1: version number");}
            lcd.clear();
            lcd.print(" Blower Controller  ");
            lcd.setCursor(0, 1);
            lcd.print(BLOWER_VERSION);
          case 2:
            if(lcd_debug){Serial.println("LCD Screen 2: safty info");}
            lcd.clear();
            lcd.write(4);
            lcd.write(5);
            lcd.print("Please read the");
            lcd.setCursor(0, 1);
            lcd.write(6);
            lcd.write(7);
            lcd.print("manual for safety");
            lcd.setCursor(0, 2);
            lcd.print("information");
            lcd.setCursor(18, 2);
            lcd.write(4);
            lcd.write(5);
            lcd.setCursor(18, 3);
            lcd.write(6);
            lcd.write(7);
            break;
          case 3:
            if(lcd_debug){Serial.println("LCD Screen 3:bootup screens done, start logic function");}
            lcd.clear();
            lcd.print("Please wait");
            t_run_lcd_control.enable();
            break;
          case 4:
            if(lcd_debug){Serial.println("LCD Screen 4:blank");}
            lcd.clear();
            lcd.write(4);
            lcd.write(5);
            lcd.print("Please read the");
            lcd.setCursor(0, 1);
            lcd.write(6);
            lcd.write(7);
            lcd.print("manual for safety");
            lcd.setCursor(0, 2);
            lcd.print("information");
            lcd.setCursor(18, 2);
            lcd.write(4);
            lcd.write(5);
            lcd.setCursor(18, 3);
            lcd.write(6);
            lcd.write(7);
            break;
            
          case 200:
          case 201:
          case 202:
          case 203:
            if(lcd_debug){Serial.println("LCD Screen 200/201:system on and running");}
            lcd_screen = 0;  //Force the screen to refresh each loop
            if(lcd_last_sensor_a==0)
            {
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print(">   Motor Online   <");
              lcd.setCursor(0, 1);
              lcd.print("Sensor(s) Active:");
              //lcd_last_sensor_flag_b = false;
              lcd_last_sensor_a = 1;
              //lcd_redraw = LCD_REDRAW_TIMES;
            }else if(lcd_last_sensor_a==1)
            {
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print(" >  Motor Online  < ");
              lcd.setCursor(0, 1);;
              lcd.print("Sensor(s) Active:");
              //lcd_last_sensor_flag_b = false;
              lcd_last_sensor_a = 2;
              //lcd_redraw = LCD_REDRAW_TIMES;
            }else if(lcd_last_sensor_a==2)
            {
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("  > Motor Online <  ");
              lcd.setCursor(0, 1);
              lcd.print("Sensor(s) Active:");
              //lcd_last_sensor_flag_b = false;
              lcd_last_sensor_a = 3;
            }else{
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("   >Motor Online<   ");
              //lcd_last_sensor_flag_b = true;;
              lcd_last_sensor_a = 0;
              lcd.setCursor(0, 1);
              lcd.print("Sensor(s) Active:");
            }
              if(lcd_sensor_c>=lcd_sensor_i)
              {
               lcd_sensor_c = 0; 
              }
              lcd.setCursor(0, 2);
              lcd.print(sensors[lcd_sensor[lcd_sensor_c]].c_name);
              lcd_sensor_c++;
              if(lcd_sensor_c>=lcd_sensor_i)
              {
               lcd_sensor_c = 0; 
              }
              if(lcd_sensor_c != 0)
              {
                lcd.setCursor(0, 3);
                lcd.print(sensors[lcd_sensor[lcd_sensor_c]].c_name);
                lcd_sensor_c++;
              }

            break;
          case 230:
            if(lcd_debug){Serial.println("LCD Screen 250:system in standby");}
            lcd.clear();
            lcd.print("TIME INFO");
            lcd.setCursor(0, 1);
            lcd.print(" Blower Controller  ");
            lcd.setCursor(7, 2);
            lcd.print(BLOWER_VERSION);
            lcd.setCursor(0, 3);
            lcd.print("Press Red to disable");
            break;
          case 250:
            if(lcd_debug){Serial.println("LCD Screen 250:system in standby");}
            lcd.clear();
            lcd.print("<<System in Standby>");
            lcd.setCursor(0, 1);
            lcd.print(" Blower Controller  ");
            lcd.setCursor(7, 2);
            lcd.print(BLOWER_VERSION);
            lcd.setCursor(0, 3);
            lcd.print("Press Red to disable");
            break;
          case 400:
            if(lcd_debug){Serial.println("LCD Screen 400:System on standby Press Green");}
            lcd.clear();
            lcd.print(">System is Disabled<");
            lcd.setCursor(0, 1);
            lcd.print(" Blower Controller  ");
            lcd.setCursor(7, 2);
            lcd.print(BLOWER_VERSION);
            lcd.setCursor(0, 3);
            lcd.print("Press Geeen to Start");
            break;
          case 500:
            if(lcd_debug){Serial.println("LCD Screen 500:System Error");}
            lcd.clear();
            lcd.print(">>>>SYSTEM ERROR<<<<");
            break;
          case 510:
            if(lcd_debug){Serial.println("LCD Screen 510:MCP Offlie Error ar x020");}
            lcd.clear();
            lcd.print(">>>>SYSTEM ERROR<<<<");
            lcd.setCursor(0, 1);
            lcd.print("MCP23017 is offline ");
            lcd.setCursor(0, 2);
            lcd.print("at address 0x20");
            lcd.setCursor(0, 3);
            lcd.print(">>System Disabled<<");
            break;
          case 511:
            if(lcd_debug){Serial.println("LCD Screen 511:MCP Offlie Error ar x021");}
            lcd.clear();
            lcd.print(">>>>SYSTEM ERROR<<<<");
            lcd.setCursor(0, 1);
            lcd.print("MCP23017 is offline ");
            lcd.setCursor(0, 2);
            lcd.print("at address 0x21");
            lcd.setCursor(0, 3);
            lcd.print(">>System Disabled<<");
            break;
          case 512:
            if(lcd_debug){Serial.println("LCD Screen 512:MCP Offlie Error ar x022");}
            lcd.clear();
            lcd.print(">>>>SYSTEM ERROR<<<<");
            lcd.setCursor(0, 1);
            lcd.print("MCP23017 is offline ");
            lcd.setCursor(0, 2);
            lcd.print("at address 0x22");
            lcd.setCursor(0, 3);
            lcd.print(">>System Disabled<<");
            break;
          case 513:
            if(lcd_debug){Serial.println("LCD Screen 512:MCP Offlie Error ar x023");}
            lcd.clear();
            lcd.print(">>>>SYSTEM ERROR<<<<");
            lcd.setCursor(0, 1);
            lcd.print("MCP23017 is offline ");
            lcd.setCursor(0, 2);
            lcd.print("at address 0x23");
            lcd.setCursor(0, 3);
            lcd.print(">>System Disabled<<");
            break;
          case 540:
            if(lcd_debug){Serial.println("LCD Screen 540:WiFi Error");}
            lcd.clear();
              lcd.write(8);
            lcd.print("  WiFi is offline  ");
            lcd.setCursor(0, 1);
            lcd.write(8);
            lcd.print("Please see manual  ");
            lcd.setCursor(0, 2);
            lcd.write(8);
            lcd.print("on how to set up");
            lcd.setCursor(0, 3);
            lcd.write(8);
            lcd.print("or fix WiFi");
            break;
          default:
            lcd_screen = 0;
            lcd_screen_next = 0;
            lcd_screen_delay = 0; 
            
        }
		#ifdef BLOWER_CONTROL_WIFI
    if(lcd_wifi)
    {
        if(WiFi.status()!= WL_CONNECTED)
        {
            if(lcd_last_sensor_flag_wifi)
            {
              lcd.setCursor(19, 0);
              lcd.write(8);
              lcd_last_sensor_flag_wifi = false;
            }else{
              lcd_last_sensor_flag_wifi = true;
            }
        }
    }
		#endif
  }
  //if(lcd_loop_c>=lcd_loop_i || lcd_loop_c>=lcd_loop_m)
  //{
  //  lcd_loop_c = 0;
  //}else{   
  //  if(lcd_loop_delay[lcd_loop_c]=0)
  //  {
      lcd_loop_c++;
  //  }else{
  //    lcd_loop_delay[lcd_loop_c]--;
  //  }
  //}
  lcd_d_task_time_stop = millis();
}
