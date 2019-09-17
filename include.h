#include <FS.h>                   //this needs to be first, or it all crashes and burns...
#include <TaskScheduler.h>
#include <Wire.h>
#include "Adafruit_MCP23017.h"
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager
#include <ArduinoJson.h>          //https://github.com/bblanchon/ArduinoJson
#include <LiquidCrystal_I2C.h>
#include "variable.h"
#include "setting.h"
#include "functions.h"
