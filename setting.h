

#ifndef BLOWERCONTROLLER_SETTINGS_H
#define BLOWERCONTROLLER_SETTINGS_H
#define BLOWERCONTROLLER_DEBUG

//Set the number of control boards in the system. Only 1 is supported at this time
	// 1 would give you 15 inputs 
	// 2 would give you 30 inputs
#define BLOWER_CONTROL_BOARDS 1

#define BLOWER_CONTROL_WIFI

// Update time from NTP server every 5 hours
#define NTP_UPDATE_INTERVAL_SEC 6*3600
//#define NTP_UPDATE_INTERVAL_SEC 30

// Maximum of 3 servers
#define NTP_SERVERS "us.pool.ntp.org", "pool.ntp.org", "time.nist.gov"

short timezone = -5; // US Eastern Time Zone

//US Eastern Time Zone (New York, Boston)


// Define the default setting for each setting

#endif /* SETTINGS_H */
