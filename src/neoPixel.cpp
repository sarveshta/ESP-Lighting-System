// // Simple NeoPixel test.  Lights just a few pixels at a time so a
// // 1m strip can safely be powered from Arduino 5V pin.  Arduino
// // may nonetheless hiccup when LEDs are first connected and not
// // accept code.  So upload code first, unplug USB, connect pixels
// // to GND FIRST, then +5V and digital pin 6, then re-plug USB.
// // A working strip will show a few pixels moving down the line,
// // cycling between red, green and blue.  If you get no response,
// // might be connected to wrong end of strip (the end wires, if
// // any, are no indication -- look instead for the data direction
// // arrows printed on the strip).
// #include "neoPixel.h"

// #define PIN 6
// #define N_LEDS 139

// Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

// void setup() {
//   strip.begin();
//   strip.setBrightness(100);
// }

// void loop() {
//   //chase(strip.Color(255, 0, 0)); // Red
//   //chase(strip.Color(0, 255, 0)); // Green
//   //chase(strip.Color(0, 0, 255)); // Blue
//   /*strip.clear();
//   strip.show();
//   delay(1000);
//   strip.fill(strip.Color(50, 50, 255), 0, N_LEDS-1);
//   strip.show();
//   delay(1000);*/
//   theaterChase(strip.Color(100, 100, 100), 50);

//   rainbow(10);
  
// }

// static void chase(uint32_t c) {
//   for(uint16_t i=0; i<strip.numPixels()+4; i++) {
//       strip.setPixelColor(i  , c); // Draw new pixel
//       strip.setPixelColor(i-4, 0); // Erase pixel a few steps back
//       strip.show();
//       delay(25);
//   }
// }

// void theaterChase(uint32_t color, int wait) {
//   for(int a=0; a<10; a++) {  // Repeat 10 times...
//     for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
//       strip.clear();         //   Set all pixels in RAM to 0 (off)
//       // 'c' counts up from 'b' to end of strip in steps of 3...
//       for(int c=b; c<strip.numPixels(); c += 3) {
//         strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
//       }
//       strip.show(); // Update strip with new contents
//       delay(wait);  // Pause for a moment
//     }
//   }
// }

// void rainbow(int wait) {
//   // Hue of first pixel runs 3 complete loops through the color wheel.
//   // Color wheel has a range of 65536 but it's OK if we roll over, so
//   // just count from 0 to 3*65536. Adding 256 to firstPixelHue each time
//   // means we'll make 3*65536/256 = 768 passes through this outer loop:
//   for(long firstPixelHue = 0; firstPixelHue < 3*65536; firstPixelHue += 256) {
//     for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
//       // Offset pixel hue by an amount to make one full revolution of the
//       // color wheel (range of 65536) along the length of the strip
//       // (strip.numPixels() steps):
//       int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
//       // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
//       // optionally add saturation and value (brightness) (each 0 to 255).
//       // Here we're using just the single-argument hue variant. The result
//       // is passed through strip.gamma32() to provide 'truer' colors
//       // before assigning to each pixel:
//       strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
//     }
//     strip.show(); // Update strip with new contents
//     delay(wait);  // Pause for a moment
//   }
// }