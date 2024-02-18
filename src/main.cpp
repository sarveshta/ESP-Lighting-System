#include "network.h"

void setup() {
  Serial.begin(115200);
  connectToWifi();
  setCurrentTime();
}

void loop() {
  uint64_t messageTime = discordToUnix(1208708398661640212);
  Serial.println(time(nullptr));
  Serial.println(timeWithinMinute(time(nullptr), messageTime));

  delay(10000); // Poll every 10 seconds
}
