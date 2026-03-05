#include <Arduino.h>

#include "DiodeManager.h"

DiodeManager diode;

void setup() {
  diode.setup();
}

void loop() {
  diode.setOn();
  delay(500);
  diode.setOff();
  delay(500);
}