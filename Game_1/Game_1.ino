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
ModulinoColor ORANGE(255, 30,0 );
bool button_0 = true;
bool button_1 = true;
bool button_2 = true;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // Call all necessary .begin() functions
  Modulino.begin(); 
  buttons.begin();
  matrix.begin();
  buzzer.begin();
  leds.begin();

  buttons.setLeds(true, true, true);
}

void loop() {
 
  // handle button presses
  if (buttons.update()) {

    if (buttons.isPressed(0)) {
      Serial.println("Button: 1");
    } else if (buttons.isPressed(1)) {
      Serial.println("Button: 2");
    } else if (buttons.isPressed(2)) {
      Serial.println("Button: 3");
    }

  buttons.setLeds(button_0, button_1, button_2);
  }

  if (Serial.available() > 0) {
      String data = Serial.readStringUntil('\n');
      if (data.startsWith("BUZZ:")) {
        int freq = data.substring(5).toInt();
        if (freq > 0) {
          buzzer.tone(freq, 1000);
        }
      }
      else if (data.startsWith("GUESS:")){
        String colors = data.substring(6);
        String color1 = colors.substring(0,1);
        String color2 = colors.substring(1,2);
        String color3 = colors.substring(2,3);
        String color4 = colors.substring(3,4);
        Serial.println(colors);
        leds.set(0, getColorForString(color1), 5);
        leds.set(1,getColorForString(color1), 5);
        leds.set(2,getColorForString(color2), 5);
        leds.set(3,getColorForString(color2), 5);
        leds.set(4,getColorForString(color3), 5);
        leds.set(5,getColorForString(color3), 5);
        leds.set(6,getColorForString(color4), 5);
        leds.set(7, getColorForString(color4), 5);
        leds.show();
      } 
      else if (data.startsWith("TRUE:")){
        String colors = data.substring(5);
        String color1 = colors.substring(0,1);
        String color2 = colors.substring(1,2);
        String color3 = colors.substring(2,3);
        String color4 = colors.substring(3,4);
        // for (int i = 0; i < 90; i++){
          matrix.beginDraw();

          matrix.stroke(0xFFFFFFFF);
          matrix.textScrollSpeed(500);

          // Add the text
          matrix.textFont(Font_5x7);
          matrix.beginText(5, 1, 0xFFFFFF);
          matrix.println(colors);
          Serial.println(colors);
          matrix.endText(SCROLL_LEFT);
          matrix.endDraw();
        // }
      }
    }
}
ModulinoColor getColorForString(String s){
  if (s.equals("r")){
    return RED;
  }
  else if (s.equals("g")){
    return GREEN;
  }
  else if (s.equals("b")){
  return BLUE;
  }
  else if (s.equals("o")){
    return ORANGE;
  }
   else if (s.equals("p")){
    return VIOLET;
  }
  else if (s.equals("y")){
    return YELLOW;
  }
  else {
    return WHITE;
  }
}
