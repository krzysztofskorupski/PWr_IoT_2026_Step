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

  Serial.begin(115200);

  while (!Serial) { 
    delay(10); 
  }
  
  delay(10000);
}

void loop() {
  diode.setOn();

  server.startAP();

  Serial.println(server.getIP());

  while (server.loopAP()) {
    yield();
  };

  server.stopAP();

  diode.setOff();

  server.startSTA();

  while (true) {
    server.loopRestSTA();
  }
}