#include "commands.h"

//All the recognised commands
void runCommand(String commandContent, String messageID)
{
    commandContent.toLowerCase();
    String commandName = commandContent.substring(1, commandContent.indexOf(' '));

    String commandArgs[4] = {commandContent.substring(commandContent.indexOf(' ') + 1, commandContent.indexOf(' ', commandContent.indexOf(' ') + 1)),
                            commandContent.substring(commandContent.indexOf(' ', commandContent.indexOf(' ') + 1) + 1, commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ') + 1) + 1)),
                            commandContent.substring(commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ') + 1) + 1) + 1, commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ') + 1) + 1) + 1)),
                            commandContent.substring(commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ') + 1) + 1) + 1) + 1, commandContent.length())};


    Serial.println("Running Command: " + commandName);

    if(commandName == "ping")
    {
        pingCommand(messageID);
    }
    else if (commandName == "ledblink")
    {
        ledBlinkCommand(messageID, commandArgs[0]);
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

void ledBlinkCommand(String messageID, String duration)
{
    if(duration.toInt() > 0 && duration.toInt() < 10) //Input validation
    {
        acknowledgeCommand(messageID);
        pinMode(2, OUTPUT);
        digitalWrite(2, HIGH);
        delay(duration.toInt() * 1000);
        digitalWrite(2, LOW);

    }
    else
    {
        replyToMessage("Duration too long", messageID);
        return;
    }
}