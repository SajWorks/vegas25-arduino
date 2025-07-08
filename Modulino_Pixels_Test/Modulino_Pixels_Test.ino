#include <Modulino.h>

ModulinoPixels leds;

void setup() {
  Modulino.begin(); // Initialize the Modulino library
  leds.begin();    // Initialize the Pixels Modulino
}

void loop() {
  // Example: Set all LEDs to a specific color
  for (int i = 0; i < 8; i++) {
    leds.set(i, GREEN, 10); // Set LED i to red, brightness 10%
  }
  leds.show(); // Display the color on the LEDs

  delay(1000); // Wait 1 second

  // Example: Clear all LEDs
  leds.clear();
  leds.show();

  delay(1000); // Wait 1 second
}
