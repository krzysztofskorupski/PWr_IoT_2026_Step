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

        //-------------------------------------------------------------------------------------------------

        void startSTA();
        void loopRestSTA();

        //-------------------------------------------------------------------------------------------------

        void setDataProvider(std::function<std::string()> callback);

    private:
        WebServer _server;

        const char* _ap_ssid = "esp32";
        const char* _ap_password = "supersecret";

        //-------------------------------------------------------------------------------------------------
        
        std::string _sta_ssid = "";
        std::string _sta_password = "";
        
        unsigned long _delay_ms = 5000;
        
        //-------------------------------------------------------------------------------------------------

        std::function<std::string()> _data_provider;

        std::string parseDataToJson(const std::string& data);
        void sendPostRequest(const std::string& body);

        const char* _url_rest = "http://10.237.211.124:3000/api/v1/iot/data";

        std::string _device = "d_123";
        std::string _sensor = "random";

};
