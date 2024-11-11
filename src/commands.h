#ifndef COMMANDS_H
#define COMMANDS_H

#include "network.h"
#include "neoPixel.h"

extern String commandArgs[8]; //Array to store command arguments for second core to use
extern String messageID;

void runCommand(String commandContent, String messageID);

void pingCommand(String messageID);
void unknownCommand(String messageID);
void acknowledgeCommand(String messageID);
void ledBlinkCommand(String messageID, String duration);
void turnOnBuzzerCommand(String messageID, String duration, String frequency, String pulse);

#endif
