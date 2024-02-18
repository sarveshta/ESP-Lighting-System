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



// void getPreviousMessages(uint64_t messageID) {

//     if(WiFi.status() == WL_CONNECTED)
//     {
//         HTTPClient http;
//         http.begin("https://discord.com/api/v9/channels/" + String(DISCORD_CHANNEL_ID) + "/messages");
//         http.addHeader("Authorization", "Bot " + String(DISCORD_BOT_TOKEN));

//         int httpCode = http.GET();

//         if (httpCode > 0) {
//             String payload = http.getString();
//             Serial.println(httpCode);
//             Serial.println(payload);
//         } else {
//             Serial.println("Error on HTTP request");
//         }

//         http.end(); 
//     }
// }