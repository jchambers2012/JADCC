#include "include.h"

Adafruit_MCP23017 mcp;

Task t_gpioControl(10000, TASK_FOREVER, &do_sensor_control);

Task t_check_MCP(30000, TASK_FOREVER, &check_MCP);


void check_MCP(){
   bool online = true;
    Wire.beginTransmission(0x20);
    switch (Wire.endTransmission()) {
      case 0:
        //success
      Serial.println ( "success 00" );
        break;
      case 1:
        //data too long to fit in transmit buffer
      Serial.println ( "data too long to fit in transmit buffer 01" );
        online = false;
        break;
      case 2:
        //received NACK on transmit of address
      Serial.println ( "received NACK on transmit of address 02" );
        online = false;
        break;
      case 3:
        //received NACK on transmit of data
      Serial.println ( "received NACK on transmit of data 03" );
        online = false;
        break;
      case 4:
        // error
        online = false;
      Serial.println ( "Error 04" );
        break;
      default:
        //Unknown error
        online = false;
      Serial.println ( "Unknown Error" );
    }
    for (int i = 0; i <= 15; i++) {
      sensors[i].chip_online = online;
    }
    if(online == false)
    {
      master_blower_error = true;
      Serial.println ( "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" );
      Serial.println ( "MCP23017 at 0x20 is OFFLINE" );
      Serial.println ( "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" );
    }else{
      master_blower_error = false;
      Serial.println ( "===========================================" );
      Serial.println ( "MCP23017 at 0x20 is ONLINE" );
      Serial.println ( "===========================================" );

    }
    
}

void do_sensor_control(){
  for (int i = 0; i <= 15; i++) {
    sensors[i].current = mcp.digitalRead(0);

    if(sensors[i].invert == true)
    {
      sensors[i].current = !sensors[i].current;
    }
    if(sensors[i].turn_on == true && sensors[i].current == true)
    {
      master_blower_on = true;
    }
    if(sensors[i].turn_off == true && sensors[i].current == true)
    {
      master_blower_off = true;
    }
    if(sensors[i].f1 == true && sensors[i].current == true)
    {
      master_f1_on = true;
    }
    if(sensors[i].f2 == true && sensors[i].current == true)
    {
      master_f2_on = true;
    }
  
#ifdef BLOWERCONTROLLER_DEBUG
    Serial.print ( "Checking Sensor: (" );
    Serial.print ( i );
    Serial.print ( ") - '" );
    Serial.print ( sensors[i].c_name );
    Serial.print ( "' is " );
    Serial.print ( sensors[i].current );
    if(sensors[i].invert == true)
    {
      Serial.print ( " (Inverted)" );
    }
    if(sensors[i].chip_online == false)
    {
      Serial.print ( " (Read Error)" );
      master_blower_off = true;
    }
      Serial.println ( " " );
#endif  
  }
    
#ifdef BLOWERCONTROLLER_DEBUG
    Serial.println ( "===========================================" );
    Serial.println ( "Sensor Check Done: " );
    Serial.print ( " - Blower Error = " );
    Serial.println ( master_blower_error );
    Serial.print ( " - Blower Off = " );
    Serial.println ( master_blower_off );
    Serial.print ( " - Blower On = " );
    Serial.println ( master_blower_on );
    Serial.print ( " - Blower Function 1 = " );
    Serial.println ( master_f1_on );
    Serial.print ( " - Blower Function 2 = " );
    Serial.println ( master_f2_on );
    Serial.println ( "===========================================" );
#endif  
}



void setup() {

  Wire.begin();
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
  mcp.begin();      // use default address 0
  for (int i = 0; i <= 15; i++) {
    mcp.pinMode(i, INPUT);
  }
#ifdef BLOWERCONTROLLER_DEBUG
  Serial.println ( "DONE Setting up MCP23017" );
#endif  

#ifdef BLOWERCONTROLLER_DEBUG
  Serial.println("Scheduler TEST");
#endif  
  
  ts.init();
  
#ifdef BLOWERCONTROLLER_DEBUG
  Serial.println("Initialized scheduler");
#endif 

  ts.addTask(t_check_MCP);
  t_check_MCP.enable();
#ifdef BLOWERCONTROLLER_DEBUG
  Serial.println("added t_check_MCP");
#endif 

  ts.addTask(t_gpioControl);
  t_gpioControl.enable();
#ifdef BLOWERCONTROLLER_DEBUG
  Serial.println("added t_gpioControl");
#endif 
  //clean FS, for testing
  //SPIFFS.format();

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
    }else {
      Serial.println("config.json missing, defaults will be used");
    }
  } else {
    Serial.println("failed to mount FS");
  }
  //end read
//  strncpy(sensors[15].c_name, "Stop Button", sizeof(sensors[15].c_name));
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
