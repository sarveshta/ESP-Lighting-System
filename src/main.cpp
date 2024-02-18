#include <ArduinoWebsockets.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include "config.h" 

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;
const char* websockets_server_host = "gateway.discord.gg"; 
const uint16_t websockets_server_port = 443; 

using namespace websockets;

WebsocketsClient client;
unsigned long lastHeartbeat = 0;
int heartbeatInterval = 0;
bool isConnected = false;

void sendHeartbeat() {
    if (!isConnected) return; 

    DynamicJsonDocument doc(256);
    doc["op"] = 1; 
    doc["d"] = nullptr;

    String payload;
    serializeJson(doc, payload);
    client.send(payload);
    Serial.println("Heartbeat sent");
}

void onMessageCallback(WebsocketsMessage message) {
    Serial.print("Got Message: ");
    Serial.println(message.data());

    DynamicJsonDocument doc(1024);
    deserializeJson(doc, message.data());
    int op = doc["op"].as<int>();

    if(op == 10) { 
        Serial.println("Received Hello");
        heartbeatInterval = doc["d"]["heartbeat_interval"].as<int>();
        lastHeartbeat = millis();
        isConnected = true; 
        sendHeartbeat();
    } else if (op == 11) {
        Serial.println("Heartbeat acknowledged");
    }
}

void sendIdentify() {
    DynamicJsonDocument doc(1024);
    doc["op"] = 2; 
    doc["d"]["token"] = DISCORD_BOT_TOKEN;
    doc["d"]["intents"] = 513; 
    doc["d"]["properties"]["$os"] = "linux";
    doc["d"]["properties"]["$browser"] = "my_library";
    doc["d"]["properties"]["$device"] = "my_library";

    String payload;
    serializeJson(doc, payload);
    client.send(payload);
    Serial.println("Identify sent");
}

void setup() {
    Serial.begin(115200);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi");

    client.onMessage(onMessageCallback);

    if(client.connect(websockets_server_host, websockets_server_port, "/?v=9&encoding=json")) {
        Serial.println("Attempting to connect to Discord Gateway...");
        sendIdentify();
    } else {
        Serial.println("Connection to Discord Gateway failed!");
    }
}

void loop() {
    client.poll();

    if (isConnected && millis() - lastHeartbeat > heartbeatInterval) {
        sendHeartbeat();
        lastHeartbeat = millis();
    }
}
