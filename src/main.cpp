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
  //Two dimensional array for commands, first column is the message ID and the second is the command
  Message messages[featchPreviousCommands];
  if(getCommands(&messages[0], &previousMessageID, featchPreviousCommands))
  {
    runCommands(&messages[0], featchPreviousCommands);
  }
  delay(5000); // Poll every 5! seconds
}
