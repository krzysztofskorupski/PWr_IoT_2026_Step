#pragma once

#include <Arduino.h>
#include <WebServer.h>
#include <string>
#include <WiFiClient.h>

class ServerManager {
    public:
    explicit ServerManager();

    void startAP();
    bool loopAP();
    void stopAP();

    void startSTA();
    void loopRestSTA();

private:
    WebServer _server;

    std::string _ap_ssid = "esp32";
    std::string _ap_password = "supersecret";

    std::string _sta_ssid = "";
    std::string _sta_password = "";

    unsigned long _delay_ms = 5000;
};
