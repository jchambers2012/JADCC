#ifndef BLOWERCONTROLLER_SETTINGS_H
#define BLOWERCONTROLLER_SETTINGS_H
#define BLOWERCONTROLLER_DEBUG

#define AC_DEBUG

//Set the number of control boards in the system. Only 1 is supported at this time
	// 1 would give you 15 inputs 
	// 2 would give you 30 inputs
#define BLOWER_CONTROL_BOARDS 1

// The mDNS responder would be BlowerControler.local
#define BLOWER_CONTROL_MDNS "BlowerControler"

//Allow the firmware to attempt to formate the SPIFFS if it has trouble mouting the FS
// #define BLOWERCONTROLLER_AUTO_FORMAT

//Enable the WiFi Subsystem for remote control, flashing, and status monitoring 
#define BLOWER_CONTROL_WIFI

// Update time from NTP server every 6 hours
#define NTP_UPDATE_INTERVAL_SEC 6*3600

// Maximum of 3 servers
#define NTP_SERVERS "us.pool.ntp.org", "pool.ntp.org", "time.nist.gov"

short timezone = -5; // US Eastern Time Zone

//US Eastern Time Zone (New York, Boston)


// Define the default setting for each setting





// Debug output destination can be defined externally with DC_DEBUG_PORT
// Lovingly stolen for PaguBuilder: @file PageBuilder.h @author hieromon@gmail.com @copyright  MIT license.
#ifndef DC_DEBUG_PORT
#define DC_DEBUG_PORT Serial
#endif // !DC_DEBUG_PORT
#ifdef BLOWERCONTROLLER_DEBUG
#define DC_DBG_DUMB(...) do {PB_DEBUG_PORT.printf( __VA_ARGS__ );} while (0)
#define DC_DBG(...) do {PB_DEBUG_PORT.print("[DC] "); PB_DEBUG_PORT.printf( __VA_ARGS__ );} while (0)
#else
#define DC_DBG_DUMB(...)
#define DC_DBG(...)
#endif // !DC_DEBUG




#endif /* SETTINGS_H */
