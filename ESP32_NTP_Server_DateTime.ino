#include <WiFi.h>
#include "time.h"

const char* ssid       = "YOUR_SSID";   //Replace it with your wifi SSID
const char* password   = "YOUR_PASS";   //Replace it with your wifi Password

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;       //Set UTC Offset of your time zone i.e For UTC -5.00 : -5 * 60 * 60 = -18000
const int   daylightOffset_sec = 3600;  //Set Daylight Offset, 3600 for daylight saving , 0 for none.

void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

void setup()
{
  Serial.begin(115200);
  
  //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println(" CONNECTED");
  
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
//  WiFi.mode(WIFI_OFF);
}

void loop()
{
  delay(1000);
  printLocalTime();
}
