#pragma once

#include <Arduino.h>
#include <WebServer.h>
#include <string>
#include <WiFiClient.h>

class ServerManager {
    public:
        ServerManager() = default;
   
        void startAP();
        void stopAP();

        bool loopAP();

        IPAddress getIP() const;

        //-------------------------------------------------------------------------------------------------

        void startSTA();
        void loopRestSTA();

    private:
        WebServer _server;

        const char* _ap_ssid = "esp32";
        const char* _ap_password = "supersecret";

        std::string _sta_ssid = "";
        std::string _sta_password = "";
};
