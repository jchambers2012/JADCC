#ifdef BLOWER_CONTROL_WIFI
#include "webpages.h"

static const char AUX_TIMEZONE[] PROGMEM = R"(
{
  "title": "TimeZone",
  "uri": "/timezone",
  "menu": true,
  "element": [
    {
      "name": "caption",
      "type": "ACText",
      "value": "Sets the time zone to get the current local time.",
      "style": "font-family:Arial;font-weight:bold;text-align:center;margin-bottom:10px;color:DarkSlateBlue"
    },
    {
      "name": "timezone",
      "type": "ACSelect",
      "label": "Select TZ name",
      "option": [],
      "selected": 10
    },
    {
      "name": "newline",
      "type": "ACElement",
      "value": "<br>"
    },
    {
      "name": "start",
      "type": "ACSubmit",
      "value": "OK",
      "uri": "/saveTZ"
    }
  ]
}
)";


static const char PAGE_ELEMENTS[] PROGMEM = R"(
[
  {
    "uri": "/zone1",
    "title": "Zone 1",
    "menu": true,
    "element": [
      {
        "name": "text",
        "type": "ACText",
        "value": "AutoConnect element behaviors collection",
        "style": "font-family:Arial;font-size:18px;font-weight:400;color:#191970"
      },
      {
        "name": "z1-1-e",
        "type": "ACCheckbox",
        "value": "z1-1-e",
        "label": "Z1-1 Enabled",
        "labelposition": "infront",
        "checked": true
      },
      {
        "name": "z1-1-i",
        "type": "ACCheckbox",
        "value": "z1-1-e",
        "label": "Z1-1 Invert",
        "labelposition": "infront",
        "checked": true
      },
      {
        "name": "z1-1-stop",
        "type": "ACCheckbox",
        "value": "z1-1-e",
        "label": "Z1-1 Stop Motor",
        "labelposition": "infront",
        "checked": false
      },
      {
        "name": "z1-1-stop",
        "type": "ACCheckbox",
        "value": "z1-1-e",
        "label": "Z1-1 Start Motor",
        "labelposition": "infront",
        "checked": true
      },
      {
        "name": "z1-1-f1",
        "type": "ACCheckbox",
        "value": "z1-1-f1",
        "label": "Z1-1 Function 1",
        "labelposition": "infront",
        "checked": true
      },
      {
        "name": "z1-1-f2",
        "type": "ACCheckbox",
        "value": "z1-1-f1",
        "label": "Z1-1 Function 2",
        "labelposition": "infront",
        "checked": true
      },
      {
        "name": "z1-1-name",
        "type": "ACInput",
        "label": "Sensor Name",
        "placeholder": "This area accepts hostname patterns",
        "pattern": "^(([a-zA-Z0-9]|[a-zA-Z0-9][a-zA-Z0-9\\-]*[a-zA-Z0-9])\\.)*([A-Za-z0-9]|[A-Za-z0-9][A-Za-z0-9\\-]*[A-Za-z0-9])$"
      },
      {
        "name": "load",
        "type": "ACSubmit",
        "value": "Load",
        "uri": "/elements"
      },
      {
        "name": "save",
        "type": "ACSubmit",
        "value": "Save",
        "uri": "/save"
      },
      {
        "name": "adjust_width",
        "type": "ACElement",
        "value": "<script type=\"text/javascript\">window.onload=function(){var t=document.querySelectorAll(\"input[type='text']\");for(i=0;i<t.length;i++){var e=t[i].getAttribute(\"placeholder\");e&&t[i].setAttribute(\"size\",e.length*.8)}};</script>"
      }
    ]
  },
  {
    "uri": "/zone2",
    "title": "Zone 2",
    "menu": true,
    "element": [
      {
        "name": "text",
        "type": "ACText",
        "value": "AutoConnect element behaviors collection",
        "style": "font-family:Arial;font-size:18px;font-weight:400;color:#191970"
      },
      {
        "name": "check",
        "type": "ACCheckbox",
        "value": "check",
        "label": "Check",
        "labelposition": "infront",
        "checked": true
      },
      {
        "name": "input",
        "type": "ACInput",
        "label": "Text input",
        "placeholder": "This area accepts hostname patterns",
        "pattern": "^(([a-zA-Z0-9]|[a-zA-Z0-9][a-zA-Z0-9\\-]*[a-zA-Z0-9])\\.)*([A-Za-z0-9]|[A-Za-z0-9][A-Za-z0-9\\-]*[A-Za-z0-9])$"
      },
      {
        "name": "radio",
        "type": "ACRadio",
        "value": [
          "Button-1",
          "Button-2",
          "Butotn-3"
        ],
        "label": "Radio buttons",
        "arrange": "vertical",
        "checked": 1
      },
      {
        "name": "select",
        "type": "ACSelect",
        "option": [
          "Option-1",
          "Option-2",
          "Option-3"
        ],
        "label": "Select",
        "selected": 2
      },
      {
        "name": "load",
        "type": "ACSubmit",
        "value": "Load",
        "uri": "/elements"
      },
      {
        "name": "save",
        "type": "ACSubmit",
        "value": "Save",
        "uri": "/save"
      },
      {
        "name": "adjust_width",
        "type": "ACElement",
        "value": "<script type=\"text/javascript\">window.onload=function(){var t=document.querySelectorAll(\"input[type='text']\");for(i=0;i<t.length;i++){var e=t[i].getAttribute(\"placeholder\");e&&t[i].setAttribute(\"size\",e.length*.8)}};</script>"
      }
    ]
  },
  {
    "uri": "/zone3",
    "title": "Zone 3",
    "menu": true,
    "element": [
      {
        "name": "text",
        "type": "ACText",
        "value": "AutoConnect element behaviors collection",
        "style": "font-family:Arial;font-size:18px;font-weight:400;color:#191970"
      },
      {
        "name": "check",
        "type": "ACCheckbox",
        "value": "check",
        "label": "Check",
        "labelposition": "infront",
        "checked": true
      },
      {
        "name": "input",
        "type": "ACInput",
        "label": "Text input",
        "placeholder": "This area accepts hostname patterns",
        "pattern": "^(([a-zA-Z0-9]|[a-zA-Z0-9][a-zA-Z0-9\\-]*[a-zA-Z0-9])\\.)*([A-Za-z0-9]|[A-Za-z0-9][A-Za-z0-9\\-]*[A-Za-z0-9])$"
      },
      {
        "name": "radio",
        "type": "ACRadio",
        "value": [
          "Button-1",
          "Button-2",
          "Butotn-3"
        ],
        "label": "Radio buttons",
        "arrange": "vertical",
        "checked": 1
      },
      {
        "name": "select",
        "type": "ACSelect",
        "option": [
          "Option-1",
          "Option-2",
          "Option-3"
        ],
        "label": "Select",
        "selected": 2
      },
      {
        "name": "load",
        "type": "ACSubmit",
        "value": "Load",
        "uri": "/elements"
      },
      {
        "name": "save",
        "type": "ACSubmit",
        "value": "Save",
        "uri": "/save"
      },
      {
        "name": "adjust_width",
        "type": "ACElement",
        "value": "<script type=\"text/javascript\">window.onload=function(){var t=document.querySelectorAll(\"input[type='text']\");for(i=0;i<t.length;i++){var e=t[i].getAttribute(\"placeholder\");e&&t[i].setAttribute(\"size\",e.length*.8)}};</script>"
      }
    ]
  }
  ]
  )";
  
  static const char PAGE_SAVE[] PROGMEM = R"(
  {
    "uri": "/save",
    "title": "Elements",
    "menu": false,
    "element": [
      {
        "name": "caption",
        "type": "ACText",
        "format": "Elements have been saved to %s",
        "style": "font-family:Arial;font-size:18px;font-weight:400;color:#191970"
      },
      {
        "name": "validated",
        "type": "ACText",
        "style": "color:red"
      },
      {
        "name": "echo",
        "type": "ACText",
        "style": "font-family:monospace;font-size:small;white-space:pre;"
      },
      {
        "name": "ok",
        "type": "ACSubmit",
        "value": "OK",
        "uri": "/elements"
      }
    ]
  }
]
)";
void wifi_setup(){

  Serial.println ( F("Setting up TZ setting page") );
  // Load aux. page
  Timezone.load(AUX_TIMEZONE);
  // Retrieve the select element that holds the time zone code and
  // register the zone mnemonic in advance.
  AutoConnectSelect&  tz = Timezone["timezone"].as<AutoConnectSelect>();
  for (uint8_t n = 0; n < sizeof(TZ) / sizeof(Timezone_t); n++) {
    tz.add(String(TZ[n].zone));
  }

  portal.join({ Timezone });        // Register aux. page
  server.on("/saveTZ", saveTZ);   // Set NTP server trigger handler
  
  Serial.println ( F("Setting up root") );
  // Behavior a root path of ESP8266WebServer.
  server.on("/", rootPage);
  
  Serial.println ( F("Setting up zone settings pages") );
  elementsAux.load(FPSTR(PAGE_ELEMENTS));
  elementsAux.on([] (AutoConnectAux& aux, PageArgument& arg) {
    //Load the needed Elemets
    return String();
  });

  Serial.println ( F("Setting up zone settings pages save funnctions") );
  saveAux.load(FPSTR(PAGE_SAVE));
  saveAux.on([] (AutoConnectAux& aux, PageArgument& arg) {
   //Save the needed Elemets
    return String();
  });

  Serial.println ( F("Setting up portal") );
  portal.join({ elementsAux, saveAux });
  config.portalTimeout = 30000;  // It will time out in 10 secondsretainPortal
  //config.retainPortal = true;
  config.apid = "BlowerConfig";
  config.ticker = true;
  portal.config(config);
  lcd.setCursor(0, 1);
  lcd.print("Connected to SSID");
  lcd.setCursor(0, 2);    
  lcd.print( WiFi.SSID() );
  Serial.println ( F("Attempting to connect to WiFi") );
  if (!portal.begin()) {
    Serial.println("failed to connect and hit timeout");
    lcd.setCursor(0, 2);
    lcd.print("Failed to connect");
    delay(5000);
    wifi_enabled = false;
  }else{
    wifi_enabled = true;
    Serial.print ( F("Attempting to start mDNS for ") );
    Serial.print ( BLOWER_CONTROL_MDNS);
    Serial.println ( F(".local") );
    //if (!MDNS.begin(BLOWER_CONTROL_MDNS)) {
    //  Serial.println("Error setting up MDNS responder!");
    //}
  }
}


//void wificonfigModeCallback(WiFiManager *myWiFiManager){
//  Serial.println("Entered config mode");
//  Serial.println(WiFi.softAPIP());
  // print the ssid that we should connect to to configure the ESP8266
//  Serial.print("Created config portal AP ");
//  Serial.println(myWiFiManager->getConfigPortalSSID());
//  lcd.clear();
//  lcd.print("Failed to connect");
//  lcd.setCursor(0, 1);
//  lcd.print("to SSID ");
//  delay(3000);
//  lcd.clear();
//  lcd.print("Entered config mode");
//  lcd.setCursor(0, 1);
//  lcd.print("Please connect to ");
//  lcd.setCursor(0, 2);    
//  lcd.print("SSID:");
//  lcd.setCursor(6, 2);    
//  lcd.print(myWiFiManager->getConfigPortalSSID());
//  lcd.setCursor(0, 3);    
//  lcd.print("Timeout 30 Sec");
//}
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
