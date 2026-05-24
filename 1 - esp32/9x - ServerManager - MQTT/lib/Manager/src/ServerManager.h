#pragma once

#include <Arduino.h>
#include <WebServer.h>
#include <string>
#include <functional>
#include <WiFiClient.h>
#include <PubSubClient.h>

class ServerManager {
    public:
        explicit ServerManager();
   
        void startAP();
        void stopAP();

        bool loopAP();

        IPAddress getIP() const;

        void startSTA();
        void loopMqttSTA();

        void setDataProvider(std::function<std::string()> measure);

    private:
        WebServer _server;

        const char* _ap_ssid = "esp32";
        const char* _ap_password = "supersecret";
        
        std::string _sta_ssid = "IoT";
        std::string _sta_password = "supersecret";
        
        std::function<std::string()> _measure;

        std::string parseDataToJson(const std::string& data);

        void connectToMqtt();
        void sendMqttMessage(const std::string& body);

        WiFiClient _client_wifi;
        PubSubClient _client_mqtt;

        std::string _mqtt_broker = "10.225.83.124";
        std::string _mqtt_device = "d_123";
        std::string _mqtt_topic = "iot/data";
        int _mqtt_port = 1883; 
        
        unsigned long _mqtt_delay = 5000;
    
        unsigned long _current_time = 0;
        unsigned long _last_publish_time = 0;
};
