#include "commands.h"

//All the recognised commands
void runCommand(String commandContent, String messageID)
{
    String commandName = commandContent.substring(1, commandContent.indexOf(' '));
    commandName.toLowerCase();
    
    Serial.println("Running Command: " + commandName);

    if(commandName == "ping")
    {
        pingCommand(messageID);
    }
    else if (commandName == "ledBlink")
    {
        ledBlinkCommand(messageID);
    }
    else //If the command is not recognised - Reacts with a red X
    {
        unknownCommand(messageID);
    }

}

void pingCommand(String messageID)
{
    replyToMessage("Pong", messageID); //Respondes with "Pong"
}

void unknownCommand(String messageID)
{
    Serial.println("Unknown Command: " + messageID);
    addReaction("%E2%9D%8C", messageID); //React with red X

}

void acknowledgeCommand(String messageID)
{
    addReaction("%E2%9C%85", messageID); //React with green checkmark
}

void ledBlinkCommand(String messageID)
{
    acknowledgeCommand(messageID);
    pinMode(2, OUTPUT);
    digitalWrite(2, HIGH);
    delay(1000);
    digitalWrite(2, LOW);
}