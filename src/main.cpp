#include "network.h"

uint64_t previousMessageID = 0;

// Number of previous commands to fetch
const int featchPreviousCommands = 10;

void setup() {
  Serial.begin(115200);
  connectToWifi();
  setCurrentTime();
  initPreviousMessage(&previousMessageID);
}

void loop() {

  String commands[featchPreviousCommands] = {};
  if(getCommands(&commands[0], &previousMessageID, featchPreviousCommands))
  {
    for(int i = 0; i < featchPreviousCommands; i++)
    {
      if(commands[i] != "")
      {
        Serial.println(commands[i]);
      }
    }
  }
  delay(10000); // Poll every 10 seconds
}
