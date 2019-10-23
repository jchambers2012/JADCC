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
    "</head>"
    "<body>"
    "<p></p><p style=\"padding-top:15px;text-align:center\">" AUTOCONNECT_LINK(COG_24) "</p>"
    "<h3 align=\"center\" style=\"color:gray;margin:10px;\">Sensor: {{DateTime}}</h3>"
    "{{TOP_MSQ}}"
    "<h3 align=\"center\" style=\"color:gray;margin:10px;\">Sensor: {{s0-name}} {{s0-current}}</h3>"
    "<h3 align=\"center\" style=\"color:gray;margin:10px;\">Sensor: {{s1-name}} {{s1-current}}</h3>"
    "<h3 align=\"center\" style=\"color:gray;margin:10px;\">Sensor: {{s2-name}} {{s2-current}}</h3>"
    "<h3 align=\"center\" style=\"color:gray;margin:10px;\">Sensor: {{s3-name}} {{s3-current}}</h3>"
    "<h3 align=\"center\" style=\"color:gray;margin:10px;\">Sensor: {{s4-name}} {{s4-current}}</h3>"
    "<h3 align=\"center\" style=\"color:gray;margin:10px;\">Sensor: {{s5-name}} {{s5-current}}</h3>"
    "<h3 align=\"center\" style=\"color:gray;margin:10px;\">Sensor: {{s6-name}} {{s6-current}}</h3>"
    "<h3 align=\"center\" style=\"color:gray;margin:10px;\">Sensor: {{s7-name}} {{s7-current}}</h3>"
    "<h3 align=\"center\" style=\"color:gray;margin:10px;\">Sensor: {{s8-name}} {{s8-current}}</h3>"
    "<h3 align=\"center\" style=\"color:gray;margin:10px;\">Sensor: {{s9-name}} {{s9-current}}</h3>"
    "<h3 align=\"center\" style=\"color:gray;margin:10px;\">Sensor: {{s10-name}} {{s10-current}}</h3>"
    "<h3 align=\"center\" style=\"color:gray;margin:10px;\">Sensor: {{s11-name}} {{s11-current}}</h3>"
    "<h3 align=\"center\" style=\"color:gray;margin:10px;\">Sensor: {{s12-name}} {{s12-current}}</h3>"
    "<h3 align=\"center\" style=\"color:gray;margin:10px;\">Sensor: {{s13-name}} {{s13-current}}</h3>"
    "<h3 align=\"center\" style=\"color:gray;margin:10px;\">Sensor: {{s14-name}} {{s14-current}}</h3>"
    "<h3 align=\"center\" style=\"color:gray;margin:10px;\">STOP: {{s15-name}} {{s15-current}}</h3>"
    "<h3 align=\"center\" style=\"color:gray;margin:10px;\">Blower Error: {{master_error}}</h3>"
    "<h3 align=\"center\" style=\"color:gray;margin:10px;\">Blower Stop: {{master_stop}}</h3>"
    "<h3 align=\"center\" style=\"color:gray;margin:10px;\">Blower Off: {{master_blower_off}}</h3>"
    "<h3 align=\"center\" style=\"color:gray;margin:10px;\">Blower On: {{master_blower_on}}</h3>"
    "<h3 align=\"center\" style=\"color:gray;margin:10px;\">Blower Function 1 : {{master_f1_on}}</h3>"
    "<h3 align=\"center\" style=\"color:gray;margin:10px;\">Blower Function 2: {{master_f2_on}}</h3>"
    "<h3 align=\"center\" style=\"color:gray;margin:10px;\">motor_sent_state: {{motor_sent_state}}</h3>"
    "</body>"
    "</html>";
  if (master_error == true)
  {
    content.replace("{{TOP_MSQ}}", String("<h1 align=\"center\"  style=\"color:red;margin:20px;\"><strong>MASTER ERROR TRIGGERED</strong> see bleow for more info <strong>System Disabled</strong></h1>{{TOP_MSQ2}}"));
  }else if (master_stop == true )
  {
    content.replace("{{TOP_MSQ}}", String("<h1 align=\"center\" >Master Motor stop is engaged. Press GREEN button to start system.</h1>{{TOP_MSQ2}}"));
  }else if (master_blower_off == false && master_blower_on == false )
  {
    content.replace("{{TOP_MSQ}}", String("<h1 align=\"center\" >System is standby, waiting for sensor to trigger motor</h1>{{TOP_MSQ2}}"));
  }else if (master_blower_off == true )
  {
    content.replace("{{TOP_MSQ}}", String("<h1 align=\"center\" >Sensor triggered a motor stop.</h1>{{TOP_MSQ2}}"));
  }else if (master_blower_on == true )
  {
    content.replace("{{TOP_MSQ}}", String("<h1 align=\"center\" >Sensor triggered a motor start.</h1>{{TOP_MSQ2}}"));
  }

  if (MCP_online_20 == false)
  {
    content.replace("{{TOP_MSQ}}", String("<h1  align=\"center\" style=\"color:red;margin:20px;\"><strong>SYSTEM ERROR</strong> MCP23017 is offline at address 0x21 a power cycle might fix the issue <strong>System Disabled</strong></h1>{{TOP_MSQ2}}"));
  }   
  #if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 2
  if (MCP_online_21 == false && MCP_enabled_21 == true)
  {
    content.replace("{{TOP_MSQ}}", String("<h1  align=\"center\" style=\"color:red;margin:20px;\"><strong>SYSTEM ERROR</strong> MCP23017 is offline at address 0x22  a power cycle might fix the issue <strong>System Disabled</strong></h1>{{TOP_MSQ2}}"));
  } 
  #endif
  #if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 3
  if (MCP_online_22 == false && MCP_enabled_22 == true)
  {
    content.replace("{{TOP_MSQ}}", String("<h1  align=\"center\" style=\"color:red;margin:20px;\"><strong>SYSTEM ERROR</strong> MCP23017 is offline at address 0x23  a power cycle might fix the issue <strong>System Disabled</strong></h1>{{TOP_MSQ2}}"));
  }
  #endif 
  #if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 4
  if (MCP_online_23 == false && MCP_enabled_23 == true)
  {
    content.replace("{{TOP_MSQ}}", String("<h1  align=\"center\" style=\"color:red;margin:20px;\"><strong>SYSTEM ERROR</strong> MCP23017 is offline at address 0x24  a power cycle might fix the issue <strong>System Disabled</strong></h1>{{TOP_MSQ2}}"));
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
  content.replace("{{s0-current}}", String(sensors[0].current));
  content.replace("{{s1-name}}", String(sensors[1].c_name));
  content.replace("{{s1-current}}", String(sensors[1].current));
  content.replace("{{s2-name}}", String(sensors[2].c_name));
  content.replace("{{s2-current}}", String(sensors[2].current));
  content.replace("{{s3-name}}", String(sensors[3].c_name));
  content.replace("{{s3-current}}", String(sensors[3].current));
  content.replace("{{s4-name}}", String(sensors[4].c_name));
  content.replace("{{s4-current}}", String(sensors[4].current));
  content.replace("{{s5-name}}", String(sensors[5].c_name));
  content.replace("{{s5-current}}", String(sensors[5].current));
  content.replace("{{s6-name}}", String(sensors[6].c_name));
  content.replace("{{s6-current}}", String(sensors[6].current));
  content.replace("{{s7-name}}", String(sensors[7].c_name));
  content.replace("{{s7-current}}", String(sensors[7].current));
  content.replace("{{s8-name}}", String(sensors[8].c_name));
  content.replace("{{s8-current}}", String(sensors[8].current));
  content.replace("{{s9-name}}", String(sensors[9].c_name));
  content.replace("{{s9-current}}", String(sensors[9].current));
  content.replace("{{s10-name}}", String(sensors[10].c_name));
  content.replace("{{s10-current}}", String(sensors[10].current));
  content.replace("{{s11-name}}", String(sensors[11].c_name));
  content.replace("{{s11-current}}", String(sensors[11].current));
  content.replace("{{s12-name}}", String(sensors[12].c_name));
  content.replace("{{s12-current}}", String(sensors[12].current));
  content.replace("{{s13-name}}", String(sensors[13].c_name));
  content.replace("{{s13-current}}", String(sensors[13].current));
  content.replace("{{s14-name}}", String(sensors[14].c_name));
  content.replace("{{s14-current}}", String(sensors[14].current));
  content.replace("{{s15-name}}", String(sensors[15].c_name));
  content.replace("{{s15-current}}", String(sensors[15].current));
  static const char *wd[7] = { "Sun", "Mon", "Tue", "Wed", "Thr", "Fri", "Sat" };
  struct tm *tm;
  time_t  t;
  char    dateTime[26];

  t = time(NULL);
  tm = localtime(&t);
  sprintf(dateTime, "%04d/%02d/%02d(%s) %02d:%02d:%02d.",
          tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
          wd[tm->tm_wday],
          tm->tm_hour, tm->tm_min, tm->tm_sec);
  content.replace("{{DateTime}}", String(dateTime));
  server.send(200, "text/html", content);
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
