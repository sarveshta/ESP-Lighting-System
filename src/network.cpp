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

//Initializes the previousMessageID with the last message sent in the channel; used when device is reset
void initPreviousMessage(uint64_t* previousMessageID) {

    if(WiFi.status() == WL_CONNECTED)
    {
        HTTPClient http;
        http.begin("https://discord.com/api/v9/channels/" + String(DISCORD_CHANNEL_ID) + "/messages?0=/");
        http.addHeader("Authorization", "Bot " + String(DISCORD_BOT_TOKEN));

        int httpCode = http.GET();

        if (httpCode > 0) {
            String payload = http.getString();
            JsonDocument doc;
            deserializeJson(doc, payload);
            *previousMessageID = doc[0]["id"].as<uint64_t>();

            Serial.println(httpCode);
            Serial.println(previousMessageID[0]);
        } else {
            Serial.println("Error on HTTP request");
        }

        http.end(); 
    }
}