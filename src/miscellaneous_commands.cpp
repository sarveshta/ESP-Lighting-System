#include "miscellaneous_commands.h"
#include "commands.h"

void blink(void* parameter)
{
        pinMode(2, OUTPUT);
        digitalWrite(2, HIGH);
        vTaskDelay(3000 / portTICK_PERIOD_MS);
        digitalWrite(2, LOW);

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
            analogWrite(4, frequency);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            analogWrite(4,0);
            vTaskDelay(500 / portTICK_PERIOD_MS);
        }
    }
    else
    {
        analogWrite(4, frequency);
        vTaskDelay(duration * 1000 / portTICK_PERIOD_MS);
        analogWrite(4,0);
    }

}