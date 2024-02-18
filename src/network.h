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

#endif