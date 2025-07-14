#include <ArduinoGraphics.h>
#include <Arduino_HS300x.h>
#include <Arduino_LPS22HB.h>
#include <RTC.h>
#include <Arduino_LSM6DSOX.h>
#include <vl53l4cd_api.h>
#include <vl53l4cd_class.h>
#include <Modulino.h>
#include <Arduino_LED_Matrix.h>
#include <TextAnimation.h>

ModulinoPixels leds;
ArduinoLEDMatrix matrix;
ModulinoButtons buttons;
ModulinoBuzzer buzzer;

ModulinoColor YELLOW(255, 255, 0);
ModulinoColor ORANGE(255, 30, 0);

bool button_0 = true;
bool button_1 = true;
bool button_2 = true;

String inputBuffer = "";

// --- Async scroll variables ---
bool showColors = false;
String scrollText = "";
int scrollOffset = 0;
unsigned long lastScrollTime = 0;
const int scrollSpeed = 250;  // ms per scroll step

void setup() {
  Serial.begin(9600);
  Modulino.begin();
  buttons.begin();
  matrix.begin();
  buzzer.begin();
  leds.begin();
  buttons.setLeds(true, true, true);
}

void loop() {
  unsigned long currentMillis = millis();

  // --- Serial input (non-blocking) ---
  while (Serial.available()) {
    char ch = Serial.read();
    if (ch == '\n') {
      handleSerialInput(inputBuffer);
      inputBuffer = "";
    } else {
      inputBuffer += ch;
    }
  }

  // --- Button handling ---
  if (buttons.update()) {
    if (buttons.isPressed(0)) Serial.println("Button: 1");
    if (buttons.isPressed(1)) Serial.println("Button: 2");
    if (buttons.isPressed(2)) Serial.println("Button: 3");

    buttons.setLeds(button_0, button_1, button_2);
  }

  // --- Async LED Matrix Scrolling ---
  if (showColors && (currentMillis - lastScrollTime >= scrollSpeed)) {
    lastScrollTime = currentMillis;

    matrix.beginDraw();
    matrix.stroke(0xFFFFFF);  // Text color
    matrix.clear();           // Clear previous frame
    matrix.textFont(Font_4x6);
    matrix.textScrollSpeed(0);  // We control scroll manually

    int xPos = 12 - scrollOffset;         // Start from right edge
    matrix.beginText(xPos, 0, 0xFFFFFF);  // y=0 is safest
    matrix.print(scrollText);
    matrix.endText();

    matrix.endDraw();

    scrollOffset++;
    if (scrollOffset > scrollText.length() * 5) {
      scrollOffset = 0;  // Reset scroll when done
    }
  }
}

// --- Serial Command Handling ---
void handleSerialInput(String data) {
  if (data.startsWith("BUZZ:")) {
    int freq = data.substring(5).toInt();
    if (freq > 0) {
      buzzer.tone(freq, 1000);
    }
  }

  else if (data.startsWith("GUESS:")) {
    String guessColors = data.substring(6);
    Serial.println(guessColors);
    leds.set(0, getColorForString(guessColors.substring(0, 1)), 5);
    leds.set(1, getColorForString(guessColors.substring(0, 1)), 5);
    leds.set(2, getColorForString(guessColors.substring(1, 2)), 5);
    leds.set(3, getColorForString(guessColors.substring(1, 2)), 5);
    leds.set(4, getColorForString(guessColors.substring(2, 3)), 5);
    leds.set(5, getColorForString(guessColors.substring(2, 3)), 5);
    leds.set(6, getColorForString(guessColors.substring(3, 4)), 5);
    leds.set(7, getColorForString(guessColors.substring(3, 4)), 5);
    leds.show();
  }

  else if (data.startsWith("TRUE:")) {
    scrollText = data.substring(5);
    showColors = true;
    scrollOffset = 0;
    lastScrollTime = millis();
  }

  else if (data.startsWith("CLEAR:")) {
    leds.clear();
    leds.show();
    showColors = false;  // Stop scrolling if you clear
    matrix.beginDraw();
    matrix.clear();
    matrix.endDraw();
  }
}

// --- Color Parser ---
ModulinoColor getColorForString(String s) {
  if (s.equals("r")) return RED;
  if (s.equals("g")) return GREEN;
  if (s.equals("b")) return BLUE;
  if (s.equals("o")) return ORANGE;
  if (s.equals("p")) return VIOLET;
  if (s.equals("y")) return YELLOW;
  return WHITE;
}