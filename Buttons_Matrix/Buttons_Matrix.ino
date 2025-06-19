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

  buttons.setLeds(true, true, true);
}

void loop() {
  // put your main code here, to run repeatedly:
 
  if (buttons.update()) {


    if (buttons.isPressed(0)) {
      matrix.beginDraw();
      matrix.stroke(0xFFFFFFFF);
      matrix.textScrollSpeed(50);

  // Add the text
      matrix.textFont(Font_5x7);
      matrix.beginText(0, 1, 0xFFFFFF);
      matrix.println("  0");
      matrix.endText(SCROLL_LEFT);
      matrix.endDraw();

    } else if (buttons.isPressed(1)) {
      matrix.beginDraw();
      matrix.stroke(0xFFFFFFFF);
      matrix.textScrollSpeed(50);

  // Add the text
      matrix.textFont(Font_5x7);
      matrix.beginText(0, 1, 0xFFFFFF);
      matrix.println("  1");
      matrix.endText(SCROLL_LEFT);
      matrix.endDraw();



    } else if (buttons.isPressed(2)) {
      matrix.beginDraw();
      matrix.stroke(0xFFFFFFFF);
      matrix.textScrollSpeed(50);

  // Add the text
      matrix.textFont(Font_5x7);
      matrix.beginText(0, 1, 0xFFFFFF);
      matrix.println("   2");
      matrix.endText(SCROLL_LEFT);
      matrix.endDraw();


     
    }


  buttons.setLeds(button_0, button_1, button_2);
  }


}
