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
#include <ArduinoGraphics.h>
#include <Arduino_LED_Matrix.h>

ModulinoPixels leds; 
ArduinoLEDMatrix matrix; 
ModulinoButtons buttons;
ModulinoBuzzer buzzer;

ModulinoColor YELLOW(255, 255, 0);
ModulinoColor ORANGE(255, 30, 0);

bool button_0 = true;
bool button_1 = true;
bool button_2 = true;

unsigned long previousMillis = 0;
const unsigned long interval = 3000;

String colors = "";
bool showColors = false;

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

  // Handle button presses
  if (buttons.update()) {
    if (buttons.isPressed(0)) Serial.println("Button: 1");
    if (buttons.isPressed(1)) Serial.println("Button: 2");
    if (buttons.isPressed(2)) Serial.println("Button: 3");

    buttons.setLeds(button_0, button_1, button_2);
  }

  // Read serial commands
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');

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
      colors = data.substring(5); // ✅ Update global `colors`
      showColors = true;
      previousMillis = 0; // Reset timer to start displaying immediately
    }
    else if (data.startsWith("CLEAR:")){
      leds.clear();
      leds.show();

    }
  }

  // ✅ Scroll text every `interval` if flag is true
  if (showColors && (currentMillis - previousMillis >= interval)) {
    previousMillis = currentMillis;

    matrix.beginDraw();
    matrix.textFont(Font_4x6);
    matrix.beginText(5, 1, 0xFFFFFF);
    matrix.print(colors);
    matrix.textScrollSpeed(200);
    matrix.endText(SCROLL_LEFT);
    matrix.endDraw();

    Serial.print("Scrolling: ");
    Serial.println(colors);
  }
}

// Color parser
ModulinoColor getColorForString(String s){
  if (s.equals("r")) return RED;
  if (s.equals("g")) return GREEN;
  if (s.equals("b")) return BLUE;
  if (s.equals("o")) return ORANGE;
  if (s.equals("p")) return VIOLET;
  if (s.equals("y")) return YELLOW;
  return WHITE;
}