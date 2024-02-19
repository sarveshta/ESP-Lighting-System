#ifndef NETWORK_H
#define NETWORK_H

#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <time.h>

#include "config.h"

//Structure to store message and messageID together
struct Message {
  String content;
  String messageID;
};

void connectToWifi();
void setCurrentTime();
void initPreviousMessage(uint64_t* previousMessageID);
bool getCommands(struct Message* commands, uint64_t* previousMessageID, int featchPreviousCommands);

#endif