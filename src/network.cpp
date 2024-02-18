#include "network.h"

// Connect to the WiFi network
void connectToWifi() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }
    Serial.println("Connected to the WiFi network");
  }

//Gets current timestamp using SNTP
uint64_t getCurrentTimestamp()
{
    //Check if the device is connected to the WiFi network
    if(WiFi.status() == WL_CONNECTED)
    {
        configTime(0, 0, "pool.ntp.org", "time.nist.gov");
        time_t now = time(nullptr);
        int timeOut = 0;
        while (now < 24 * 3600) {
            Serial.println("Waiting for time...");
            delay(500);
            now = time(nullptr);
            if(timeOut > 10)
            {
                Serial.println("Failed to get time");
                return 0;
            }
            timeOut++;
        }
        return now;
    }
}