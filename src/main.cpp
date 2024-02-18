#include "network.h"

void setup() {
  connectToWifi();
}

void loop() {
  if(WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("https://discord.com/api/v9/channels/" + String(DISCORD_CHANNEL_ID) + "/messages");
    http.addHeader("Authorization", "Bot " + String(DISCORD_BOT_TOKEN));
    
    int httpCode = http.GET();
    
    if (httpCode > 0) { //Check for the returning code
        String payload = http.getString();
        Serial.println(httpCode);
        Serial.println(payload);
        // Parse JSON and extract message content here
    } else {
        Serial.println("Error on HTTP request");
    }

    http.end(); //Free the resources
  }

  delay(10000); // Poll every 10 seconds
}
