#ifndef COMMANDS_H
#define COMMANDS_H

#include "network.h"
#include "neoPixel.h"
#include "miscellaneous_commands.h"

extern String commandArgs[8]; //Array to store command arguments for second core to use
extern String globalMessageID;
extern TaskHandle_t currentTaskHandle; // Handle for the active task

void runCommand(String commandContent, String messageID);

void pingCommand();
void unknownCommand();
void acknowledgeCommand();
void ledBlinkCommand();
void turnOnBuzzerCommand();

#endif
