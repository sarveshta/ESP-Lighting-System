#include "commands.h"
String commandArgs[8];
String globalMessageID;
TaskHandle_t currentTaskHandle = NULL; // Handle for the active task

void startCommandTask(void (*taskFunction)(void *)) {
    // If an existing task is running, delete it
    if (currentTaskHandle != NULL) {
        vTaskDelete(currentTaskHandle);
        currentTaskHandle = NULL;
    }
    // Create a new task
    xTaskCreatePinnedToCore(taskFunction, "Command Task", 4096, NULL, 1, &currentTaskHandle, 1);
}

//All the recognised commands
void runCommand(String commandContent, String messageID)
{
    globalMessageID = messageID;
    commandContent.toLowerCase();
    String commandName = commandContent.substring(1, commandContent.indexOf(' '));

    // Reset commandArgs to empty strings
    for (int i = 0; i < 8; i++) {
        commandArgs[i] = "";
    }

    // Parse command arguments dynamically
    int currentIndex = commandContent.indexOf(' ') + 1;
    for (int i = 0; i < 8; i++) {
        int nextSpace = commandContent.indexOf(' ', currentIndex);
        if (nextSpace == -1) {
            commandArgs[i] = commandContent.substring(currentIndex);
            break;
        }
        commandArgs[i] = commandContent.substring(currentIndex, nextSpace);
        currentIndex = nextSpace + 1;
    }


    Serial.println("Running Command: " + commandName);

    if(commandName == "ping")
    {
        pingCommand();
    }
    else if (commandName == "ledblink")
    {
        acknowledgeCommand();
        startCommandTask(blink);
    }
    else if (commandName == "buzzer")
    {
        int duration = commandArgs[0].toInt();
        int frequency = commandArgs[1].toInt();

        if(duration >= 0 && duration <= 10 && frequency >= 0 && frequency <= 255) //Input validation
        {
            acknowledgeCommand();
            startCommandTask(buzzer);
        }
        else
        {
            replyToMessage("Duration too long or frequency out of bounds", messageID);
            return;
        }
    }
    else if (commandName == "theaterchase")
    {
        acknowledgeCommand();
        startCommandTask(theaterChase);
    }
    else if (commandName == "warning") {
        warningLight(commandArgs[0].toInt());
        
    }
    else if (commandName == "off") {
        clear();
    }
    else //If the command is not recognised - Reacts with a red X
    {
        unknownCommand(globalMessageID);
    }

}

void pingCommand()
{
    replyToMessage("Pong", globalMessageID); //Respondes with "Pong"
}

void unknownCommand()
{
    Serial.println("Unknown Command: " + globalMessageID);
    addReaction("%E2%9D%8C", globalMessageID); //React with red X

}

void acknowledgeCommand()
{
    addReaction("%E2%9C%85", globalMessageID); //React with green checkmark
}

void ledBlinkCommand()
{
}

void turnOnBuzzerCommand()
{
}