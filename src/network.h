#ifndef NETWORK_H
#define NETWORK_H

#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <time.h>

#include "config.h"
#include "commands.h"


//Structure to store message and messageID together
struct Message {
  String content;
  String messageID;
};

void connectToWifi();
void setCurrentTime();
void initPreviousMessage(uint64_t* previousMessageID);
bool getCommands(struct Message* commands, uint64_t* previousMessageID, int featchPreviousCommands);
void runCommands(struct Message* commands, int numberOfCommands);
void replyToMessage(String response, String messageID);
void addReaction(String emoji, String messageID);

#endif