void run_lcd_control()
{
   if(lcd_debug){Serial.println("LCD Control: Im doing something...");}
          lcd_screen_next = 4;
          lcd_screen_delay = 0; 
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
          t_run_lcd_control.enable();
          break;
        case 4:
          if(lcd_debug){Serial.println("LCD Screen 4:blank");}
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
