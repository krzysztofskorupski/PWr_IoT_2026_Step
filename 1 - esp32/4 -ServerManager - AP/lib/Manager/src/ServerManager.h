#pragma once

#include <Arduino.h>
#include <WebServer.h>
#include <string>
#include <functional>
#include <WiFiClient.h>

class ServerManager {
    public:
    explicit ServerManager();
    
    void startAP();
    bool loopAP();
    void stopAP();

private:
    WebServer _server;

    std::string _ap_ssid = "esp32";
    std::string _ap_password = "supersecret";
};
