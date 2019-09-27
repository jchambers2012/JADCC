#ifndef BLOWERCONTROLLER_VARIABLE_H
#define BLOWERCONTROLLER_VARIABLE_H

#define BLOWER_VERSION "0.08 BETA"

Scheduler ts, cts; 

RCSwitch motorRF = RCSwitch();

bool shouldSaveConfig = false;    //flag for saving data

bool debug_debug = true;
int debug_debug_task_time = 5000;  //how offen to refresh the LDC screen
unsigned long debug_debug_time, debug_debug_ran ; //Track the time each function takes to run
unsigned long debug_debug_times[10];
unsigned long system_loop_start,system_loop_total,system_loop_run,system_loop_max; //Track the time each function takes to run

bool lcd_debug = false;
int lcd_d_task_time = 1000;  //how offen to refresh the LDC screen
int lcd_c_task_time = 250;   //how offen the LCD logic is run to see what screens need to be seen based on GPIOs and Motor Logic
unsigned long lcd_d_task_time_start, lcd_d_task_time_stop, lcd_d_task_time_ran, lcd_d_task_time_max, lcd_c_task_time_start, lcd_c_task_time_stop, lcd_c_task_time_ran, lcd_c_task_time_max; //Track the time each function takes to run
#define LCD_REDRAW_TIMES 20
byte lcd_redraw = LCD_REDRAW_TIMES;
bool lcd_error = false;
byte lcd_redraw_every = 10;
int lcd_screen = 0;
int lcd_last_sensor_a = 0;
int lcd_last_sensor_b = 0;
int lcd_last_sensor_c = 0;
byte lcd_last_sensor_flag_a = 0;
bool lcd_last_sensor_flag_b = false;
bool lcd_last_sensor_flag_wifi = false;
int lcd_screen_next = 0;
int lcd_screen_delay = 0;
byte lcd_wifi_none[8] ={0b01010,0b00100,0b01010,0b00000,0b10001,0b10001,0b11111,0b01110};
//char lcd_error[2][20] = "";


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
  byte times_required = 2;          //The numbers of time the state has to be stable
} sensor_type;
#if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS == 2
  sensor_type sensors[32]; // Two control board in use
  byte sensors_zone_num = 6;
#elif defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS == 3
  sensor_type sensors[48]; // Two control board in use
  byte sensors_zone_num = 9;
#elif defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 4
  sensor_type sensors[64]; // Two control board in use
  byte sensors_zone_num = 12;
#else
  sensor_type sensors[16]; // Only one control board in use
  byte sensors_zone_num = 3;
#endif
byte gpio_max_read = 15;    // MAX number of indexes the sensor GPIO function should read.  Must be 15, 31, etc.
typedef struct {
  bool current = false;             //The currently read sensor from the MCP
  bool last = false;                //The last read sensor from the MCP
  bool confirmed = false;           //The state that will be processed for this sesnor
  byte times = 0;                   //The numbers of time the state has been stable from the MCP to help debounce the buttons
  byte times_required = 3;          //The numbers of time the state has to be stable
} gpio_type;

gpio_type gpio_button_green;
gpio_type gpio_button_blue;
gpio_type gpio_button_black;
gpio_type gpio_button_yellow;

bool gpio_debug = false;
int gpio_task_time = 50;
unsigned long gpio_task_time_start, gpio_task_time_stop, gpio_task_time_ran, gpio_task_time_max; //Track the time each function takes to run

bool motor_debug = false;
int motor_task_time = 500;
unsigned long motor_task_time_start, motor_task_time_stop, motor_task_time_ran, motor_task_time_max; //Track the time each function takes to run
bool motor_force_state = true;      //used to forcethe do_motor_control() function to set the blower state, should be set to true for first boot
volatile bool motor_logic_state = false;     //used by the run_blower_control() to set the blower state
volatile bool motor_sent_state = false;       //used by the do_motor_control() to set the blower state

bool motor_rf = false;              //if the motor needs to send an RF code out to start/stop the motor
bool motor_f2 = false;              //if the motor is controlled via Function Relay 2
bool motor_ir = false;              //if the motor needs to send an IR code out to start/stop the motorbool motor_f2 = false;


int MCP_task_time = 10000;
unsigned long MCP_task_time_start, MCP_task_time_stop, MCP_task_time_ran, MCP_task_time_max; //Track the time each function takes to run
bool MCP_debug = false;
bool MCP_online_20 = false;
#if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 2
  bool MCP_online_21 = false;
  bool MCP_enabled_21 = false;
#endif
#if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 3
  bool MCP_online_22 = false;
  bool MCP_enabled_22 = false;
#endif
#if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 4
  bool MCP_online_23 = false;
  bool MCP_enabled_23 = false;
#endif

bool require_green = true;          //Required to press the green button an a safty stop of the motor
volatile bool master_stop = false;
volatile bool master_blower_on = false;
volatile bool master_blower_off = false;
volatile bool master_error = false;
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
