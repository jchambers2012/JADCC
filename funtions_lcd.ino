void run_lcd_control()
{

  if(master_error == true)
  {
    //System Error - screens 500-599
    if(lcd_screen <= 500 && lcd_screen >= 599 )
    {
          lcd_screen_next = 500;
          lcd_screen_delay = 0; 
    }
  }else if(master_stop){
    //System in standby - screens 400-499
    if(lcd_screen <= 400 && lcd_screen >= 499 )
    {
          lcd_screen_next = 400;
          lcd_screen_delay = 0; 
    }
  }else if(master_blower_on == true && master_blower_off == false){
    //Motor sensor on/running - screens 200-299
    if(lcd_screen <= 200 && lcd_screen >= 200 )
    {
          lcd_screen_next = 200;
          lcd_screen_delay = 0; 
    }
  }
}
void run_lcd_draw()
{
  if(lcd_screen_delay>0)
  {
    lcd_screen_delay--;
  }else{
    lcd_screen = lcd_screen_next;
      switch(lcd_screen)
      {
        case 0:    // your hand is on the sensor
          if(lcd_debug){Serial.println("LCD Screen 0: starting the LCD screen");}
          lcd.begin();
          lcd.backlight();
          lcd_screen_next = 1;
          break;
        case 1:
          if(lcd_debug){Serial.println("LCD Screen 1: version number");}
          lcd.clear();
          lcd.print(" Blower Controller  ");
          lcd.setCursor(0, 1);
          lcd.print(BLOWER_VERSION);
          lcd_screen_next = 2;
          lcd_screen_delay = 5;
        case 2:
          if(lcd_debug){Serial.println("LCD Screen 2: safty info");}
          //lcd.createChar(1, {  B11111,  B11111,  B01110,  B01110,  B01110,  B00100,  B00000,  B00100});
          lcd.clear();
          lcd.write(1);
          lcd.print("Please read the   ");
          lcd.setCursor(0, 1);
          lcd.write(1);
          lcd.print("manual for safty  ");
          lcd.setCursor(0, 2);
          lcd.write(1);
          lcd.print("information       ");
          lcd_screen_next = 3;
          lcd_screen_delay = 5;
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
          break;
          
        case 200:
          if(lcd_debug){Serial.println("LCD Screen 200:system on and running");}
          lcd.clear();
          break;
        case 400:
          if(lcd_debug){Serial.println("LCD Screen 400:System on standby Press Green");}
          lcd.clear();
          break;
        case 500:
          if(lcd_debug){Serial.println("LCD Screen 500:System Error");}
          lcd.clear();
          break;
        default:
          lcd_screen = 0;
          lcd_screen_next = 0;
          lcd_screen_delay = 0; 
          
      }

  }
  if(lcd_debug){Serial.print("LCD DELAY:");Serial.println(lcd_screen_delay);}
  if(lcd_debug){Serial.print("lcd_screen:");Serial.println(lcd_screen);}
  if(lcd_debug){Serial.print("lcd_screen_next:");Serial.println(lcd_screen_next);}
}
