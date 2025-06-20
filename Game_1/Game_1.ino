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
int right = 0;
int wrong = 0; 
int reset = 0;
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
      right +=1; 
      Serial.println("right");
      Serial.println(right);


    } else if (buttons.isPressed(1)) {
      wrong += 1;
      Serial.println("wrong place");
      Serial.println(wrong);



    } else if (buttons.isPressed(2)) {
      reset += 1;
      Serial.println("wrong");
      Serial.println(reset);



     
    }

  buttons.setLeds(button_0, button_1, button_2);
  }


}
