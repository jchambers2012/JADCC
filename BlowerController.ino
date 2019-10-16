#include "include.h"
;;;;;;;;;;;;;;;;;;;;
Adafruit_MCP23017 mcp_20; //Zones 1-3 Sensors INDEX 0-15

#if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 2
  Adafruit_MCP23017 mcp_21; //Zones 4-6 Sensors INDEX 16-31
#endif
#if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 3
  Adafruit_MCP23017 mcp_22; //Zones 4-6 Sensors INDEX 16-31
#endif
#if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 4
  Adafruit_MCP23017 mcp_23; //Zones 4-6 Sensors INDEX 16-31
#endif

#ifdef BLOWER_CONTROL_WIFI
  ESP8266WebServer server(80);
  //holds the current upload
  File fsUploadFile;
#endif

LiquidCrystal_I2C lcd(0x27, 20, 4);

Task t_gpioControl(gpio_task_time, TASK_FOREVER, &do_sensor_control);

Task t_run_blower_control(motor_task_time, TASK_FOREVER, &run_blower_control);

Task t_check_MCP(MCP_task_time, TASK_FOREVER, &check_MCP);

Task t_run_lcd_control(lcd_c_task_time, TASK_FOREVER, &run_lcd_control);

Task t_run_lcd_draw(lcd_d_task_time, TASK_FOREVER, &run_lcd_draw);

Task t_run_debug(debug_debug_task_time, TASK_FOREVER, &run_debug);

void setup() {
  ESP.wdtEnable(WDTO_8S);
  pinMode(RELAY_F1, OUTPUT);
  digitalWrite(RELAY_F1, false);  
  pinMode(RELAY_F2, OUTPUT);
  digitalWrite(RELAY_F2, false);  
  pinMode(RELAY_LED_RED, OUTPUT);
  digitalWrite(RELAY_LED_RED, false);  
  pinMode(RELAY_LED_GREEN, OUTPUT);
  digitalWrite(RELAY_LED_GREEN, false);  
  pinMode(GPIO_IR, OUTPUT);
  digitalWrite(GPIO_IR, false);  
  pinMode(GPIO_START, INPUT_PULLUP);
  Wire.begin();
  lcd.begin();
  lcd.backlight();
  lcd.home();
  lcd.print("System Starting...");
  Serial.begin ( 115200 );
  Serial.print ( F("Blower Controller Version: ") );
  Serial.println ( BLOWER_VERSION );
  Serial.println ( F("Created By Jason Chambers") );
  Serial.println ( F("Warning - This device does not contain any Emergency Control or Fail-Safe Functions. This device should not be used as a life safety system.") );
  run_chip_dump();
  #ifdef BLOWER_CONTROL_WIFI
  lcd.clear();
  lcd.print("Starting WiFi");
  wdt_disable();
  wifi_setup();

  wdt_enable(WDTO_8S);
  if(WiFi.SSID().length()>0)
  {
    //if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");
    lcd.setCursor(0, 2);
    lcd.print("WiFi connected");
    lcd.setCursor(0, 3);
    lcd.print("                    ");
    lcd.setCursor(0, 3);
    Serial.println("1");
    lcd.print(WiFi.localIP());
    Serial.println("2");
    Serial.println(WiFi.localIP());
    Serial.println("3");
    //delay(2000);
    lcd_wifi = true;
    wifi_enabled = true;
    Serial.println("WiFi setup done)");
  }else{
    //if you get here you have connected to the WiFi
    Serial.println("WiFi not setup");
    lcd.clear();
    lcd.print("WiFi not set up");
    delay(2000);
    lcd_wifi = false;
    wifi_enabled = false;
  }
  #endif

  ESP.wdtFeed();
  #ifdef BLOWERCONTROLLER_DEBUG
  Serial.print ( "Zones Enabled: " );
  Serial.println ( sensors_zone_num );
  #endif

  #ifdef BLOWERCONTROLLER_DEBUG
  Serial.println ( "Setting up MCP23017" );
  #endif
  mcp_20.begin(0);      // use default address 0 (0x20)
  for (int i = 0; i <= 15; i++) {
    mcp_20.pinMode(i, INPUT);
  }
  
  #ifdef BLOWERCONTROLLER_DEBUG
  Serial.println ( "DONE Setting up MCP23017" );
  #endif

  #ifdef BLOWERCONTROLLER_DEBUG
  Serial.println("++++++++++++++++++++++++++++++++++++++++");
  Serial.println("Scheduler INIT");
  #endif

  ESP.wdtFeed();
  #ifdef BLOWERCONTROLLER_DEBUG
  Serial.println("Initialized Critical scheduler");
  #endif
  ts.init();

  //Run the hardware MCP checker
  ts.addTask(t_check_MCP);
  t_check_MCP.enable();
  #ifdef BLOWERCONTROLLER_DEBUG
  Serial.println("Started t_check_MCP task");
  #endif

  //Run the GPIO control logic
  ts.addTask(t_gpioControl);
  t_gpioControl.enable();
  #ifdef BLOWERCONTROLLER_DEBUG
  Serial.println("Started t_gpioControl task");
  #endif

  //Run the blower control logic
  ts.addTask(t_run_blower_control);
  t_run_blower_control.enable();
  #ifdef BLOWERCONTROLLER_DEBUG
  Serial.println("Started t_run_blower_control task");
  #endif

  ESP.wdtFeed();
  #ifdef BLOWERCONTROLLER_DEBUG
  Serial.println("Initialized normal scheduler");
  #endif
  //ts.init();
  //ts.setHighPriorityScheduler(&cts);

  
  //Run the Debugger
  ts.addTask(t_run_debug);
  t_run_debug.enable();
  #ifdef BLOWERCONTROLLER_DEBUG
  Serial.println("Started t_run_lcd_draw task");
  #endif

  //Run the hardware LCD functions checker
  ts.addTask(t_run_lcd_draw);
  t_run_lcd_draw.enable();
  #ifdef BLOWERCONTROLLER_DEBUG
  Serial.println("Started t_run_lcd_draw task");
  #endif

  //Run the hardware LCD functions checker
  ts.addTask(t_run_lcd_control);
  #ifdef BLOWERCONTROLLER_DEBUG
  Serial.println("Started t_run_lcd_control task");
  #endif

  #ifdef BLOWERCONTROLLER_DEBUG
  Serial.println("++++++++++++++++++++++++++++++++++++++++");
  #endif
  ESP.wdtFeed();
  
  //Set the default names for each sensor. The full name is staored in variable.h
  //This will be overritten by the config.json file (if found)
  sensors[0].c_name[8]='1';sensors[0].c_name[11]='1';
  sensors[1].c_name[8]='1';sensors[1].c_name[11]='2';
  sensors[2].c_name[8]='1';sensors[2].c_name[11]='3';
  sensors[3].c_name[8]='1';sensors[3].c_name[11]='4';
  sensors[4].c_name[8]='1';sensors[4].c_name[11]='5';
  sensors[5].c_name[8]='2';sensors[5].c_name[11]='1';
  sensors[6].c_name[8]='2';sensors[6].c_name[11]='2';
  sensors[7].c_name[8]='2';sensors[7].c_name[11]='3';
  sensors[8].c_name[8]='2';sensors[8].c_name[11]='4';
  sensors[9].c_name[8]='2';sensors[9].c_name[11]='5';
  sensors[10].c_name[8]='3';sensors[10].c_name[11]='1';
  sensors[11].c_name[8]='3';sensors[11].c_name[11]='2';
  sensors[12].c_name[8]='3';sensors[12].c_name[11]='3';
  sensors[13].c_name[8]='3';sensors[13].c_name[11]='4';
  sensors[14].c_name[8]='3';sensors[14].c_name[11]='5';
  #if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 2
  sensors[16].c_name[8]='4';sensors[16].c_name[11]='1';
  sensors[17].c_name[8]='4';sensors[17].c_name[11]='2';
  sensors[18].c_name[8]='4';sensors[18].c_name[11]='3';
  sensors[19].c_name[8]='4';sensors[19].c_name[11]='4';
  sensors[20].c_name[8]='4';sensors[20].c_name[11]='5';
  sensors[21].c_name[8]='5';sensors[21].c_name[11]='1';
  sensors[22].c_name[8]='5';sensors[22].c_name[11]='2';
  sensors[23].c_name[8]='5';sensors[23].c_name[11]='3';
  sensors[24].c_name[8]='5';sensors[24].c_name[11]='4';
  sensors[25].c_name[8]='5';sensors[25].c_name[11]='5';
  sensors[26].c_name[8]='6';sensors[26].c_name[11]='1';
  sensors[27].c_name[8]='6';sensors[27].c_name[11]='2';
  sensors[28].c_name[8]='6';sensors[28].c_name[11]='3';
  sensors[29].c_name[8]='6';sensors[29].c_name[11]='4';
  sensors[30].c_name[8]='6';sensors[30].c_name[11]='5';
  #endif

  //clean FS, for testing
  //wdt_disable();
  //SPIFFS.format();
  //wdt_enable(BLOWER_WDT);
  //read configuration from FS json
  Serial.println("Mounting FS...");
  isFSMounted = SPIFFS.begin();
    if (!isFSMounted) {
    Serial.println("Formatting file system...");
    wdt_disable();
    SPIFFS.format();
    wdt_enable(WDTO_8S);
  }
  ESP.wdtFeed();
  if (isFSMounted) {
    Serial.println("Mounted file system");
    if (SPIFFS.exists("/config.json")) {
      //file exists, reading and loading
      Serial.println("reading config file");
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile) {
        Serial.println("opened config file");
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        json.printTo(Serial);
        if (json.success()) {
          ESP.wdtFeed();
          Serial.println("\nparsed json");

          //strcpy(mqtt_server, json["mqtt_server"]);
          //strcpy(mqtt_port, json["mqtt_port"]);
          //strcpy(blynk_token, json["blynk_token"]);

        } else {
          Serial.println("failed to load json config, defaults will be used");
        }
        configFile.close();
      }
    } else {
      Serial.println("config.json missing, defaults will be used");
    }
  } else {
    Serial.println("failed to mount FS, defaults will be used");
  }


  ESP.wdtFeed();
  #ifdef BLOWER_CONTROL_WIFI
  if(wifi_enabled == true && ntp_enabled == true)
  {
    
    Serial.println("Starting NTP");
    setup_ntp();
    Serial.println("DONE NTP");
  }
  #endif
  //This controller is complied for 2 controller
  #if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 2
    if(MCP_enabled_21==true)
	{
	  //Dual controller board is enabled
      mcp_21.begin(1);      // use default address 1 (0x21)
      for (int i = 0; i <= 15; i++) {
        mcp_21.pinMode(i, INPUT);
      }
	  gpio_max_read = 31;  //Incease the number of sensor that should be read by the system
	}
  #endif
  //This controller is complied for 3 controller
  #if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 3
    if(MCP_enabled_22==true)
	{
	  //Dual controller board is enabled
      mcp_22.begin(1);      // use default address 1 (0x21)
      for (int i = 0; i <= 15; i++) {
        mcp_22.pinMode(i, INPUT);
      }
	  gpio_max_read = 31;  //Incease the number of sensor that should be read by the system
	}
  #endif
  //This controller is complied for 4 controller
  #if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 4
    if(MCP_enabled_23==true)
	{
	  //Dual controller board is enabled
      mcp_23.begin(1);      // use default address 1 (0x21)
      for (int i = 0; i <= 15; i++) {
        mcp_23.pinMode(i, INPUT);
      }
	  gpio_max_read = 31;  //Incease the number of sensor that should be read by the system
	}
  #endif
  
  ESP.wdtFeed();
  if(motor_rf)
  {
    Serial.println("Starting the RF TX");
    motorRF.enableTransmit(GPIO_IR);
    Serial.println("DONE: Starting the RF TX");
  }
  //Force Sensor 15 to be a stop switch but allow other config settings.
  //This can not be overwritten and remain enabled and to disable the motor.
  //Hard coded logic in do_sensor_control() will also disable the motor if
  //this sensor is triggered.
  
  //strncpy(sensors[15].c_name, "Stop Button", sizeof(sensors[15].c_name));
  sensors[15].turn_on = false;
  sensors[15].turn_off = true;
  sensors[15].enable = true;
  //sensors[15].invert = false;
  #if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 2
  //Force Sensor 31 to be a stop switch but allow other config settings.
  //This can not be overwritten and remain enabled and to disable the motor.
  //Hard coded logic in do_sensor_control() will also disable the motor if
  //this sensor is triggered.
  
  //strncpy(sensors[31].c_name, "Stop Button", sizeof(sensors[31].c_name));
  sensors[31].turn_on = false;
  sensors[31].turn_off = true;
  sensors[31].enable = true;
  #endif
  master_stop = true;  //force the system into a stop until the start button has been pressed on first boot
  


  //TEST Objects until I can get around to getting config.json working

  sensors[4].enable = false;
  //sensors[13].turn_on = false;
  //sensors[13].turn_off = true;
  sensors[13].f1 = true;
  //master_stop = false;

  ESP.wdtFeed();
  #ifdef BLOWER_CONTROL_WIFI
  web_setup();
  #endif
  wdt_enable(WDTO_8S);
}


void loop() {
  system_loop_start = millis();
  system_loop_run++;
  ts.execute();

  #ifdef BLOWER_CONTROL_WIFI
  server.handleClient();
  MDNS.update();
  if(readyForNtpUpdate  && motor_logic_state==MOTOR_STOP)
   {
    //Only Update the NTP when the motor is offline and GPIO pulling can be delayed.
    readyForNtpUpdate = false;
    printTime(0);
    updateNTP();
    Serial.print("\nUpdated time from NTP Server: ");
    printTime(0);
    Serial.print("Next NTP Update: ");
    printTime(tick);
  }
  #endif

  if(system_loop_total>system_loop_max)
  {
    system_loop_max = system_loop_total;
  }
  if((lcd_d_task_time_stop-lcd_d_task_time_start)>lcd_d_task_time_max)
  {
    lcd_d_task_time_max = lcd_d_task_time_stop-lcd_d_task_time_start;
  }
  if((lcd_c_task_time_stop-lcd_c_task_time_start)>lcd_c_task_time_max)
  {
    lcd_c_task_time_max = lcd_c_task_time_stop-lcd_c_task_time_start;
  }
  if((gpio_task_time_stop-gpio_task_time_start)>gpio_task_time_max)
  {
    gpio_task_time_max = gpio_task_time_stop-gpio_task_time_start;
  }
  if((MCP_task_time_stop-MCP_task_time_start)>MCP_task_time_max)
  {
    MCP_task_time_max = MCP_task_time_stop-MCP_task_time_start;
  }
  if((motor_task_time_stop-motor_task_time_start)>MCP_task_time_max)
  {
    motor_task_time_max = motor_task_time_stop-motor_task_time_start;
  } 
  system_loop_total = millis()-system_loop_start;
  //ESP.wdtFeed();
}
