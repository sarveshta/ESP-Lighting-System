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

//Gets current time from NTP servers
void setCurrentTime() {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi is not connected!");
        return;
    }
    
    configTime(0, 0, "time.google.com", "time.nist.gov"); // Use different NTP servers
    time_t now = time(nullptr);
    int timeOut = 0;
    while (now < 24 * 3600) {
        Serial.println("Waiting for time...");
        delay(1000);
        now = time(nullptr);
        if (timeOut++ > 20) { // Increment timeout here
            Serial.println("Failed to get time");
            return;
        }
    }
    Serial.print("Current time: ");
    Serial.println(time(nullptr));
}

//Converts Discord snowflake to Unix timestamp
uint64_t discordToUnix(uint64_t snowflake)
{
    printf("Unix timestamp: %llu\n", ((snowflake >> 22) + DISCORD_EPOCH)/1000);
    return ((snowflake >> 22) + DISCORD_EPOCH)/1000;
} 

//Checks if message was sent within the last minute
bool timeWithinMinute(uint64_t currentTime, uint64_t messageTime)
{
    return (currentTime - messageTime) < 60;
}

void getPreviousMessages() {

    if(WiFi.status() == WL_CONNECTED)
    {
        HTTPClient http;
        http.begin("https://discord.com/api/v9/channels/" + String(DISCORD_CHANNEL_ID) + "/messages");
        http.addHeader("Authorization", "Bot " + String(DISCORD_BOT_TOKEN));

        int httpCode = http.GET();

        if (httpCode > 0) {
            String payload = http.getString();
            Serial.println(httpCode);
            Serial.println(payload);
        } else {
            Serial.println("Error on HTTP request");
        }

        http.end(); 
    }
}