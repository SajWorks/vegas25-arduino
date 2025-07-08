

#include <Modulino.h>


ModulinoButtons buttons;

bool button_a = true;
bool button_b = true;
bool button_c = true;

void setup() {
  Serial.begin(9600);

  Modulino.begin();

  buttons.begin();

  buttons.setLeds(true, true, true);
}

void loop() {
  
  if (buttons.update()) {


    if (buttons.isPressed(0)) {
      matrix.beginDraw();
      matrix.stroke(0xFFFFFFFF);
      matrix.textScrollSpeed(50);

  // Add the text
      matrix.textFont(Font_5x7);
      matrix.beginText(0, 1, 0xFFFFFF);
      matrix.println("0");
      matrix.endText(SCROLL_LEFT);
      matrix.endDraw();


    } else if (buttons.isPressed(1)) {
      matrix.beginDraw();
      matrix.stroke(0xFFFFFFFF);
      matrix.textScrollSpeed(50);

  // Add the text
      matrix.textFont(Font_5x7);
      matrix.beginText(0, 1, 0xFFFFFF);
      matrix.println("1");
      matrix.endText(SCROLL_LEFT);
      matrix.endDraw();


    } else if (buttons.isPressed(2)) {
      matrix.beginDraw();
      matrix.stroke(0xFFFFFFFF);
      matrix.textScrollSpeed(50);

      // Add the text
      matrix.textFont(Font_5x7);
      matrix.beginText(0, 1, 0xFFFFFF);
      matrix.println("2");
      matrix.endText(SCROLL_LEFT);
      matrix.endDraw();

     
    }


    buttons.setLeds(button_0, button_1, button_2);
  }
}