
#ifndef BLOWERCONTROLLER_VARIABLE_H
#define BLOWERCONTROLLER_VARIABLE_H

Scheduler ts; 

bool shouldSaveConfig = false;    //flag for saving data

bool lcd_error = false;
//char lcd_error[2][20] = "";

byte sensors_zone_num = 3;
typedef struct {
  bool enable = true;
  char c_name[20] = "SENSOR Z#-S#"; //Name of the sensor that will be display on the LCD
  bool invert = false;              //Is this sensor inverted HIGH is LOW and LOW is HIGH
  bool turn_on = true;              //Does this sensor turn on the moton
  bool turn_off = false;            //Does this sensor turn off the motor -maybe a safety interlock to verify the garbage bin is in place
  bool chip_online = false;         //Used to verify the MCP is online and used to verify this is a trused reading
  bool f1 = false;                  //Does this sensor turn on F1 Realy
  bool f2 = false;                  //Does this sensor turn on F2 Realy (Ignored if this realy is used to turn on/off the motor
  bool current = false;             //The currently read sensor from the MCP
  bool last = false;                //The last read sensor from the MCP
  bool confirmed = false;           //The state that will be processed for this sesnor
  byte times = 0;                   //The numbers of time the state has been stable from the MCP to help debounce the buttons
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
