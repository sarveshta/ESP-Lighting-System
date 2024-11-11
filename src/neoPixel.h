#ifndef NEOPIXEL_H
#define NEOPIXEL_H

#include <Adafruit_NeoPixel.h>
#include "config.h"

void chase(uint32_t c);
void theaterChase(void* parameters);
void rainbow(void* parameters);
void warningLight(void* parameters);
void clear(void* parameters);

#endif