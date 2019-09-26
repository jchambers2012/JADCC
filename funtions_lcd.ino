void run_lcd_control()
{
  lcd_c_task_time_start = millis();
  lcd_c_task_time_ran++;

  if(master_error == true)
  {
    //System Error - screens 500-599
    if(lcd_screen <= 500 || lcd_screen >= 599 )
    {
          lcd_screen_next = 500;
          lcd_screen_delay = 0; 
    }
    if(MCP_online_20==false){
          lcd_screen_next = 510;
          lcd_screen_delay = 0; 
    }
    
    #if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 2
    if(MCP_enabled_21 == true && MCP_online_21 == false)
    {
          lcd_screen_next = 511;
          lcd_screen_delay = 0; 
    }
   #endif
    #if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 3
    if(MCP_enabled_22 == true && MCP_online_22 == false)
    {
          lcd_screen_next = 512;
          lcd_screen_delay = 0; 
    }
   #endif
    #if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 4
    if(MCP_enabled_23 == true && MCP_online_23 == false)
    {
          lcd_screen_next = 514;
          lcd_screen_delay = 0; 
    }
   #endif
  }else if(master_stop){
    //System in standby - screens 400-499
    if(lcd_screen <= 400 || lcd_screen >= 499 )
    {
          lcd_screen_next = 400;
          lcd_screen_delay = 0; 
    }
  }else if(master_blower_on == true && master_blower_off == false){
    //Motor sensor on/running - screens 200-299
    if(lcd_screen < 200 || lcd_screen > 249 )
    {
          lcd_screen_next = 200;
          lcd_screen_delay = 0; 
    }
  }else if(master_blower_on == false && master_blower_off == false){
    //Motor sensor on/running - screens 200-299
    if(lcd_screen <= 250 || lcd_screen >= 299 )
    {
          lcd_screen_next = 250;
          lcd_screen_delay = 0; 
    }
  }
  lcd_c_task_time_stop = millis();
}
void run_lcd_draw()
{
  lcd_d_task_time_start = millis();
  lcd_d_task_time_ran++;
  // see if the LCD screen needs to be updated or force an update every XX times
  lcd_redraw++;
  if(lcd_screen != lcd_screen_next || lcd_redraw >= 20)
  {
     lcd_redraw = 0; //reset the redraw counter
    if(lcd_screen_delay>0)
    {
      lcd_screen_delay--;
    }else{
      lcd_screen = lcd_screen_next;
        switch(lcd_screen)
        {
          case 0:    // your hand is on the sensor
            if(lcd_debug){Serial.println("LCD Screen 0: starting the LCD screen");}
            lcd.clear();
            lcd.print("System booting...");
            lcd_screen_next = 1;
            break;
          case 1:
            if(lcd_debug){Serial.println("LCD Screen 1: version number");}
            lcd.clear();
            lcd.print(" Blower Controller  ");
            lcd.setCursor(0, 1);
            lcd.print(BLOWER_VERSION);
            lcd_screen_next = 2;
            lcd_screen_delay = 10;
          case 2:
            if(lcd_debug){Serial.println("LCD Screen 2: safty info");}
            //lcd.createChar(1, {  B11111,  B11111,  B01110,  B01110,  B01110,  B00100,  B00000,  B00100});
            lcd.clear();
            //lcd.write(1);
            lcd.print("Please read the   ");
            lcd.setCursor(0, 1);
            //lcd.write(1);
            lcd.print("manual for safety ");
            lcd.setCursor(0, 2);
            //lcd.write(1);
            lcd.print("information       ");
            lcd_screen_next = 3;
            lcd_screen_delay = 10;
            break;
          case 3:
            if(lcd_debug){Serial.println("LCD Screen 3:bootup screens done, start logic function");}
            lcd.clear();
            lcd.print("Please wait");
            lcd_screen_next = 4;
            t_run_lcd_control.enable();
            break;
          case 4:
            if(lcd_debug){Serial.println("LCD Screen 4:blank");}
            lcd.clear();
            //lcd.write(1);
            lcd.print("! Please read the   ");
            lcd.setCursor(0, 1);
            //lcd.write(1);
            lcd.print("! manual for safety ");
            lcd.setCursor(0, 2);
            //lcd.write(1);
            lcd.print("! information       ");
            break;
            
          case 200:
          case 201:
          case 202:
          case 203:
            if(lcd_debug){Serial.println("LCD Screen 200/201:system on and running");}
            if(lcd_screen_next==201)
            {
              lcd.setCursor(0, 0);
              lcd.print(">   Motor Online   <");
              //lcd_last_sensor_flag_b = false;
              lcd_screen_next = 202;
              lcd_redraw = LCD_REDRAW_TIMES;
            }else if(lcd_screen_next==202)
            {
              lcd.setCursor(0, 0);
              lcd.print(" >  Motor Online  < ");
              //lcd_last_sensor_flag_b = false;
              lcd_screen_next = 203;
              lcd_redraw = LCD_REDRAW_TIMES;
            }else if(lcd_screen_next==203)
            {
              lcd.setCursor(0, 0);
              lcd.print("  > Motor Online <  ");
              //lcd_last_sensor_flag_b = false;
              lcd_screen_next = 200;
              lcd_redraw = LCD_REDRAW_TIMES;
            }else{
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("   >Motor Online<   ");
              //lcd_last_sensor_flag_b = true;
              lcd_screen_next = 201;
              lcd_redraw = LCD_REDRAW_TIMES;
              lcd.setCursor(0, 1);
              lcd.print("Sensor(s) Active:");
              
              lcd_last_sensor_flag_a=0;
              for (int i = 0; i <= 14; i++) {
                if(sensors[i].enable == true && sensors[i].confirmed == true)
                {
                  if(lcd_last_sensor_flag_a==0)
                  {
                    lcd.setCursor(0, 2);
                    lcd.print(sensors[i].c_name);
                    lcd_last_sensor_flag_a=1;
                    lcd_last_sensor_a = i;
                  }else if(lcd_last_sensor_flag_a==1){
                    lcd.setCursor(0, 3);
                    lcd.print(sensors[i].c_name);
                    lcd_last_sensor_flag_a=2;
                    lcd_last_sensor_b = i;
                    break;
                  }else{
                    lcd_last_sensor_c++;
                  }
                  if(lcd_debug){
                    Serial.print("name = ");
                    Serial.println(sensors[i].c_name);
                    Serial.print("lcd_last_sensor_flag_a = ");
                    Serial.println(lcd_last_sensor_flag_a);
                    Serial.print("lcd_last_sensor_flag_b = ");
                    Serial.println(lcd_last_sensor_flag_b);
                    Serial.print("lcd_last_sensor_a = ");
                    Serial.println(lcd_last_sensor_a);
                    Serial.print("lcd_last_sensor_b = ");
                    Serial.println(lcd_last_sensor_b);
                    }
                }
              }
            } 
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
          default:
            lcd_screen = 0;
            lcd_screen_next = 0;
            lcd_screen_delay = 0; 
            
        }
    }
  }
  if(lcd_debug){Serial.print("LCD DELAY: ");Serial.println(lcd_screen_delay);}
  if(lcd_debug){Serial.print("lcd_screen: ");Serial.println(lcd_screen);}
  if(lcd_debug){Serial.print("lcd_screen_next: ");Serial.println(lcd_screen_next);}
  if(lcd_debug){Serial.print("lcd_redraw: ");Serial.println(lcd_redraw);}
  if(lcd_debug){Serial.print("(lcd_screen != lcd_screen_next): ");Serial.println(lcd_screen != lcd_screen_next);}
  lcd_d_task_time_stop = millis();
}
