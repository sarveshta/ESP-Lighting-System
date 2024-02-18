#include "network.h"

uint64_t previousMessageID = 0;

void setup() {
  Serial.begin(115200);
  connectToWifi();
  setCurrentTime();
  initPreviousMessage(&previousMessageID);
}

void loop() {
  initPreviousMessage(&previousMessageID);
  delay(10000); // Poll every 10 seconds
}
