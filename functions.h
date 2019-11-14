#ifndef BLOWERCONTROLLER_FUNCTIONS_H
#define BLOWERCONTROLLER_FUNCTIONS_H
#define BLOWERCONTROLLER_DEBUG
void do_sensor_control();
void check_MCP();
void run_blower_control();
void run_lcd_control();
void run_lcd_draw();
void read_button_green();
void read_button_black();
void read_button_blue();
void read_button_yellow();
void run_debug();
void run_chip_dump();
void load_defaults_boot();
void load_force_stop();

#ifdef BLOWER_CONTROL_WIFI
//WEB SERVER FUNCTIONS
void rootPage();
void zonePage();
void downloadConfig();
void settingsPage();
void saveConfig();
bool createConfigJSON();
int loadConfigJSON();
void restoreConfig();
void settingsMotor();
void zonePageSubmit();
void saveTZ();
String returnDateTime();
String formatBytes(size_t bytes);
String getContentType(String filename);
bool handleFileRead(String path);
void handleFileUpload();
void handleFileDelete();
void handleFileCreate();
void handleFileList();
void web_setup();
void wifi_setup();
void setup_ntp();
void printTime(time_t offset);
void updateNTP();
void secTicker();
#endif
#endif /* functions.h */
