#pragma once

#include <Arduino.h>
#include <WebServer.h>
#include <string>
#include <functional>
#include <WiFiClient.h>

class ServerManager {
    public:
        ServerManager() = default;
   
        void startAP();
        void stopAP();

        bool loopAP();

        IPAddress getIP() const;

        void startSTA();
        void loopRestSTA();

        //-------------------------------------------------------------------------------------------------

        void setDataProvider(std::function<std::string()> measure);

    private:
        WebServer _server;

        const char* _ap_ssid = "esp32";
        const char* _ap_password = "supersecret";
        
        std::string _sta_ssid = "IoT";
        std::string _sta_password = "supersecret";
        
        //-------------------------------------------------------------------------------------------------

        std::function<std::string()> _measure;
};
