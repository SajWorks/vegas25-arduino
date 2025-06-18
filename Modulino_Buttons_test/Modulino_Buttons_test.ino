/*
 * Modulino Buttons - Basic
 *
 * This example code is in the public domain. 
 * Copyright (c) 2025 Arduino
 * SPDX-License-Identifier: MPL-2.0
 */

#include <Modulino.h>

// Create a ModulinoButtons object
ModulinoButtons buttons;

bool button_a = true;
bool button_b = true;
bool button_c = true;

void setup() {
  Serial.begin(9600);
  // Initialize Modulino I2C communication
  Modulino.begin();
  // Detect and connect to buttons module
  buttons.begin();
  // Turn on the LEDs above buttons A, B, and C
  buttons.setLeds(true, true, true);
}

void loop() {
  // Check for new button events, returns true when button state changes
  if (buttons.update()) {
    // You can use either index (0=A, 1=B, 2=C) or letter ('A', 'B', 'C') to check buttons
    // Below we use the letter-based method for better readability

    if (buttons.isPressed(0)) {
      Serial.println("Button A pressed!");

    } else if (buttons.isPressed(1)) {
      Serial.println("Button B pressed!");

    } else if (buttons.isPressed(2)) {
      Serial.println("Button C pressed!");
     
    }

    // Update the LEDs above buttons, depending on the variables value
    buttons.setLeds(button_a, button_b, button_c);
  }
}