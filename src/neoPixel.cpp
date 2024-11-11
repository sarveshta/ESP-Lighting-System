#include "neoPixel.h"
#include "commands.h"

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void chase(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels()+4; i++) {
      strip.setPixelColor(i  , c); // Draw new pixel
      strip.setPixelColor(i-4, 0); // Erase pixel a few steps back
      strip.show();
      delay(25);
  }
}

void theaterChase(void* parameter) {
  int red = commandArgs[0].toInt();
  int blue = commandArgs[1].toInt();
  int green = commandArgs[2].toInt();
  int wait = commandArgs[3].toInt();
  uint32_t color = strip.Color(red, blue, green, 50);
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      vTaskDelay(wait / portTICK_PERIOD_MS);  // Pause for a moment using vTask
    }
  }
}

void rainbow(void* parameter) {
  int wait = commandArgs[0].toInt();
  // Hue of first pixel runs 3 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 3*65536. Adding 256 to firstPixelHue each time
  // means we'll make 3*65536/256 = 768 passes through this outer loop:
  for(long firstPixelHue = 0; firstPixelHue < 3*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    vTaskDelay(wait / portTICK_PERIOD_MS);  // Pause for a moment
  }
}

void warningLight(void* parameter) {
  int maxBrightness = commandArgs[0].toInt();
  int stepDelay = 10;
  // Gradually turn on every other LED to full red brightness while the others fade to blue and then vice versa.
  strip.clear();
  while (true) {
    // Gradually increase red brightness and decrease blue brightness
    for (int brightness = 0; brightness <= maxBrightness; brightness++) {
      for (int i = 0; i < strip.numPixels(); i++) {
        if (i % 2 == 0) { // Only every other LED
          strip.setPixelColor(i, strip.Color(brightness, 0, maxBrightness - brightness)); // Gradually increasing red, decreasing blue
        } else {
          strip.setPixelColor(i, strip.Color(maxBrightness - brightness, 0, brightness)); // Gradually increasing blue, decreasing red
        }
      }
      strip.show(); // Update strip with new contents
      vTaskDelay(stepDelay / portTICK_PERIOD_MS); // Delay between brightness steps
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    // Gradually decrease red brightness and increase blue brightness
    for (int brightness = maxBrightness; brightness >= 0; brightness--) {
      for (int i = 0; i < strip.numPixels(); i++) {
        if (i % 2 == 0) { // Only every other LED
          strip.setPixelColor(i, strip.Color(brightness, 0, maxBrightness - brightness)); // Gradually decreasing red, increasing blue
        } else {
          strip.setPixelColor(i, strip.Color(maxBrightness - brightness, 0, brightness)); // Gradually decreasing blue, decreasing red
        }
      }
      strip.show(); // Update strip with new contents
      vTaskDelay(stepDelay / portTICK_PERIOD_MS); // Delay between brightness steps
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void clear(void* parameter){
  strip.clear();
  strip.show();
}


