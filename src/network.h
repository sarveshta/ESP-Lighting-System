#ifndef NETWORK_H
#define NETWORK_H

#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <time.h>

#include "config.h"

//Discord EPOCH starts on 2015-01-01
#define DISCORD_EPOCH 1420070400000ULL

void connectToWifi();
void setCurrentTime();
uint64_t discordToUnix(uint64_t snowflake);
bool timeWithinMinute(uint64_t currentTime, uint64_t messageTime);

#endif