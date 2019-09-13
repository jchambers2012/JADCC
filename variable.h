
#ifndef BLOWERCONTROLLER_VARIABLE_H
#define BLOWERCONTROLLER_VARIABLE_H

Scheduler ts; 

bool shouldSaveConfig = false;    //flag for saving data

byte sensors_zone_num = 3;
typedef struct {
  bool enable = true;
  char c_name[20] = "THIS IS A TEST";
  bool invert = false;
  bool turn_on = true;
  bool turn_off = false;
  bool chip_online = false;
  bool f1 = false;
  bool f2 = false;
  bool current = false;
} sensor_type;

sensor_type sensors[15];

bool master_blower_on = false;
bool master_blower_off = false;
bool master_blower_error = false;
bool master_f1_on = false;
bool master_f2_on = false;

const unsigned int check_sensors = 100;
unsigned long lastSampleTime = millis();


#endif /* VARIABLE_H */
