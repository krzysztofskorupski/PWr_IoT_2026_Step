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

  server.setDataProvider([]() -> std::string { 
    return sensor.measure(); 
  });
}

void loop() {

  Serial.println("Configuration mode...");
  diode.setOn();

  server.startAP();

  while (server.loopAP()) {
    yield();
  };

  server.stopAP();

  Serial.println("Production mode...");
  diode.setOff();

  server.startSTA();

  while (true) {
    server.loopRestSTA();
  }
}