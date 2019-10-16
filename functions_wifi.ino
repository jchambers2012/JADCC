#ifdef BLOWER_CONTROL_WIFI

void wifi_setup(){
  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;

  //reset settings - for testing
  //wifiManager.resetSettings();
  wifiManager.setAPCallback(wificonfigModeCallback);
  wifiManager.setConfigPortalTimeout(30);
  lcd.setCursor(0, 1);
  lcd.print("Connecting to SSID");
  lcd.setCursor(0, 2);    
  lcd.print( WiFi.SSID() );
  if (!wifiManager.autoConnect("BlowerConfig")) {
    Serial.println("failed to connect and hit timeout");
    lcd.setCursor(0, 2);
    lcd.print("Failed to connect");
    delay(5000);
  }
}


void wificonfigModeCallback(WiFiManager *myWiFiManager){
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  // print the ssid that we should connect to to configure the ESP8266
  Serial.print("Created config portal AP ");
  Serial.println(myWiFiManager->getConfigPortalSSID());
  lcd.clear();
  lcd.print("Failed to connect");
  lcd.setCursor(0, 1);
  lcd.print("to SSID ");
  delay(3000);
  lcd.clear();
  lcd.print("Entered config mode");
  lcd.setCursor(0, 1);
  lcd.print("Please connect to ");
  lcd.setCursor(0, 2);    
  lcd.print("SSID:");
  lcd.setCursor(6, 2);    
  lcd.print(myWiFiManager->getConfigPortalSSID());
  lcd.setCursor(0, 3);    
  lcd.print("Timeout 30 Sec");
}
void wifi_save_config () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
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


// Minimal NTP Time Demo with DST correction
//
// Uses built-in ESP8266 LWIP sntp library to get time
// https://github.com/neptune2/simpleDSTadjust


void setup_ntp(){
  updateNTP(); // Init the NTP time
  printTime(0); // print initial time time now.

  tick = NTP_UPDATE_INTERVAL_SEC; // Init the NTP update countdown ticker
  ticker1.attach(1, secTicker); // Run a 1 second interval Ticker
  Serial.print("Next NTP Update: ");
  printTime(tick);
}

// NTP timer update ticker
void secTicker()
{
  tick--;
  if(tick<=0)
   {
    readyForNtpUpdate = true;
    tick= NTP_UPDATE_INTERVAL_SEC; // Re-arm
   }

   //printTime(0);  // Uncomment if you want to see time printed every second
}


void updateNTP() {
  byte i_break = 10;
  configTime(timezone * 3600, 0, NTP_SERVERS);

  delay(500);
  while (!time(nullptr)) {
    Serial.print("#");
    delay(1000);
    i_break--;
    if(i_break==0){
      ntp_synced=false;
      break;
    }
  }
  ntp_synced=true;
}


void printTime(time_t offset)
{
  char buf[30];
  char *dstAbbrev;
  time_t t = dstAdjusted.time(&dstAbbrev)+offset;
  struct tm *timeinfo = localtime (&t);
  
  int hour = (timeinfo->tm_hour+11)%12+1;  // take care of noon and midnight
  sprintf(buf, "%02d/%02d/%04d %02d:%02d:%02d%s %s\n",timeinfo->tm_mon+1, timeinfo->tm_mday, timeinfo->tm_year+1900, hour, timeinfo->tm_min, timeinfo->tm_sec, timeinfo->tm_hour>=12?"pm":"am", dstAbbrev);
  Serial.print(buf);
}


#endif
