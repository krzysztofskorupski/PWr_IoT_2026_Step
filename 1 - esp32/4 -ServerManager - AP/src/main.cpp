#include <Arduino.h>
#include <WiFi.h>
#include <string>

#include "DiodeManager.h"
#include "ServerManager.h"
#include "SensorManager.h"

DiodeManager diode;
ServerManager server;
SensorManager sensor;

void setup() {
  diode.setup();
  sensor.setup();

  Serial.begin(115200);

  while (!Serial) { 
    delay(10); 
  }
  
  delay(10000);
}

void loop() {

  Serial.println("Configuration mode...");
  diode.setOn();

  server.startAP();

  while (server.loopAP()) {
    yield();
  };
}