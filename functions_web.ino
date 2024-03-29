#ifdef BLOWER_CONTROL_WIFI
#include "webpages.h"

void rootPage() {
  String  content =
    "<html>"
    "<head>"
    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
    "<script type=\"text/javascript\">"
    "setTimeout(\"location.reload()\", 5000);"
    "</script>"
    "<style>"
    ".sensor {"
    "color:gray;margin:10px;"
    "}"
    "</style>"
    "</head>"
    "<body>"
    "<p></p><p style=\"padding-top:15px;text-align:center\"><a href=\"/settings\">Settings<a></p>"
    "<h3 align=\"center\" class=\"sensor\">Sensor: {{DateTime}}</h3>"
    "{{TOP_MSQ}}"
    "<table align=\"center\"><tr><th>Zone 1</th><th>Zone 2</th><th>Zone 3</th></tr>"
    "<tr><td>"
    "<h3 align=\"center\" class=\"sensor\">{{s0-name}}: {{s0-current}}</h3>"
    "<h3 align=\"center\" class=\"sensor\">{{s1-name}}: {{s1-current}}</h3>"
    "<h3 align=\"center\" class=\"sensor\">{{s2-name}}: {{s2-current}}</h3>"
    "<h3 align=\"center\" class=\"sensor\">{{s3-name}}: {{s3-current}}</h3>"
    "<h3 align=\"center\" class=\"sensor\">{{s4-name}}: {{s4-current}}</h3>"
    "</td><td>"
    "<h3 align=\"center\" class=\"sensor\">{{s5-name}}: {{s5-current}}</h3>"
    "<h3 align=\"center\" class=\"sensor\">{{s6-name}}: {{s6-current}}</h3>"
    "<h3 align=\"center\" class=\"sensor\">{{s7-name}}: {{s7-current}}</h3>"
    "<h3 align=\"center\" class=\"sensor\">{{s8-name}}: {{s8-current}}</h3>"
    "<h3 align=\"center\" class=\"sensor\">{{s9-name}}: {{s9-current}}</h3>"
    "</td><td>"
    "<h3 align=\"center\" class=\"sensor\">{{s10-name}}: {{s10-current}}</h3>"
    "<h3 align=\"center\" class=\"sensor\">{{s11-name}}: {{s11-current}}</h3>"
    "<h3 align=\"center\" class=\"sensor\">{{s12-name}}: {{s12-current}}</h3>"
    "<h3 align=\"center\" class=\"sensor\">{{s13-name}}: {{s13-current}}</h3>"
    "<h3 align=\"center\" class=\"sensor\">{{s14-name}}: {{s14-current}}</h3>"
    "</td></tr></table>"
    "<h3 align=\"center\" class=\"sensor\">STOP: {{s15-current}}</h3>"
    "<h3 align=\"center\" class=\"sensor\">Blower Error: {{master_error}}</h3>"
    "<h3 align=\"center\" class=\"sensor\">Blower Stop: {{master_stop}}</h3>"
    "<h3 align=\"center\" class=\"sensor\">Blower Off: {{master_blower_off}}</h3>"
    "<h3 align=\"center\" class=\"sensor\">Blower On: {{master_blower_on}}</h3>"
    "<h3 align=\"center\" class=\"sensor\">Blower Function 1 : {{master_f1_on}}</h3>"
    "<h3 align=\"center\" class=\"sensor\">Blower Function 2: {{master_f2_on}}</h3>"
    "<h3 align=\"center\" class=\"sensor\">motor_sent_state: {{motor_sent_state}}</h3>"
    "</body>"
    "</html>";
  if (master_error == true)
  {
    content.replace("{{TOP_MSQ}}", String("<h1 align=\"center\"  style=\"color:red;margin:20px;\"><strong>MASTER ERROR TRIGGERED</strong> see bleow for more info <strong>System Disabled</strong></h1>{{TOP_MSQ2}}"));
  } else if (master_stop == true )
  {
    content.replace("{{TOP_MSQ}}", String("<h1 align=\"center\" >Master Motor stop is engaged. Press GREEN button to start system.</h1>{{TOP_MSQ2}}"));
  } else if (master_blower_off == false && master_blower_on == false )
  {
    content.replace("{{TOP_MSQ}}", String("<h1 align=\"center\" >System is standby, waiting for sensor to trigger motor</h1>{{TOP_MSQ2}}"));
  } else if (master_blower_off == true )
  {
    content.replace("{{TOP_MSQ}}", String("<h1 align=\"center\" >Sensor triggered a motor stop.</h1>{{TOP_MSQ2}}"));
  } else if (master_blower_on == true )
  {
    content.replace("{{TOP_MSQ}}", String("<h1 align=\"center\" >Sensor triggered a motor start.</h1>{{TOP_MSQ2}}"));
  }

  if (MCP_online_20 == false)
  {
    content.replace("{{TOP_MSQ}}", String("<h1  align=\"center\" style=\"color:red;margin:20px;\"><strong>SYSTEM ERROR</strong> MCP23017 is HTML_OFFLINE at address 0x21 a power cycle might fix the issue <strong>System Disabled</strong></h1>{{TOP_MSQ2}}"));
  }
#if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 2
  if (MCP_online_21 == false && MCP_enabled_21 == true)
  {
    content.replace("{{TOP_MSQ}}", String("<h1  align=\"center\" style=\"color:red;margin:20px;\"><strong>SYSTEM ERROR</strong> MCP23017 is HTML_OFFLINE at address 0x22  a power cycle might fix the issue <strong>System Disabled</strong></h1>{{TOP_MSQ2}}"));
  }
#endif
#if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 3
  if (MCP_online_22 == false && MCP_enabled_22 == true)
  {
    content.replace("{{TOP_MSQ}}", String("<h1  align=\"center\" style=\"color:red;margin:20px;\"><strong>SYSTEM ERROR</strong> MCP23017 is HTML_OFFLINE at address 0x23  a power cycle might fix the issue <strong>System Disabled</strong></h1>{{TOP_MSQ2}}"));
  }
#endif
#if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 4
  if (MCP_online_23 == false && MCP_enabled_23 == true)
  {
    content.replace("{{TOP_MSQ}}", String("<h1  align=\"center\" style=\"color:red;margin:20px;\"><strong>SYSTEM ERROR</strong> MCP23017 is HTML_OFFLINE at address 0x24  a power cycle might fix the issue <strong>System Disabled</strong></h1>{{TOP_MSQ2}}"));
  }
#endif
  content.replace("{{TOP_MSQ2}}", String("")); //kill off the {{TOP_MSQ}}
  content.replace("{{master_error}}", String(master_error));
  content.replace("{{master_stop}}", String(master_stop));
  content.replace("{{master_blower_off}}", String(master_blower_off));
  content.replace("{{master_blower_on}}", String(master_blower_on));
  content.replace("{{master_f1_on}}", String(master_f1_on));
  content.replace("{{master_f2_on}}", String(master_f2_on));
  content.replace("{{motor_sent_state}}", String(motor_sent_state));

  content.replace("{{s0-name}}", String(sensors[0].c_name));
  if (sensors[0].confirmed) {
    if (sensors[0].turn_off)
    {
      content.replace("{{s0-current}}", HTML_ONLINE_M);
    } else {
      content.replace("{{s0-current}}", HTML_ONLINE);
    }
  } else {
    if (sensors[0].enable)
    {
      content.replace("{{s0-current}}", HTML_OFFLINE);
    } else {
      content.replace("{{s0-current}}", HTML_DISABLED);
    }
  }
  content.replace("{{s1-name}}", String(sensors[1].c_name));
  if (sensors[1].confirmed) {
    if (sensors[1].turn_off)
    {
      content.replace("{{s1-current}}", HTML_ONLINE_M);
    } else {
      content.replace("{{s1-current}}", HTML_ONLINE);
    }
  } else {
    if (sensors[1].enable)
    {
      content.replace("{{s1-current}}", HTML_OFFLINE);
    } else {
      content.replace("{{s1-current}}", HTML_DISABLED);
    }
  }
  content.replace("{{s2-name}}", String(sensors[2].c_name));
  if (sensors[2].confirmed) {
    if (sensors[2].turn_off)
    {
      content.replace("{{s2-current}}", HTML_ONLINE_M);
    } else {
      content.replace("{{s2-current}}", HTML_ONLINE);
    }
  } else {
    if (sensors[2].enable)
    {
      content.replace("{{s2-current}}", HTML_OFFLINE);
    } else {
      content.replace("{{s2-current}}", HTML_DISABLED);
    }
  }
  content.replace("{{s3-name}}", String(sensors[3].c_name));
  if (sensors[3].confirmed) {
    if (sensors[3].turn_off)
    {
      content.replace("{{s3-current}}", HTML_ONLINE_M);
    } else {
      content.replace("{{s3-current}}", HTML_ONLINE);
    }
  } else {
    if (sensors[3].enable)
    {
      content.replace("{{s3-current}}", HTML_OFFLINE);
    } else {
      content.replace("{{s3-current}}", HTML_DISABLED);
    }
  }
  content.replace("{{s4-name}}", String(sensors[4].c_name));
  if (sensors[4].confirmed) {
    if (sensors[4].turn_off)
    {
      content.replace("{{s4-current}}", HTML_ONLINE_M);
    } else {
      content.replace("{{s4-current}}", HTML_ONLINE);
    }
  } else {
    if (sensors[4].enable)
    {
      content.replace("{{s4-current}}", HTML_OFFLINE);
    } else {
      content.replace("{{s4-current}}", HTML_DISABLED);
    }
  }
  content.replace("{{s5-name}}", String(sensors[5].c_name));
  if (sensors[5].confirmed) {
    if (sensors[5].turn_off)
    {
      content.replace("{{s5-current}}", HTML_ONLINE_M);
    } else {
      content.replace("{{s5-current}}", HTML_ONLINE);
    }
  } else {
    if (sensors[5].enable)
    {
      content.replace("{{s5-current}}", HTML_OFFLINE);
    } else {
      content.replace("{{s5-current}}", HTML_DISABLED);
    }
  }
  content.replace("{{s6-name}}", String(sensors[6].c_name));
  if (sensors[6].confirmed) {
    if (sensors[6].turn_off)
    {
      content.replace("{{s6-current}}", HTML_ONLINE_M);
    } else {
      content.replace("{{s6-current}}", HTML_ONLINE);
    }
  } else {
    if (sensors[6].enable)
    {
      content.replace("{{s6-current}}", HTML_OFFLINE);
    } else {
      content.replace("{{s6-current}}", HTML_DISABLED);
    }
  }
  content.replace("{{s7-name}}", String(sensors[7].c_name));
  if (sensors[7].confirmed) {
    if (sensors[7].turn_off)
    {
      content.replace("{{s7-current}}", HTML_ONLINE_M);
    } else {
      content.replace("{{s7-current}}", HTML_ONLINE);
    }
  } else {
    if (sensors[7].enable)
    {
      content.replace("{{s7-current}}", HTML_OFFLINE);
    } else {
      content.replace("{{s7-current}}", HTML_DISABLED);
    }
  }
  content.replace("{{s8-name}}", String(sensors[8].c_name));
  if (sensors[8].confirmed) {
    if (sensors[8].turn_off)
    {
      content.replace("{{s8-current}}", HTML_ONLINE_M);
    } else {
      content.replace("{{s8-current}}", HTML_ONLINE);
    }
  } else {
    if (sensors[8].enable)
    {
      content.replace("{{s8-current}}", HTML_OFFLINE);
    } else {
      content.replace("{{s8-current}}", HTML_DISABLED);
    }
  }
  content.replace("{{s9-name}}", String(sensors[9].c_name));
  if (sensors[9].confirmed) {
    if (sensors[9].turn_off)
    {
      content.replace("{{s9-current}}", HTML_ONLINE_M);
    } else {
      content.replace("{{s9-current}}", HTML_ONLINE);
    }
  } else {
    if (sensors[9].enable)
    {
      content.replace("{{s9-current}}", HTML_OFFLINE);
    } else {
      content.replace("{{s9-current}}", HTML_DISABLED);
    }
  }
  content.replace("{{s10-name}}", String(sensors[10].c_name));
  if (sensors[10].confirmed) {
    if (sensors[10].turn_off)
    {
      content.replace("{{s10-current}}", HTML_ONLINE_M);
    } else {
      content.replace("{{s10-current}}", HTML_ONLINE);
    }
  } else {
    if (sensors[10].enable)
    {
      content.replace("{{s10-current}}", HTML_OFFLINE);
    } else {
      content.replace("{{s10-current}}", HTML_DISABLED);
    }
  }
  content.replace("{{s11-name}}", String(sensors[11].c_name));
  if (sensors[11].confirmed) {
    if (sensors[11].turn_off)
    {
      content.replace("{{s11-current}}", HTML_ONLINE_M);
    } else {
      content.replace("{{s11-current}}", HTML_ONLINE);
    };
  } else {
    if (sensors[11].enable)
    {
      content.replace("{{s11-current}}", HTML_OFFLINE);
    } else {
      content.replace("{{s11-current}}", HTML_DISABLED);
    }
  }
  content.replace("{{s12-name}}", String(sensors[12].c_name));
  if (sensors[12].confirmed) {
    if (sensors[12].turn_off)
    {
      content.replace("{{s12-current}}", HTML_ONLINE_M);
    } else {
      content.replace("{{s12-current}}", HTML_ONLINE);
    }
  } else {
    if (sensors[12].enable)
    {
      content.replace("{{s12-current}}", HTML_OFFLINE);
    } else {
      content.replace("{{s12-current}}", HTML_DISABLED);
    }
  }
  content.replace("{{s13-name}}", String(sensors[13].c_name));
  if (sensors[13].confirmed) {
    if (sensors[13].turn_off)
    {
      content.replace("{{s13-current}}", HTML_ONLINE_M);
    } else {
      content.replace("{{s13-current}}", HTML_ONLINE);
    }
  } else {
    if (sensors[13].enable)
    {
      content.replace("{{s13-current}}", HTML_OFFLINE);
    } else {
      content.replace("{{s13-current}}", HTML_DISABLED);
    }
  }
  content.replace("{{s14-name}}", String(sensors[14].c_name));
  if (sensors[14].confirmed) {
    if (sensors[14].turn_off)
    {
      content.replace("{{s14-current}}", HTML_ONLINE_M);
    } else {
      content.replace("{{s14-current}}", HTML_ONLINE);
    }
  } else {
    if (sensors[14].enable)
    {
      content.replace("{{s14-current}}", HTML_OFFLINE);
    } else {
      content.replace("{{s14-current}}", HTML_DISABLED);
    }
  }
  content.replace("{{s15-name}}", String(sensors[15].c_name));
  if (sensors[15].confirmed) {
    if (sensors[15].turn_off)
    {
      content.replace("{{s15-current}}", HTML_ONLINE_M);
    } else {
      content.replace("{{s15-current}}", HTML_ONLINE);
    }
  } else {
    if (sensors[15].enable)
    {
      content.replace("{{s15-current}}", HTML_OFFLINE);
    } else {
      content.replace("{{s15-current}}", HTML_DISABLED);
    }
  }
  content.replace("{{DateTime}}", String(returnDateTime()));
  server.send(200, "text/html", content);
}
void saveConfig() {
  if (createConfigJSON())
  {
    server.send(200, "text/html", "");
  }
}
void settingsMotor() {

  server.send(200, "text/html", "");
}
void restoreConfig() {

  server.send(200, "text/html", "");
}
void settingsPage() {
  String  content =
    "<html>"
    "<head>"
    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
    "</head>"
    "<body>"
    "<ul>"
    "<li><a href=\"/\">Status Page</a></li>"
    "<li><a href=\"/_ac\">ESP8266 Settings (WiFI)</a></li>"
    "<li><a href=\"/motor\">Edit Motor Control</a></li>"
    "<li><a href=\"/zone1\">Edit Zone 1 Sensors 1-5</a></li>"
    "<li><a href=\"/zone2\">Edit Zone 2 Sensors 1-5</a></li>"
    "<li><a href=\"/zone3\">Edit Zone 3 Sensors 1-5</a></li>"
    "<li><a href=\"/saveConfig\">Commit the config to Flash</a></li>"
    "<li><a href=\"/config.json\">Backup Config</a></li>"
    "<li><a href=\"/restore\">Restore Backed-up Config</a></li>"
    "<li><a href=\"/restore\">Delete Config File and Reboot (WiFi will be uneffected)</a></li>"
    "</ul>"
    "</body>"
    "</html>";

  server.send(200, "text/html", content);
}

void zonePageSubmit() {
  int offset = 0;
  String message  =
    "<html>"
    "<head>"
    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
    "</head>"
    "<body><a href=\"/\"> Go Home to confime settings</a> or <a href=\"/\"> Commit settings to flash storage</a>";
  "</body>"
  "</html>";
  if (server.arg("ID") == "") {
    server.send(500, "text/text", "Missing ID");
    return;
  } else if (server.arg("ID") == "1")
  {
    offset = 0;
  } else if (server.arg("ID") == "2")
  {
    offset = 5;
  } else if (server.arg("ID") == "3")
  {
    offset = 10;
  } else {
    //Error Overflow attack?
    server.send(500, "text/text", "Bad ID");
    return;
  }
  if ( server.arg("1-e") == "")   {
    sensors[0 + offset].enable = false;
  } else {
    sensors[0 + offset].enable = true;
  }
  if ( server.arg("1-i") == "")   {
    sensors[0 + offset].invert = false;
  } else {
    sensors[0 + offset].invert = true;
  }
  if ( server.arg("1-stop") == "")   {
    sensors[0 + offset].turn_off = false;
  } else {
    sensors[0 + offset].turn_off = true;
  }
  if ( server.arg("1-start") == "")   {
    sensors[0 + offset].turn_on = false;
  } else {
    sensors[0 + offset].turn_on = true;
  }
  if ( server.arg("1-f1") == "")   {
    sensors[0 + offset].f1 = false;
  } else {
    sensors[0 + offset].f1 = true;
  }
  if ( server.arg("1-f2") == "")   {
    sensors[0 + offset].f2 = false;
  } else {
    sensors[0 + offset].f2 = true;
  }
  if ( server.arg("2-e") == "")   {
    sensors[1 + offset].enable = false;
  } else {
    sensors[1 + offset].enable = true;
  }
  if ( server.arg("2-i") == "")   {
    sensors[1 + offset].invert = false;
  } else {
    sensors[1 + offset].invert = true;
  }
  if ( server.arg("2-stop") == "")   {
    sensors[1 + offset].turn_off = false;
  } else {
    sensors[1 + offset].turn_off = true;
  }
  if ( server.arg("2-start") == "")   {
    sensors[1 + offset].turn_on = false;
  } else {
    sensors[1 + offset].turn_on = true;
  }
  if ( server.arg("2-f1") == "")   {
    sensors[1 + offset].f1 = false;
  } else {
    sensors[1 + offset].f1 = true;
  }
  if ( server.arg("2-f2") == "")   {
    sensors[1 + offset].f2 = false;
  } else {
    sensors[1 + offset].f2 = true;
  }
  if ( server.arg("3-e") == "")   {
    sensors[2 + offset].enable = false;
  } else {
    sensors[2 + offset].enable = true;
  }
  if ( server.arg("3-i") == "")   {
    sensors[2 + offset].invert = false;
  } else {
    sensors[2 + offset].invert = true;
  }
  if ( server.arg("3-stop") == "")   {
    sensors[2 + offset].turn_off = false;
  } else {
    sensors[2 + offset].turn_off = true;
  }
  if ( server.arg("3-start") == "")   {
    sensors[2 + offset].turn_on = false;
  } else {
    sensors[2 + offset].turn_on = true;
  }
  if ( server.arg("3-f1") == "")   {
    sensors[2 + offset].f1 = false;
  } else {
    sensors[2 + offset].f1 = true;
  }
  if ( server.arg("3-f2") == "")   {
    sensors[2 + offset].f2 = false;
  } else {
    sensors[2 + offset].f2 = true;
  }
  if ( server.arg("4-e") == "")   {
    sensors[3 + offset].enable = false;
  } else {
    sensors[3 + offset].enable = true;
  }
  if ( server.arg("4-i") == "")   {
    sensors[3 + offset].invert = false;
  } else {
    sensors[3 + offset].invert = true;
  }
  if ( server.arg("4-stop") == "")   {
    sensors[3 + offset].turn_off = false;
  } else {
    sensors[3 + offset].turn_off = true;
  }
  if ( server.arg("4-start") == "")   {
    sensors[3 + offset].turn_on = false;
  } else {
    sensors[3 + offset].turn_on = true;
  }
  if ( server.arg("4-f1") == "")   {
    sensors[3 + offset].f1 = false;
  } else {
    sensors[3 + offset].f1 = true;
  }
  if ( server.arg("4-f2") == "")   {
    sensors[3 + offset].f2 = false;
  } else {
    sensors[3 + offset].f2 = true;
  }
  if ( server.arg("5-e") == "")   {
    sensors[4 + offset].enable = false;
  } else {
    sensors[4 + offset].enable = true;
  }
  if ( server.arg("5-i") == "")   {
    sensors[4 + offset].invert = false;
  } else {
    sensors[4 + offset].invert = true;
  }
  if ( server.arg("5-stop") == "")   {
    sensors[4 + offset].turn_off = false;
  } else {
    sensors[4 + offset].turn_off = true;
  }
  if ( server.arg("5-start") == "")   {
    sensors[4 + offset].turn_on = false;
  } else {
    sensors[4 + offset].turn_on = true;
  }
  if ( server.arg("5-f1") == "")   {
    sensors[4 + offset].f1 = false;
  } else {
    sensors[4 + offset].f1 = true;
  }
  if ( server.arg("5-f2") == "")   {
    sensors[4 + offset].f2 = false;
  } else {
    sensors[4 + offset].f2 = true;
  }


  server.send(200, "text/html", message);
}


void zonePage() {
  int offset = 0;
  String content  =
    "</head>"
    "<html>"
    "<head>"
    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
    "<style type=\"text/css\">"
    "th, td {"
    "  padding: 15px;"
    "}"
    "table tr:nth-child(even) {"
    "  background-color: #eee;"
    "}"
    "table tr:nth-child(odd) {"
    "  background-color: #fff;"
    "}"
    "table th {"
    "  color: white;"
    "  background-color: black;"
    "}"
    "</style>"
    "</head>"
    "<body>"
    "<form action=\"/zonePageSubmit\" method=\"post\">"
    "<table><tr><th>ID</th><th>Enabled</th><th>Invert</th><th>Stop Motor</th><th>Start Motor</th><th>Function 1</th><th>Function 2</th><th>Sensor Name</th></tr>"
    "<tr><td>Zone {ID} Sensor 1</td>"
    "<td><input type=\"checkbox\" name=\"1-e\" value=\"1-e\" {1-e} id=\"1-e\"></td>"
    "<td><input type=\"checkbox\" name=\"1-i\" value=\"1-i\" {1-i} id=\"1-i\"></td>"
    "<td><input type=\"checkbox\" name=\"1-stop\" value=\"1-stop\" {1-stop} id=\"1-stop\"></td>"
    "<td><input type=\"checkbox\" name=\"1-start\" value=\"1-start\" {1-start} id=\"1-start\"></td>"
    "<td><input type=\"checkbox\" name=\"1-f1\" value=\"1-f1\" {1-f1} id=\"1-f1\"></td>"
    "<td><input type=\"checkbox\" name=\"1-f2\" value=\"1-f1\" {1-f2} id=\"1-f2\"></td>"
    "<td><input type=\"text\" id=\"1-name\" name=\"1-name\" value=\"{1-name}\"  maxlength=\"20\" placeholder=\"This area accepts hostname patterns\"></td>"
    "</tr>"
    "<tr><td>Zone {ID} Sensor 2</td>"
    "<td><input type=\"checkbox\" name=\"2-e\" value=\"2-e\" {2-e} id=\"2-e\"></td>"
    "<td><input type=\"checkbox\" name=\"2-i\" value=\"2-i\" {2-i} id=\"2-i\"></td>"
    "<td><input type=\"checkbox\" name=\"2-stop\" value=\"2-stop\" {2-stop} id=\"2-stop\"></td>"
    "<td><input type=\"checkbox\" name=\"2-start\" value=\"2-start\" {2-start} id=\"2-start\"></td>"
    "<td><input type=\"checkbox\" name=\"2-f1\" value=\"2-f1\" {2-f1} id=\"2-f1\"></td>"
    "<td><input type=\"checkbox\" name=\"2-f2\" value=\"2-f1\" {2-f2} id=\"2-f2\"></td>"
    "<td><input type=\"text\" id=\"2-name\" name=\"2-name\" value=\"{2-name}\"  maxlength=\"20\" placeholder=\"This area accepts hostname patterns\"></td>"
    "</tr>"
    "<tr><td>Zone {ID} Sensor 3</td>"
    "<td><input type=\"checkbox\" name=\"3-e\" value=\"3-e\" {3-e} id=\"3-e\"></td>"
    "<td><input type=\"checkbox\" name=\"3-i\" value=\"3-i\" {3-i} id=\"3-i\"></td>"
    "<td><input type=\"checkbox\" name=\"3-stop\" value=\"3-stop\" {3-stop} id=\"3-stop\"></td>"
    "<td><input type=\"checkbox\" name=\"3-start\" value=\"3-start\" {3-start} id=\"3-start\"></td>"
    "<td><input type=\"checkbox\" name=\"3-f1\" value=\"3-f1\" {3-f1} id=\"3-f1\"></td>"
    "<td><input type=\"checkbox\" name=\"3-f2\" value=\"3-f1\" {3-f2} id=\"3-f2\"></td>"
    "<td><input type=\"text\" id=\"3-name\" name=\"3-name\" value=\"{3-name}\"  maxlength=\"20\" placeholder=\"This area accepts hostname patterns\"></td>"
    "</tr>"
    "<tr><td>Zone {ID} Sensor 4</td>"
    "<td><input type=\"checkbox\" name=\"4-e\" value=\"4-e\" {4-e} id=\"4-e\"></td>"
    "<td><input type=\"checkbox\" name=\"4-i\" value=\"4-i\" {4-i} id=\"4-i\"></td>"
    "<td><input type=\"checkbox\" name=\"4-stop\" value=\"4-stop\" {4-stop} id=\"4-stop\"></td>"
    "<td><input type=\"checkbox\" name=\"4-start\" value=\"4-start\" {4-start} id=\"4-start\"></td>"
    "<td><input type=\"checkbox\" name=\"4-f1\" value=\"4-f1\" {4-f1} id=\"4-f1\"></td>"
    "<td><input type=\"checkbox\" name=\"4-f2\" value=\"4-f1\" {4-f2} id=\"4-f2\"></td>"
    "<td><input type=\"text\" id=\"4-name\" name=\"4-name\" value=\"{4-name}\"  maxlength=\"20\" placeholder=\"This area accepts hostname patterns\"></td>"
    "</tr>"
    "<tr><td>Zone {ID} Sensor 5</td>"
    "<td><input type=\"checkbox\" name=\"5-e\" value=\"5-e\" {5-e} id=\"5-e\"></td>"
    "<td><input type=\"checkbox\" name=\"5-i\" value=\"5-i\" {5-i} id=\"5-i\"></td>"
    "<td><input type=\"checkbox\" name=\"5-stop\" value=\"5-stop\" {5-stop} id=\"5-stop\"></td>"
    "<td><input type=\"checkbox\" name=\"5-start\" value=\"5-start\" {5-start} id=\"5-start\"></td>"
    "<td><input type=\"checkbox\" name=\"5-f1\" value=\"5-f1\" {5-f1} id=\"5-f1\"></td>"
    "<td><input type=\"checkbox\" name=\"5-f2\" value=\"5-f1\" {5-f2} id=\"5-f2\"></td>"
    "<td><input type=\"text\" id=\"5-name\" name=\"5-name\" value=\"{5-name}\"  maxlength=\"20\" placeholder=\"This area accepts hostname patterns\"></td>"
    "</tr>"
    "</table>"
    " <input type=\"hidden\" name=\"ID\" value=\"{ID}\" id=\"ID\">"
    "<input type=\"submit\" value=\"Save\">"
    "</form>"
    "</body>"
    "</html>";

  if (server.uri() == "/zone1") {
    offset = 0;
    content.replace("{ID}", "1");
  } else if (server.uri() == "/zone2") {
    offset = 5;
    content.replace("{ID}", "2");
  } else if (server.uri() == "/zone3") {
    offset = 10;
    content.replace("{ID}", "3");
  }

  content.replace("{{portal}}", server.uri());
  if (sensors[0 + offset].enable == true)   {
    content.replace("{1-e}", "checked");
  }
  if (sensors[0 + offset].invert == true)   {
    content.replace("{1-i}", "checked");
  }
  if (sensors[0 + offset].turn_off == true) {
    content.replace("{1-stop}", "checked");
  }
  if (sensors[0 + offset].turn_on == true)  {
    content.replace("{1-start}", "checked");
  }
  if (sensors[0 + offset].f1 == true)       {
    content.replace("{1-f1}", "checked");
  }
  if (sensors[0 + offset].f2 == true)       {
    content.replace("{1-f2}", "checked");
  }
  content.replace("{1-name}", String(sensors[0 + offset].c_name));

  if (sensors[1 + offset].enable == true)   {
    content.replace("{2-e}", "checked");
  }
  if (sensors[1 + offset].invert == true)   {
    content.replace("{2-i}", "checked");
  }
  if (sensors[1 + offset].turn_off == true) {
    content.replace("{2-stop}", "checked");
  }
  if (sensors[1 + offset].turn_on == true)  {
    content.replace("{2-start}", "checked");
  }
  if (sensors[1 + offset].f1 == true)       {
    content.replace("{2-f1}", "checked");
  }
  if (sensors[1 + offset].f2 == true)       {
    content.replace("{2-f2}", "checked");
  }
  content.replace("{2-name}", String(sensors[1 + offset].c_name));

  if (sensors[2 + offset].enable == true)   {
    content.replace("{3-e}", "checked");
  }
  if (sensors[2 + offset].invert == true)   {
    content.replace("{3-i}", "checked");
  }
  if (sensors[2 + offset].turn_off == true) {
    content.replace("{3-stop}", "checked");
  }
  if (sensors[2 + offset].turn_on == true)  {
    content.replace("{3-start}", "checked");
  }
  if (sensors[2 + offset].f1 == true)       {
    content.replace("{3-f1}", "checked");
  }
  if (sensors[2 + offset].f2 == true)       {
    content.replace("{3-f2}", "checked");
  }
  content.replace("{3-name}", String(sensors[2 + offset].c_name));

  if (sensors[3 + offset].enable == true)   {
    content.replace("{4-e}", "checked");
  }
  if (sensors[3 + offset].invert == true)   {
    content.replace("{4-i}", "checked");
  }
  if (sensors[3 + offset].turn_off == true) {
    content.replace("{4-stop}", "checked");
  }
  if (sensors[3 + offset].turn_on == true)  {
    content.replace("{4-start}", "checked");
  }
  if (sensors[3 + offset].f1 == true)       {
    content.replace("{4-f1}", "checked");
  }
  if (sensors[3 + offset].f2 == true)       {
    content.replace("{4-f2}", "checked");
  }
  content.replace("{4-name}", String(sensors[3 + offset].c_name));

  if (sensors[4 + offset].enable == true)   {
    content.replace("{5-e}", "checked");
  }
  if (sensors[4 + offset].invert == true)   {
    content.replace("{5-i}", "checked");
  }
  if (sensors[4 + offset].turn_off == true) {
    content.replace("{5-stop}", "checked");
  }
  if (sensors[4 + offset].turn_on == true)  {
    content.replace("{5-start}", "checked");
  }
  if (sensors[4 + offset].f1 == true)       {
    content.replace("{5-f1}", "checked");
  }
  if (sensors[4 + offset].f2 == true)       {
    content.replace("{5-f2}", "checked");
  }
  content.replace("{5-name}", String(sensors[4 + offset].c_name));
  server.send(200, "text/html", content);
}

void downloadConfig()
{
  if (SPIFFS.exists("/config.json") ) {
    File file = SPIFFS.open("/config.json", "r");
    server.streamFile(file, F("text/json"));
    file.close();
    return;
  } else {
    server.send(500, "text/html", F("<html><head></head><body><h1>CONFIG.JSON Not found, default options are being used.</h1><p>Please see manual on how to setup the system</p></body></html>"));
    return;
  }
}

void saveTZ() {
  // Retrieve the value of AutoConnectElement with arg function of WebServer class.
  // Values are accessible with the element name.
  String  tz = server.arg("timezone");

  for (uint8_t n = 0; n < sizeof(TZ) / sizeof(Timezone_t); n++) {
    String  tzName = String(TZ[n].zone);
    if (tz.equalsIgnoreCase(tzName)) {
      configTime(TZ[n].tzoff * 3600, 0, TZ[n].ntpServer);
      Serial.println("Time zone: " + tz);
      Serial.println("ntp server: " + String(TZ[n].ntpServer));
      break;
    }
  }

  // The /start page just constitutes timezone,
  // it redirects to the root page without the content response.
  server.sendHeader("Location", String("http://") + server.client().localIP().toString() + String("/"));
  server.send(302, "text/plain", "");
  server.client().flush();
  server.client().stop();
}

#endif
