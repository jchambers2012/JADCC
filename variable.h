#ifndef BLOWERCONTROLLER_VARIABLE_H
#define BLOWERCONTROLLER_VARIABLE_H

Scheduler ts, cts; 
bool shouldSaveConfig = false;    //flag for saving data

bool lcd_debug = false;
int lcd_d_task_time = 1000;  //how offen to refresh the LDC screen
int lcd_c_task_time = 250;   //how offen the LCD logic is run to see what screens need to be seen based on GPIOs and Motor Logic
byte lcd_redraw = 0;
bool lcd_error = false;
byte lcd_redraw_every = 10;
int lcd_screen = 0;
int lcd_screen_next = 0;
int lcd_screen_delay = 0;
//char lcd_error[2][20] = "";

byte sensors_zone_num = 3;
typedef struct {
  bool enable = true;               //Should the sensor even be checked
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
  byte times_required = 5;          //The numbers of time the state has to be stable
} sensor_type;
sensor_type sensors[16];

typedef struct {
  bool current = false;             //The currently read sensor from the MCP
  bool last = false;                //The last read sensor from the MCP
  bool confirmed = false;           //The state that will be processed for this sesnor
  byte times = 0;                   //The numbers of time the state has been stable from the MCP to help debounce the buttons
  byte times_required = 5;          //The numbers of time the state has to be stable
} gpio_type;

gpio_type gpio_button_green;
gpio_type gpio_button_blue;
gpio_type gpio_button_black;
gpio_type gpio_button_yellow;

bool gpio_debug = false;
int gpio_task_time = 100;

bool motor_debug = false;
int motor_task_time = 500;
bool motor_force_state = true;      //used to forcethe do_motor_control() function to set the blower state, should be set to true for first boot
bool motor_logic_state = false;     //used by the run_blower_control() to set the blower state
bool motor_sent_state = false;       //used by the do_motor_control() to set the blower state

bool motor_ir = false;              //if the motor needs to send an IR code out to start/stop the motor
bool motor_f2 = false;              //if the motor is controlled via Function Relay 2

int MCP_task_time = 10000;
bool MCP_debug = false;

bool require_green = true;          //Required to press the green button an a safty stop of the motor
bool master_stop = false;
bool master_blower_on = false;
bool master_blower_off = false;
bool master_error = false;
bool master_f1_on = false;
bool master_f2_on = false;

const unsigned int check_sensors = 100;
unsigned long lastSampleTime = millis();

#define MOTOR_STOP false
#define MOTOR_START true
#define RELAY_F1 D5         
#define RELAY_F2 D3
#define RELAY_LED_RED D6
#define RELAY_LED_GREEN D4
#define GPIO_START D7
#define GPIO_IR D0
#define GPIO_B1 D8
#define GPIO_B2 A0
#endif /* VARIABLE_H */
