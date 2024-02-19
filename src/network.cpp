#include "network.h"

// Connect to the WiFi network
void connectToWifi() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.println("Connecting to the WiFi network");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println(".");
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
    Serial.println("Waiting for the current time");
    while (now < 24 * 3600) {
        Serial.println(".");
        delay(500);
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
        Serial.println("Fetching previous message...");
        HTTPClient http;
        http.begin("https://discord.com/api/v9/channels/" + String(DISCORD_CHANNEL_ID) + "/messages?0=/limit=1");
        http.addHeader("Authorization", "Bot " + String(DISCORD_BOT_TOKEN));

        int httpCode = http.GET();

        if (httpCode > 0) {
            String payload = http.getString();
            JsonDocument doc;
            deserializeJson(doc, payload);
            *previousMessageID = doc[0]["id"].as<uint64_t>();

        } else {
            Serial.println("Error on HTTP request");
        }

        http.end(); 
    }
}

//Gets previous commands from the channel after the previousMessageID
bool getCommands(String* commands, uint64_t* previousMessageID, int featchPreviousCommands)
{
    if(WiFi.status() == WL_CONNECTED)
    {   
        Serial.println("Fetching previous commands...");
        HTTPClient http;
        http.begin("https://discord.com/api/v9/channels/" + String(DISCORD_CHANNEL_ID) + "/messages?after=" + String(*previousMessageID) + "&limit=" + String(featchPreviousCommands));
        http.addHeader("Authorization", "Bot " + String(DISCORD_BOT_TOKEN));

        int httpCode = http.GET();

        if (httpCode > 0) {
            String payload = http.getString();
            JsonDocument doc;
            deserializeJson(doc, payload);
            JsonArray array = doc.as<JsonArray>();

            for (int i = 0; i < array.size(); i++) {
                // Iterate through each element of the object
                if(array[i].as<JsonObject>()["content"].as<String>()[0] == '!')
                {
                    commands[i] = array[i].as<JsonObject>()["content"].as<String>();
                } 
            }
            Serial.println("Previous commands fetched");
            if(array.size() > 0)
            {
                *previousMessageID = array[array.size() - 1].as<JsonObject>()["id"].as<uint64_t>();
            }
            return true;

        } else {
            Serial.println("Error on HTTP request");
            return false;
        }

        http.end(); 
    }
    return false;
}