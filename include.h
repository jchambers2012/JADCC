#include <FS.h>
#include "setting.h"
//#define _TASK_SLEEP_ON_IDLE_RUN
#define _TASK_PRIORITY
//#define _TASK_WDT_IDS
#define _TASK_TIMECRITICAL
#define _TASK_STD_FUNCTION
#include <TaskScheduler.h>
#include <Wire.h>
#include "Adafruit_MCP23017.h"
#include <LiquidCrystal_I2C.h>
#include <RCSwitch.h>
#include <Ticker.h>
#include <ArduinoJson.h>          //https://github.com/bblanchon/ArduinoJson
#ifdef BLOWER_CONTROL_WIFI
  //#include <ESP8266mDNS.h>
  #include <AutoConnect.h>
  #include <simpleDSTadjust.h>
  #include "webpages.h"
  #include <time.h>
#endif
#include "variable.h"
#include "functions.h"
