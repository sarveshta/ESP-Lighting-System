#include "commands.h"

//All the recognised commands
void runCommand(String commandContent, String messageID)
{
    commandContent.toLowerCase();
    String commandName = commandContent.substring(1, commandContent.indexOf(' '));

    String commandArgs[8] = {
        commandContent.substring(commandContent.indexOf(' ') + 1, commandContent.indexOf(' ', commandContent.indexOf(' ') + 1)),
        commandContent.substring(commandContent.indexOf(' ', commandContent.indexOf(' ') + 1) + 1, commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ') + 1) + 1)),
        commandContent.substring(commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ') + 1) + 1) + 1, commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ') + 1) + 1) + 1)),
        commandContent.substring(commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ') + 1) + 1) + 1) + 1, commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ') + 1) + 1) + 1) + 1)),
        commandContent.substring(commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ') + 1) + 1) + 1) + 1) + 1) + 1, commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ') + 1) + 1) + 1) + 1) + 1) + 1)),
        commandContent.substring(commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ') + 1) + 1) + 1) + 1) + 1) + 1) + 1) + 1, commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ') + 1) + 1) + 1) + 1) + 1) + 1) + 1) + 1)),
        commandContent.substring(commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ') + 1) + 1) + 1) + 1) + 1) + 1) + 1) + 1) + 1) + 1, commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ') + 1) + 1) + 1) + 1) + 1) + 1) + 1) + 1) + 1) + 1)),
        commandContent.substring(commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ', commandContent.indexOf(' ') + 1) + 1) + 1) + 1) + 1) + 1) + 1) + 1) + 1) + 1) + 1) + 1, commandContent.length())
    };


    Serial.println("Running Command: " + commandName);

    if(commandName == "ping")
    {
        pingCommand(messageID);
    }
    else if (commandName == "ledblink")
    {
        ledBlinkCommand(messageID, commandArgs[0]);
    }
    else if (commandName == "buzzer")
    {
        turnOnBuzzerCommand(messageID, commandArgs[0],commandArgs[1],commandArgs[2]);
    }
    else if (commandName = "theaterchase")
    {
        theaterChase(commandArgs[0].toInt(), commandArgs[1].toInt(), commandArgs[2].toInt(), commandArgs[3].toInt());
    }
    else if (commandName = "warning") {
        warning(commandArgs[0].toInt());
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

void turnOnBuzzerCommand(String messageID, String duration, String frequency, String pulse)
{
    if(duration.toInt() >= 0 && duration.toInt() <= 10 && frequency.toInt() >= 0 && frequency.toInt() <= 255) //Input validation
    {
        pulse.toLowerCase();
        pinMode(4, OUTPUT);
        if(pulse == "true" || pulse == "t")
        {
            for(int i = 0; i < duration.toInt(); i++)
            {
                analogWrite(4, frequency.toInt());
                delay(500);
                analogWrite(4,0);
                delay(500);
            }
        }
        else
        {
            analogWrite(4, frequency.toInt());
            delay(duration.toInt() * 1000);
            analogWrite(4,0);
        }
    }
    else
    {
        replyToMessage("Duration too long or frequency out of bounds", messageID);
        return;
    }
}