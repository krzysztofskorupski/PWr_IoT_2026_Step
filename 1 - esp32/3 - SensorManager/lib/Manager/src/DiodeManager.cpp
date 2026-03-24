#include "DiodeManager.h"

void DiodeManager::setup() {
  pinMode(DIODE_PIN, OUTPUT);
  setOff();
}

void DiodeManager::setOn() {
  digitalWrite(DIODE_PIN, HIGH);
}

void DiodeManager::setOff() {
  digitalWrite(DIODE_PIN, LOW);
}