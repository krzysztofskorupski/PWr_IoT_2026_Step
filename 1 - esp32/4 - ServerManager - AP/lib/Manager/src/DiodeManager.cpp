#include "DiodeManager.h"

void DiodeManager::setup() {
  pinMode(DIODE_PIN, OUTPUT);
}

void DiodeManager::setOn() {
  digitalWrite(DIODE_PIN, HIGH);
}

void DiodeManager::setOff() {
  digitalWrite(DIODE_PIN, LOW);
}