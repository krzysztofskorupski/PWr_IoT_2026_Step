#include <Arduino.h>

const uint8_t DIODE_PIN = 2;

void setup() {
  pinMode(DIODE_PIN, OUTPUT);
}

void loop() {
  digitalWrite(DIODE_PIN, LOW);
  delay(500);
  digitalWrite(DIODE_PIN, HIGH);
  delay(500);
}