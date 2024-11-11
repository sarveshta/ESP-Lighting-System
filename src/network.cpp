#include "network.h"


// Connect to the WiFi network
void connectToWifi() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to the WiFi network");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to the WiFi network");
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
    Serial.print("Waiting for the current time");
    while (now < 24 * 3600) {
        Serial.print(".");
        delay(500);
        now = time(nullptr);
        if (timeOut++ > 20) { // Increment timeout here
            Serial.println("\nFailed to get time");
            return;
        }
    }
    Serial.print("\nCurrent time: ");
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
        http.setTimeout(TIMEOUT_DURATION);

        int httpCode = http.GET();
        if (httpCode > 0) {
            String payload = http.getString();
            JsonDocument doc;
            deserializeJson(doc, payload);
            *previousMessageID = doc[0]["id"].as<uint64_t>();
            Serial.println("Previous message fetched and has ID: " + String(*previousMessageID));

        } else {
            Serial.println("Error on HTTP request");
        }

        http.end(); 
    }
}

//Gets previous commands from the channel after the previousMessageID
bool getCommands(struct Message* commands, uint64_t* previousMessageID, int featchPreviousCommands)
{
    if(WiFi.status() == WL_CONNECTED)
    {   
        Serial.println("Fetching previous commands...");
        HTTPClient http;
        http.begin("https://discord.com/api/v9/channels/" + String(DISCORD_CHANNEL_ID) + "/messages?after=" + String(*previousMessageID) + "&limit=" + String(featchPreviousCommands));
        http.addHeader("Authorization", "Bot " + String(DISCORD_BOT_TOKEN));
        http.setTimeout(TIMEOUT_DURATION);

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
                    commands[i].messageID = array[i].as<JsonObject>()["id"].as<String>();
                    commands[i].content = array[i].as<JsonObject>()["content"].as<String>();
                    Serial.println("Command: " + commands[i].content + " ID: " + commands[i].messageID);
                } 
            }
            Serial.println("Previous commands fetched");
            if(array.size() > 0)
            {
                *previousMessageID = array[0].as<JsonObject>()["id"].as<uint64_t>();
                return true;
            }

        } else {
            Serial.println("Error on HTTP request");
            return false;
        }

        http.end(); 
    }
    return false;
}

void replyToMessage(String response, String messageID)
{
    if(WiFi.status() == WL_CONNECTED)
    {
        Serial.println("Replying to message...");
        HTTPClient http;
        http.begin("https://discord.com/api/v9/channels/" + String(DISCORD_CHANNEL_ID) + "/messages");
        http.addHeader("Authorization", "Bot " + String(DISCORD_BOT_TOKEN));
        http.addHeader("Content-Type", "application/json");
        http.setTimeout(TIMEOUT_DURATION);

        String payload = "{\"content\":\"" + response + "\",\"message_reference\":{\"message_id\":\"" + messageID + "\"}}";
        int httpCode = http.POST(payload);

        if (httpCode > 0) {
            Serial.println("Reply sent");
        } else {
            Serial.println("Error on HTTP request");
        }

        http.end(); 
    }
}

void addReaction(String emoji, String messageID)
{
    if(WiFi.status() == WL_CONNECTED)
    {
        Serial.println("Adding reaction...");
        HTTPClient http;
        http.begin("https://discord.com/api/v9/channels/" + String(DISCORD_CHANNEL_ID) + "/messages/" + messageID + "/reactions/" + emoji + "/%40me");
        http.addHeader("Authorization", "Bot " + String(DISCORD_BOT_TOKEN));
        http.setTimeout(TIMEOUT_DURATION);
        int httpCode = http.PUT("{}");
        if (httpCode > 0) {
            Serial.println("Reaction added");
        } else {
            Serial.println("Error on HTTP request");
        }

        http.end(); 
    }
}

void runCommands(struct Message* commands, int numberOfCommands)
{
    //Runs all commands in reverse order (aka chronological order)
    for(int i = numberOfCommands; i >= 0; i--)
    {
        if(commands[i].content[0] == COMMAND_PREFIX)
        {
            runCommand(commands[i].content, commands[i].messageID);
        }
    }
}

