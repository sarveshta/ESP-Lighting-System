#ifndef NETWORK_H
#define NETWORK_H

#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <time.h>

#include "config.h"

void connectToWifi();
void setCurrentTime();
void initPreviousMessage(uint64_t* previousMessageID);
bool getCommands(String* commands, uint64_t* previousMessageID, int featchPreviousCommands);

#endif