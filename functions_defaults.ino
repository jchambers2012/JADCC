#ifndef BLOWERCONTROLLER_DEFAULTS
#define BLOWERCONTROLLER_DEFAULTS

void load_defaults_boot()
{
  //Set the default names for each sensor. The full name is staored in variable.h
  //This will be overritten by the config.json file (if found)
  sensors[0].c_name[8]='1';sensors[0].c_name[11]='1';
  sensors[1].c_name[8]='1';sensors[1].c_name[11]='2';
  sensors[2].c_name[8]='1';sensors[2].c_name[11]='3';
  sensors[3].c_name[8]='1';sensors[3].c_name[11]='4';
  sensors[4].c_name[8]='1';sensors[4].c_name[11]='5';
  sensors[5].c_name[8]='2';sensors[5].c_name[11]='1';
  sensors[6].c_name[8]='2';sensors[6].c_name[11]='2';
  sensors[7].c_name[8]='2';sensors[7].c_name[11]='3';
  sensors[8].c_name[8]='2';sensors[8].c_name[11]='4';
  sensors[9].c_name[8]='2';sensors[9].c_name[11]='5';
  sensors[10].c_name[8]='3';sensors[10].c_name[11]='1';
  sensors[11].c_name[8]='3';sensors[11].c_name[11]='2';
  sensors[12].c_name[8]='3';sensors[12].c_name[11]='3';
  sensors[13].c_name[8]='3';sensors[13].c_name[11]='4';
  sensors[14].c_name[8]='3';sensors[14].c_name[11]='5';
  #if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 2
  sensors[16].c_name[8]='4';sensors[16].c_name[11]='1';
  sensors[17].c_name[8]='4';sensors[17].c_name[11]='2';
  sensors[18].c_name[8]='4';sensors[18].c_name[11]='3';
  sensors[19].c_name[8]='4';sensors[19].c_name[11]='4';
  sensors[20].c_name[8]='4';sensors[20].c_name[11]='5';
  sensors[21].c_name[8]='5';sensors[21].c_name[11]='1';
  sensors[22].c_name[8]='5';sensors[22].c_name[11]='2';
  sensors[23].c_name[8]='5';sensors[23].c_name[11]='3';
  sensors[24].c_name[8]='5';sensors[24].c_name[11]='4';
  sensors[25].c_name[8]='5';sensors[25].c_name[11]='5';
  sensors[26].c_name[8]='6';sensors[26].c_name[11]='1';
  sensors[27].c_name[8]='6';sensors[27].c_name[11]='2';
  sensors[28].c_name[8]='6';sensors[28].c_name[11]='3';
  sensors[29].c_name[8]='6';sensors[29].c_name[11]='4';
  sensors[30].c_name[8]='6';sensors[30].c_name[11]='5';
  #endif
}

void load_force_stop()
{
  //Force Sensor 15 to be a stop switch but allow other config settings.
  //This can not be overwritten and remain enabled and to disable the motor.
  //Hard coded logic in do_sensor_control() will also disable the motor if
  //this sensor is triggered.
  
  //strncpy(sensors[15].c_name, "Stop Button", sizeof(sensors[15].c_name));
  sensors[15].turn_on = false;
  sensors[15].turn_off = true;
  sensors[15].enable = true;
  //sensors[15].invert = false;
  #if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 2
  //Force Sensor 31 to be a stop switch but allow other config settings.
  //This can not be overwritten and remain enabled and to disable the motor.
  //Hard coded logic in do_sensor_control() will also disable the motor if
  //this sensor is triggered.
  
  //strncpy(sensors[31].c_name, "Stop Button", sizeof(sensors[31].c_name));
  sensors[31].turn_on = false;
  sensors[31].turn_off = true;
  sensors[31].enable = true;
  #endif
  master_stop = true;  //force the system into a stop until the start button has been pressed on first boot
  

}

#endif
