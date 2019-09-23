#include "include.h"
;;;;;;;;;;;;;;;;;;;;
Adafruit_MCP23017 mcp_20; //Zones 1-3 Sensors INDEX 0-15

#if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 2
  Adafruit_MCP23017 mcp_21; //Zones 4-6 Sensors INDEX 16-31
#endif

LiquidCrystal_I2C lcd(0x27, 20, 4);

Task t_gpioControl(gpio_task_time, TASK_FOREVER, &do_sensor_control);

Task t_run_blower_control(motor_task_time, TASK_FOREVER, &run_blower_control);

Task t_check_MCP(MCP_task_time, TASK_FOREVER, &check_MCP);

Task t_run_lcd_control(lcd_c_task_time, TASK_FOREVER, &run_lcd_control);

Task t_run_lcd_draw(lcd_d_task_time, TASK_FOREVER, &run_lcd_draw);

Task t_run_debug(5000, TASK_FOREVER, &run_debug);


void setup() {
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
  Serial.print ( "Blower Controller Version: " );
  Serial.println ( BLOWER_VERSION );
  Serial.println ( "Created By Jason Chambers" );
  Serial.println ( "Warning - This device does not contain any Emergency Control or Fail-Safe Functions. This device should not be used as a life safety system." );

  #ifdef BLOWERCONTROLLER_DEBUG
  Serial.print ( "Zones Enabled: " );
  Serial.println ( sensors_zone_num );
  #endif

  #ifdef BLOWERCONTROLLER_DEBUG
  Serial.println ( "Setting up MCP23017" );
  #endif
  mcp_20.begin(0);      // use default address 0 (0x20)
  for (int i = 0; i <= 15; i++) {
    mcp.pinMode(i, INPUT);
  }
  
  #ifdef BLOWERCONTROLLER_DEBUG
  Serial.println ( "DONE Setting up MCP23017" );
  #endif

  #ifdef BLOWERCONTROLLER_DEBUG
  Serial.println("++++++++++++++++++++++++++++++++++++++++");
  Serial.println("Scheduler INIT");
  #endif


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
  //clean FS, for testing
  //SPIFFS.format();

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

  //read configuration from FS json
  Serial.println("Mounting FS...");

  if (SPIFFS.begin()) {
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
          Serial.println("\nparsed json");

          //strcpy(mqtt_server, json["mqtt_server"]);
          //strcpy(mqtt_port, json["mqtt_port"]);
          //strcpy(blynk_token, json["blynk_token"]);

        } else {
          Serial.println("failed to load json config");
        }
        configFile.close();
      }
    } else {
      Serial.println("config.json missing, defaults will be used");
    }
  } else {
    Serial.println("failed to mount FS");
  }
  
  
  
  //This controller is complied for dual controller
  #if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 2
    if(MCP_enabled_21==true)
	{
	  //Dual controller board is enabled
      mcp_21.begin(1);      // use default address 1 (0x21)
      for (int i = 0; i <= 15; i++) {
        mcp.pinMode(i, INPUT);
      }
	  gpio_max_read = 31;  //Incease the number of sensor that should be read by the system
	}
  #endif
  
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
  sensors[13].turn_on = false;
  sensors[13].turn_off = true;
  sensors[13].f1 = true;
  //master_stop = false;
}


void loop() {
  ts.execute();

  if (shouldSaveConfig) {
    Serial.println("saving config");
    DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();
    //json["mqtt_server"] = mqtt_server;
    //json["mqtt_port"] = mqtt_port;
    //json["blynk_token"] = blynk_token;

    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
      Serial.println("failed to open config file for writing");
    }

    json.printTo(Serial);
    json.printTo(configFile);
    configFile.close();
    //end save
  }
}
