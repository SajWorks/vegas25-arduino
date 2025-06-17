#include <Modulino.h>
#include <ArduinoGraphics.h>
#include <Arduino_LED_Matrix.h>

// Create object instances
ModulinoThermo thermo;
ModulinoBuzzer buzzer;
ArduinoLEDMatrix matrix;

int frequency = 440;
int duration = 1000;

// The last time that temp and humidity data was sent
static unsigned long lastSentTime = 0;

void setup() {
  Serial.begin(9600);

  // Call all necessary .begin() functions
  Modulino.begin();
  thermo.begin();
  buzzer.begin();  
  matrix.begin();
}

void loop() {

  // Settings for the LED Matrix
  matrix.beginDraw();
  matrix.stroke(0xFFFFFFFF);
  matrix.textScrollSpeed(50);

  // Add the text
  matrix.textFont(Font_5x7);
  matrix.beginText(0, 1, 0xFFFFFF);
  matrix.println("Hi!");
  matrix.endText(SCROLL_LEFT);
  matrix.endDraw();

  // Send the temp and humidity data if it's been more than 2 seconds
  if (millis() - lastSentTime > 2000) {

    // Measuring the temperature and humidity data
    float celsius = thermo.getTemperature();
    float fahrenheit = (celsius * 9 / 5) + 32;
    float humidity = thermo.getHumidity();

    // Serial data format <celcius>:<fahrenheit>:<humidity>\n
    Serial.print(celsius);
    Serial.print(":");
    Serial.print(fahrenheit);
    Serial.print(":");
    Serial.println(humidity);

    // Update the lastSentTime
    lastSentTime = millis();
  }

  // // Read incoming serial data for buzzer test
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    if (data.startsWith("BUZZ:")) {
      int freq = data.substring(5).toInt();
      if (freq > 0) {
        buzzer.tone(freq, 1000);
      }
    }
  }
}
