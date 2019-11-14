#ifndef BLOWERCONTROLLER_VARIABLE_H
#define BLOWERCONTROLLER_VARIABLE_H


bool debug_debug = true;
bool lcd_debug = false;
bool gpio_debug = false;
bool MCP_debug = false;



#define BLOWER_VERSION "0.18 BETA"

Scheduler ts, cts; 

RCSwitch motorRF = RCSwitch();

bool shouldSaveConfig = false;    //flag for saving data

int debug_debug_task_time = 10000;  //how offen to refresh the Serial screen
unsigned long debug_debug_time, debug_debug_ran ; //Track the time each function takes to run
unsigned long debug_debug_times[10];
unsigned long system_loop_start,system_loop_total,system_loop_run,system_loop_max; //Track the time each function takes to run

int lcd_loop[10]=       {0,1,2 ,3,4,0,0,0,0,0};  //First 5 Screens. Screen 4 will start the control processes
byte lcd_loop_delay[10]={0,2,10,2,0,0,0,0,0,0};  //Will delay the LCD display from moving onto the next screen
byte lcd_loop_i = 5;
byte lcd_loop_c = 0;
byte lcd_loop_d = 0;
byte lcd_loop_delay_add = 1;
const byte lcd_loop_m = 5;
int lcd_sensor[10]={0,0,0,0,0,0,0,0,0};
byte lcd_sensor_i = 0;
byte lcd_sensor_c = 0;
const byte lcd_sensor_m = 5 ;
bool lcd_sensor_flip = false;
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
bool lcd_wifi = false;
//byte lcd_wifi_none[8] ={0b01010,0b00100,0b01010,0b00000,0b10001,0b10001,0b11111,0b01110};// Router with an x
byte lcd_wifi_none[8] = { 0b10100, 0b01000, 0b10100, 0b00001, 0b00011, 0b00111, 0b01111, 0b11111}; //Bars with an x
byte lcd_exclam_0_0[8] = {0,15,15,15,7,7,3,3};
byte lcd_exclam_0_1[8] = {0,30,30,30,28,28,24,24};
byte lcd_exclam_1_0[8] = {3,3,1,1,1,0,1,1};
byte lcd_exclam_1_1[8] = {24,24,16,16,16,0,16,16};

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
  unsigned long time_on = 0;        //The time the button was pressed
  unsigned long time_off = 1;       //The time the button was released
  unsigned long time_total = 0;     //Total time the button was held
  bool processed_h = false;         //set high once time_on is set
  bool processed_l = false;         //set high once time_off is set
} sensor_type;
#if defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS == 2
  #define BLOWER_CONTROL_MAX_SENSOR 32
  byte sensors_zone_num = 6;
#elif defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS == 3
  #define BLOWER_CONTROL_MAX_SENSOR 48
  byte sensors_zone_num = 9;
#elif defined(BLOWER_CONTROL_BOARDS) && BLOWER_CONTROL_BOARDS >= 4
  #define BLOWER_CONTROL_MAX_SENSOR 64
  byte sensors_zone_num = 12;
#else
  #define BLOWER_CONTROL_MAX_SENSOR 16
  byte sensors_zone_num = 3;
#endif
sensor_type sensors[BLOWER_CONTROL_MAX_SENSOR]; // Only one control board in use
byte gpio_max_read = 15;    // MAX number of indexes the sensor GPIO function should read.  Must be 15, 31, etc.
unsigned long gpio_last_read = 0;    // MAX number of indexes the sensor GPIO function should read.  Must be 15, 31, etc.
uint8_t gpio_last_reading_A = 0;    // MAX number of indexes the sensor GPIO function should read.  Must be 15, 31, etc.
uint8_t gpio_last_reading_B = 0;    // MAX number of indexes the sensor GPIO function should read.  Must be 15, 31, etc.
int gpio_last_address = 0;    // MAX number of indexes the sensor GPIO function should read.  Must be 15, 31, etc.
typedef struct {
  bool current = false;             //The currently read sensor from the MCP
  bool last = false;                //The last read sensor from the MCP
  bool confirmed = false;           //The state that will be processed for this sesnor
  byte times = 0;                   //The numbers of time the state has been stable from the MCP to help debounce the buttons
  byte times_required = 3;          //The numbers of time the state has to be stable
  unsigned long time_on = 0;        //The time the button was pressed
  unsigned long time_off = 1;       //The time the button was released
  unsigned long time_total = 0;     //Total time the button was held
  bool processed_h = false;         //set high once time_on is set
  bool processed_l = false;         //set high once time_off is set
} gpio_type;

gpio_type gpio_button_green;
gpio_type gpio_button_blue;
gpio_type gpio_button_black;
gpio_type gpio_button_yellow;

int gpio_task_time = 1000;

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

#ifdef BLOWER_CONTROL_WIFI

const String HTML_ONLINE = "<font color=\"green\">ACTIVE</font>";
const String HTML_ONLINE_M = "<font color=\"red\">MOTOR OFF</font>";
const String HTML_OFFLINE = "INACTIVE";
const String HTML_DISABLED = "<font color=\"gray\">Disabled</font>";

struct dstRule StartRule = {"EDT", Second, Sun, Mar, 2, 3600};    // Daylight time = UTC/GMT -4 hours
struct dstRule EndRule = {"EST", First, Sun, Nov, 2, 0};       // Standard time = UTC/GMT -5 hour

ESP8266WebServer  server;
AutoConnect portal(server);
AutoConnectConfig config;
AutoConnectAux  elementsAux;
AutoConnectAux  Timezone;
AutoConnectAux  saveAux;
typedef struct {
  const char* zone;
  const char* ntpServer;
  int8_t      tzoff;
} Timezone_t;

static const Timezone_t TZ[] = {
  { "Europe/London", "europe.pool.ntp.org", 0 },
  { "Europe/Berlin", "europe.pool.ntp.org", 1 },
  { "Europe/Helsinki", "europe.pool.ntp.org", 2 },
  { "Europe/Moscow", "europe.pool.ntp.org", 3 },
  { "Asia/Dubai", "asia.pool.ntp.org", 4 },
  { "Asia/Karachi", "asia.pool.ntp.org", 5 },
  { "Asia/Dhaka", "asia.pool.ntp.org", 6 },
  { "Asia/Jakarta", "asia.pool.ntp.org", 7 },
  { "Asia/Manila", "asia.pool.ntp.org", 8 },
  { "Asia/Tokyo", "asia.pool.ntp.org", 9 },
  { "Australia/Brisbane", "oceania.pool.ntp.org", 10 },
  { "Pacific/Noumea", "oceania.pool.ntp.org", 11 },
  { "Pacific/Auckland", "oceania.pool.ntp.org", 12 },
  { "Atlantic/Azores", "europe.pool.ntp.org", -1 },
  { "America/Noronha", "south-america.pool.ntp.org", -2 },
  { "America/Araguaina", "south-america.pool.ntp.org", -3 },
  { "America/Blanc-Sablon", "north-america.pool.ntp.org", -4},
  { "America/New_York", "north-america.pool.ntp.org", -5 },
  { "America/Chicago", "north-america.pool.ntp.org", -6 },
  { "America/Denver", "north-america.pool.ntp.org", -7 },
  { "America/Los_Angeles", "north-america.pool.ntp.org", -8 },
  { "America/Anchorage", "north-america.pool.ntp.org", -9 },
  { "Pacific/Honolulu", "north-america.pool.ntp.org", -10 },
  { "Pacific/Samoa", "oceania.pool.ntp.org", -11 }
};

bool wifi_enabled = false;
unsigned int ntp_localPort = 2390;      // local port to listen for UDP packets
IPAddress timeServerIP; // time.nist.gov NTP server address
const char* ntpServerName = "time.nist.gov";
const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message
byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets
WiFiUDP ntp_udp;
bool ntp_enabled = true;
bool ntp_synced = false;

Ticker ticker1;
int32_t tick;

// flag changed in the ticker function to start NTP Update
bool readyForNtpUpdate = false;

// Setup simpleDSTadjust Library rules
simpleDSTadjust dstAdjusted(StartRule, EndRule);

#endif



//FS
bool isFSMounted = false;
#define MOTOR_STOP        false
#define MOTOR_START       true
#define RELAY_F1          D5         
#define RELAY_F2          D3
#define RELAY_LED_RED     D6
#define RELAY_LED_GREEN   D4
#define GPIO_START        D7
#define GPIO_IR           D0
#define GPIO_B1           D8
#define GPIO_B2           A0
#define JSONVERSION       1

#endif /* VARIABLE_H */
