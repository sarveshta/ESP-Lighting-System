#ifndef NEOPIXEL_H
#define NEOPIXEL_H

#include <Adafruit_NeoPixel.h>
#include "config.h"

void chase(uint32_t c);
void theaterChase(int red, int blue, int green, int wait);
void rainbow(int wait);
void warningLight(int stepDelay);

#endif