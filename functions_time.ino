#ifdef BLOWER_CONTROL_WIFI
#ifndef BLOWERCONTROLLER_FUNCTIONS_TIME_H
#define BLOWERCONTROLLER_FUNCTIONS_TIME_H
String returnDateTime() {
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
  return String(dateTime);
}
#endif
#endif
