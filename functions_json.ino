#ifdef BLOWER_CONTROL_WIFI
#ifndef BLOWERCONTROLLER_FUNCTIONS_JSON_H
#define BLOWERCONTROLLER_FUNCTIONS_JSON_H


int loadConfigJSON() {
  if (SPIFFS.exists("/config.json")) {
    //file exists, reading and loading
    DC_DBG( "reading config file\n");
    File configFile = SPIFFS.open("/config.json", "r");
    if (configFile) {
      DC_DBG("opened config file\n");
      const size_t capacity = JSON_ARRAY_SIZE(BLOWER_CONTROL_MAX_SENSOR) + JSON_OBJECT_SIZE(6) + BLOWER_CONTROL_MAX_SENSOR * JSON_OBJECT_SIZE(8) + JSON_OBJECT_SIZE(9) + 2270;
      DynamicJsonDocument doc(capacity);
      DeserializationError error = deserializeJson(doc, configFile);
      if (error)
      {
        Serial.println(F("Failed to read file, using default configuration"));
        return -1;
      }
      if (doc["version"] != JSONVERSION || doc["version"] == "")
      {
        Serial.print(F("Failed to read config.json, Version does not match: " ));
        Serial.println( JSONVERSION);
        return -2;
      }
      //int version = doc["version"]; // 1
      //const char* created = doc["created"]; // "pýÿ? "
      //const char* tz = doc["tz"]; // "America/Blanc-Sablon"
      //int zones = doc["zones"]; // 3
      JsonArray date_sensors = doc["sensors"];
      for (JsonVariant v : date_sensors) {
        int id = (int)v["id"];
        if (id >= 0  && id <= BLOWER_CONTROL_MAX_SENSOR)
        {
          //sensors[id].c_name  =  v["c_name"];
          sensors[id].enable  =  (bool)v["enabled"];
          sensors[id].invert  =  (bool)v["invert"];
          sensors[id].turn_on  = (bool)v["turn_on"];
          sensors[id].turn_off = (bool)v["turn_off"];
          sensors[id].f1       = (bool)v["f1"];
          sensors[id].f2       = (bool)v["f2"];
        }
      }


    } else {
      Serial.println("failed to load json config, defaults will be used");
    }
    configFile.close();
    return true;
  }
  Serial.println("config.json missing, defaults will be used");
  return -99;
}
bool createConfigJSON() {
  // Delete existing file, otherwise the configuration is appended to the file
  SPIFFS.remove("/config.json");

  // Open file for writing
  File file = SPIFFS.open("/config.json", "w");
  if (!file) {
    Serial.println(F("Failed to create file /config.json"));
    server.send(500, "text/text", F("Failed to create file /config.json"));
    return false;
  }

  // Allocate a temporary JsonDocument
  // Don't forget to change the capacity to match your requirements.
  // Use arduinojson.org/assistant to compute the capacity.

  const size_t capacity = JSON_ARRAY_SIZE(BLOWER_CONTROL_MAX_SENSOR) + JSON_OBJECT_SIZE(6) + BLOWER_CONTROL_MAX_SENSOR * JSON_OBJECT_SIZE(9) + JSON_OBJECT_SIZE(9) + 2310;
  DynamicJsonDocument doc(capacity);

  // Set the values in the document
  doc["version"] = JSONVERSION;
  doc["created"] = String(returnDateTime());
  doc["tz"] = "America/Blanc-Sablon";  //TODO
  doc["zones"] = sensors_zone_num;
  JsonArray data_sensors = doc.createNestedArray("sensors");
  int i = 0;
  JsonObject sensors_0 = data_sensors.createNestedObject();
  sensors_0["id"]       = i;
  sensors_0["c_name"]   = sensors[i].c_name;
  sensors_0["enabled"]  = sensors[i].enable;
  sensors_0["invert"]   = sensors[i].invert;
  sensors_0["turn_on"]  = sensors[i].turn_on;
  sensors_0["turn_off"] = sensors[i].turn_off;
  sensors_0["f1"]       = sensors[i].f1;
  sensors_0["f2"]       = sensors[i].f2;
  i++;

  JsonObject sensors_1 = data_sensors.createNestedObject();
  sensors_1["id"]       = i;
  sensors_1["c_name"]   = sensors[i].c_name;
  sensors_1["enabled"]  = sensors[i].enable;
  sensors_1["invert"]   = sensors[i].invert;
  sensors_1["turn_on"]  = sensors[i].turn_on;
  sensors_1["turn_off"] = sensors[i].turn_off;
  sensors_1["f1"]       = sensors[i].f1;
  sensors_1["f2"]       = sensors[i].f2;
  i++;

  JsonObject sensors_2 = data_sensors.createNestedObject();
  sensors_2["id"]       = i;
  sensors_2["c_name"]   = sensors[i].c_name;
  sensors_2["enabled"]  = sensors[i].enable;
  sensors_2["invert"]   = sensors[i].invert;
  sensors_2["turn_on"]  = sensors[i].turn_on;
  sensors_2["turn_off"] = sensors[i].turn_off;
  sensors_2["f1"]       = sensors[i].f1;
  sensors_2["f2"]       = sensors[i].f2;
  i++;

  JsonObject sensors_3 = data_sensors.createNestedObject();
  sensors_3["id"]       = i;
  sensors_3["c_name"]   = sensors[i].c_name;
  sensors_3["enabled"]  = sensors[i].enable;
  sensors_3["invert"]   = sensors[i].invert;
  sensors_3["turn_on"]  = sensors[i].turn_on;
  sensors_3["turn_off"] = sensors[i].turn_off;
  sensors_3["f1"]       = sensors[i].f1;
  sensors_3["f2"]       = sensors[i].f2;
  i++;

  JsonObject sensors_4 = data_sensors.createNestedObject();
  sensors_4["id"]       = i;
  sensors_4["c_name"]   = sensors[i].c_name;
  sensors_4["enabled"]  = sensors[i].enable;
  sensors_4["invert"]   = sensors[i].invert;
  sensors_4["turn_on"]  = sensors[i].turn_on;
  sensors_4["turn_off"] = sensors[i].turn_off;
  sensors_4["f1"]       = sensors[i].f1;
  sensors_4["f2"]       = sensors[i].f2;
  i++;

  JsonObject sensors_5 = data_sensors.createNestedObject();
  sensors_5["id"]       = i;
  sensors_5["c_name"]   = sensors[i].c_name;
  sensors_5["enabled"]  = sensors[i].enable;
  sensors_5["invert"]   = sensors[i].invert;
  sensors_5["turn_on"]  = sensors[i].turn_on;
  sensors_5["turn_off"] = sensors[i].turn_off;
  sensors_5["f1"]       = sensors[i].f1;
  sensors_5["f2"]       = sensors[i].f2;
  i++;

  JsonObject sensors_6 = data_sensors.createNestedObject();
  sensors_6["id"]       = i;
  sensors_6["c_name"]   = sensors[i].c_name;
  sensors_6["enabled"]  = sensors[i].enable;
  sensors_6["invert"]   = sensors[i].invert;
  sensors_6["turn_on"]  = sensors[i].turn_on;
  sensors_6["turn_off"] = sensors[i].turn_off;
  sensors_6["f1"]       = sensors[i].f1;
  sensors_6["f2"]       = sensors[i].f2;
  i++;

  JsonObject sensors_7 = data_sensors.createNestedObject();
  sensors_7["id"]       = i;
  sensors_7["c_name"]   = sensors[i].c_name;
  sensors_7["enabled"]  = sensors[i].enable;
  sensors_7["invert"]   = sensors[i].invert;
  sensors_7["turn_on"]  = sensors[i].turn_on;
  sensors_7["turn_off"] = sensors[i].turn_off;
  sensors_7["f1"]       = sensors[i].f1;
  sensors_7["f2"]       = sensors[i].f2;
  i++;

  JsonObject sensors_8 = data_sensors.createNestedObject();
  sensors_8["id"]       = i;
  sensors_8["c_name"]   = sensors[i].c_name;
  sensors_8["enabled"]  = sensors[i].enable;
  sensors_8["invert"]   = sensors[i].invert;
  sensors_8["turn_on"]  = sensors[i].turn_on;
  sensors_8["turn_off"] = sensors[i].turn_off;
  sensors_8["f1"]       = sensors[i].f1;
  sensors_8["f2"]       = sensors[i].f2;
  i++;

  JsonObject sensors_9 = data_sensors.createNestedObject();
  sensors_9["id"]       = i;
  sensors_9["c_name"]   = sensors[i].c_name;
  sensors_9["enabled"]  = sensors[i].enable;
  sensors_9["invert"]   = sensors[i].invert;
  sensors_9["turn_on"]  = sensors[i].turn_on;
  sensors_9["turn_off"] = sensors[i].turn_off;
  sensors_9["f1"]       = sensors[i].f1;
  sensors_9["f2"]       = sensors[i].f2;
  i++;

  JsonObject sensors_10 = data_sensors.createNestedObject();
  sensors_10["id"]       = i;
  sensors_10["c_name"]   = sensors[i].c_name;
  sensors_10["enabled"]  = sensors[i].enable;
  sensors_10["invert"]   = sensors[i].invert;
  sensors_10["turn_on"]  = sensors[i].turn_on;
  sensors_10["turn_off"] = sensors[i].turn_off;
  sensors_10["f1"]       = sensors[i].f1;
  sensors_10["f2"]       = sensors[i].f2;
  i++;

  JsonObject sensors_11 = data_sensors.createNestedObject();
  sensors_11["id"]       = i;
  sensors_11["c_name"]   = sensors[i].c_name;
  sensors_11["enabled"]  = sensors[i].enable;
  sensors_11["invert"]   = sensors[i].invert;
  sensors_11["turn_on"]  = sensors[i].turn_on;
  sensors_11["turn_off"] = sensors[i].turn_off;
  sensors_11["f1"]       = sensors[i].f1;
  sensors_11["f2"]       = sensors[i].f2;
  i++;

  JsonObject sensors_12 = data_sensors.createNestedObject();
  sensors_12["id"]       = i;
  sensors_12["c_name"]   = sensors[i].c_name;
  sensors_12["enabled"]  = sensors[i].enable;
  sensors_12["invert"]   = sensors[i].invert;
  sensors_12["turn_on"]  = sensors[i].turn_on;
  sensors_12["turn_off"] = sensors[i].turn_off;
  sensors_12["f1"]       = sensors[i].f1;
  sensors_12["f2"]       = sensors[i].f2;
  i++;

  JsonObject sensors_13 = data_sensors.createNestedObject();
  sensors_13["id"]       = i;
  sensors_13["c_name"]   = sensors[i].c_name;
  sensors_13["enabled"]  = sensors[i].enable;
  sensors_13["invert"]   = sensors[i].invert;
  sensors_13["turn_on"]  = sensors[i].turn_on;
  sensors_13["turn_off"] = sensors[i].turn_off;
  sensors_13["f1"]       = sensors[i].f1;
  sensors_13["f2"]       = sensors[i].f2;
  i++;

  JsonObject sensors_14 = data_sensors.createNestedObject();
  sensors_14["id"]       = i;
  sensors_14["c_name"]   = sensors[i].c_name;
  sensors_14["enabled"]  = sensors[i].enable;
  sensors_14["invert"]   = sensors[i].invert;
  sensors_14["turn_on"]  = sensors[i].turn_on;
  sensors_14["turn_off"] = sensors[i].turn_off;
  sensors_14["f1"]       = sensors[i].f1;
  sensors_14["f2"]       = sensors[i].f2;
  i++;

  JsonObject sensors_15 = data_sensors.createNestedObject();
  sensors_15["id"]       = i;
  sensors_15["c_name"]   = sensors[i].c_name;
  sensors_15["enabled"]  = sensors[i].enable;
  sensors_15["invert"]   = sensors[i].invert;
  sensors_15["turn_on"]  = sensors[i].turn_on;
  sensors_15["turn_off"] = sensors[i].turn_off;
  sensors_15["f1"]       = sensors[i].f1;
  sensors_15["f2"]       = sensors[i].f2;
  i++;
  JsonObject motor = doc.createNestedObject("motor");
  motor["type"] = 0;
  motor["ir_off_raw"] = "10766,1043,359,1048,354,343,1050,1046,359,1042,359,340,1049,1047,355,344,1049,1047,358,342,1049,1045,357,343,1050,1045,359,341,1050,342,1053,1043,358,1044,360,340,1052,1043,361,1042,363,335,1056,338,1055,338,1058,1038,365,";
  motor["ir_on_raw"] = "10766,1043,359,1048,354,343,1050,1046,359,1042,359,340,1049,1047,355,344,1049,1047,358,342,1049,1045,357,343,1050,1045,359,341,1050,342,1053,1043,358,1044,360,340,1052,1043,361,1042,363,335,1056,338,1055,338,1058,1038,365,";
  motor["rf_off_code"] = "14330290";
  motor["rf_off_tri"] = false;
  motor["rf_on_code"] = "14330289";
  motor["rf_on_tri"] = false;
  motor["rf_off_raw"] = "10777,1043,362,1044,360,337,1057,1043,362,1042,362,337,1057,1042,363,335,1060,1039,365,335,1059,1040,364,337,1057,1042,363,335,1060,334,1060,1039,365,1041,365,333,1061,1037,369,1037,367,335,1060,334,1060,1039,366,334,1061,";
  motor["rf_on_raw"] = "10766,1043,359,1048,354,343,1050,1046,359,1042,359,340,1049,1047,355,344,1049,1047,358,342,1049,1045,357,343,1050,1045,359,341,1050,342,1053,1043,358,1044,360,340,1052,1043,361,1042,363,335,1056,338,1055,338,1058,1038,365,";

  // Serialize JSON to file
  if (serializeJson(doc, file) == 0) {
    Serial.println(F("Failed to write to file"));
    server.send(500, "text/text", F("Failed to write to file"));
    return false;
  }

  // Close the file
  file.close();
  return true;

}
#endif
#endif
