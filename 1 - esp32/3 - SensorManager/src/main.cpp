#include <Arduino.h>

#include "DiodeManager.h"
#include "SensorManager.h"

DiodeManager diode;
SensorManager sensor;

void setup() {
  diode.setup();
  sensor.setup();

  while (!Serial) { 
    delay(10); 
  }
  
  delay(10000);
}

void loop() {
  Serial.print(sensor.measure().c_str());
  diode.setOn();
  delay(500);
  diode.setOff();
  delay(500);
}