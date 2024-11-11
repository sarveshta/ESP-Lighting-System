#include "miscellaneous_commands.h"
#include "commands.h"

void blink(void* parameter)
{
    pinMode(2, OUTPUT);
    digitalWrite(2, HIGH);
    vTaskDelay(3000 / portTICK_PERIOD_MS);
    digitalWrite(2, LOW);
    currentTaskHandle = NULL;
    vTaskDelete(NULL);

}

void buzzer(void* parameter)
{
    int duration = commandArgs[0].toInt();
    int frequency = commandArgs[1].toInt();
    String pulse = commandArgs[2];

    pulse.toLowerCase();
    pinMode(4, OUTPUT);
    if(pulse == "true" || pulse == "t")
    {
        for(int i = 0; i < duration; i++)
        {
            tone(4, frequency, 0);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            tone(4, frequency, 0);
            vTaskDelay(500 / portTICK_PERIOD_MS);
        }
    }
    else
    {
        tone(4, frequency, duration * 1000);
        vTaskDelay(duration * 1000 / portTICK_PERIOD_MS);
        tone(4, 0, duration * 1000);
    }
    currentTaskHandle = NULL;
    vTaskDelete(NULL);
    
}