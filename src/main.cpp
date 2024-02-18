#include "network.h"

using namespace websockets;
WebsocketsClient client;

void onMessage(WebsocketsMessage message) {
    Serial.print("Got Message: ");
    Serial.println(message.data());

}

void onEventsCallback(WebsocketsEvent event, String data) {
    if(event == WebsocketsEvent::ConnectionOpened) {
        Serial.println("Connnection Opened");
        // Construct the authentication payload
        DynamicJsonDocument doc(1024);
        JsonObject d = doc.createNestedObject("d");
        doc["op"] = 2; // Opcode for IDENTIFY
        d["token"] = DISCORD_BOT_TOKEN;
        d["intents"] = 513; // Intents for GUILDS and GUILD_MESSAGES
        JsonObject properties = d.createNestedObject("properties");
        properties["$os"] = "linux";
        properties["$browser"] = "my_esp32_bot";
        properties["$device"] = "esp32";

        String payload;
        serializeJson(doc, payload);
        client.send(payload);
    } 
    else if(event == WebsocketsEvent::ConnectionClosed) {
        Serial.println("Connnection Closed");
    }
}

void setup() {
  Serial.begin(115200);
  connectToWifi();

  client.onMessage(onMessage);
  client.onEvent(onEventsCallback);

  // Connect to Discord Gateway
  client.connect("wss://gateway.discord.gg/?v=9&encoding=json");

}

void loop() {
  client.poll();
}