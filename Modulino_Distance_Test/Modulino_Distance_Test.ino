#include <Modulino.h>

ModulinoDistance distance;

void setup() {
  Serial.begin(9600);
  Modulino.begin(); // Initialize the Modulino library
  distance.begin();    // Initialize the Distance Modulino
}

void loop() {
  if (distance.available()) {
    int measure = distance.get();
    Serial.print("New measurement: ");
    Serial.println(measure);
  }
  delay(100);
}
