#ifdef BLOWER_CONTROL_WIFI
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
  lcd.print("Timeout 60 Sec");
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
#endif
