#include "miscellaneous_commands.h"
#include "commands.h"

void blink(void* parameter)
{
        pinMode(2, OUTPUT);
        digitalWrite(2, HIGH);
        delay(3000);
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
            delay(500);
            analogWrite(4,0);
            delay(500);
        }
    }
    else
    {
        analogWrite(4, frequency);
        delay(duration * 1000);
        analogWrite(4,0);
    }

}