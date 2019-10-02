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

/*

  ntp_udp NTP Client

  Get the time from a Network Time Protocol (NTP) time server
  Demonstrates use of ntp_udp sendPacket and ReceivePacket
  For more on NTP time servers and the messages needed to communicate with them,
  see http://en.wikipedia.org/wiki/Network_Time_Protocol

  created 4 Sep 2010
  by Michael Margolis
  modified 9 Apr 2012
  by Tom Igoe
  updated for the ESP8266 12 Apr 2015
  by Ivan Grokhotkov

  This code is in the public domain.

*/

// send an NTP request to the time server at the given address
void sendNTPpacket(IPAddress& address) {
  Serial.println("sending NTP packet...");
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  ntp_udp.beginPacket(address, 123); //NTP requests are to port 123
  ntp_udp.write(packetBuffer, NTP_PACKET_SIZE);
  ntp_udp.endPacket();
}
void ntp_start(){
  if(wifi_enabled==true)
  {
    ntp_udp.begin(ntp_localPort);
    Serial.print("Local port: ");
    Serial.println(ntp_udp.localPort());
  }
}

void ntp_sync(){
  call_ntp_sync();
}
void call_ntp_sync(){
  if(wifi_enabled==true && WiFi.status() != WL_CONNECTED && ntp_enabled==true)
  {
    //get a random server from the pool
    WiFi.hostByName(ntpServerName, timeServerIP);
  
    sendNTPpacket(timeServerIP); // send an NTP packet to a time server
    // wait to see if a reply is available
    delay(1000);
  
    int cb = ntp_udp.parsePacket();
    if (!cb) {
      Serial.println("no packet yet");
    } else {
      Serial.print("packet received, length=");
      Serial.println(cb);
      // We've received a packet, read the data from it
      ntp_udp   .read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer
  
      //the timestamp starts at byte 40 of the received packet and is four bytes,
      // or two words, long. First, esxtract the two words:
  
      unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
      unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
      // combine the four bytes (two words) into a long integer
      // this is NTP time (seconds since Jan 1 1900):
      unsigned long secsSince1900 = highWord << 16 | lowWord;
      Serial.print("Seconds since Jan 1 1900 = ");
      Serial.println(secsSince1900);
  
      // now convert NTP time into everyday time:
      Serial.print("Unix time = ");
      // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
      const unsigned long seventyYears = 2208988800UL;
      // subtract seventy years:
      unsigned long epoch = secsSince1900 - seventyYears;
      // print Unix time:
      Serial.println(epoch);
  
  
      // print the hour, minute and second:
      Serial.print("The UTC time is ");       // UTC is the time at Greenwich Meridian (GMT)
      Serial.print((epoch  % 86400L) / 3600); // print the hour (86400 equals secs per day)
      Serial.print(':');
      if (((epoch % 3600) / 60) < 10) {
        // In the first 10 minutes of each hour, we'll want a leading '0'
        Serial.print('0');
      }
      Serial.print((epoch  % 3600) / 60); // print the minute (3600 equals secs per minute)
      Serial.print(':');
      if ((epoch % 60) < 10) {
        // In the first 10 seconds of each minute, we'll want a leading '0'
        Serial.print('0');
      }
      Serial.println(epoch % 60); // print the second
    }
  }
}
#endif
