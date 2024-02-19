#ifndef COMMANDS_H
#define COMMANDS_H

#include "network.h"

void runCommand(String commandContent, String messageID);

void pingCommand(String messageID);
void unknownCommand(String messageID);
void acknowledgeCommand(String messageID);
void ledBlinkCommand(String messageID, String duration);
void turnOnBuzzerCommand(String messageID, String duration, String frequency, String pulse);

#endif
