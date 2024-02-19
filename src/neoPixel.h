#ifndef NEOPIXEL_H
#define NEOPIXEL_H

#include <Adafruit_NeoPixel.h>
#include "config.h"

void chase(uint32_t c);
void theaterChase(uint32_t color, int wait);
void rainbow(int wait);

#endif