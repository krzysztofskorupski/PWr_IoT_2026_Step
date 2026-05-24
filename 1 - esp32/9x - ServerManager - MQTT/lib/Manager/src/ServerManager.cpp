#include "ServerManager.h"
#include "webpage/MainPageAP.h"
#include <HTTPClient.h>
#include <WiFi.h>

ServerManager::ServerManager() : _client_mqtt(_client_wifi) {}

void ServerManager::startAP() {
    WiFi.softAP(_ap_ssid, _ap_password);

    _server.on("/", [this]() { 
        _server.send(200, "text/html", CONFIG_PAGE);
    });

    _server.on("/save", HTTP_POST, [this]() {
        _sta_ssid = _server.arg("ssid").c_str();
        _sta_password = _server.arg("password").c_str();

        Serial.printf("%s | %s\n", _sta_ssid.c_str(), _sta_password.c_str());

        _server.send(200, "text/plain", "Credentials received.");
    });

    _server.begin();
}

void ServerManager::stopAP() {
    _server.stop();

    WiFi.softAPdisconnect(true);
}

bool ServerManager::loopAP() {
    _server.handleClient();

    return _sta_ssid.empty();
}

IPAddress ServerManager::getIP() const {

    return WiFi.softAPIP();
}

void ServerManager::startSTA() {
    WiFi.mode(WIFI_STA); 

    WiFi.begin(_sta_ssid.c_str(), _sta_password.c_str());

    delay(10000);

    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Connection failed (STA). Rebooting...");

        delay(5000);
        
        ESP.restart();
    }

    Serial.println("Connection established (STA).");

    _client_mqtt.setServer(_mqtt_broker.c_str(), _mqtt_port);                           
}

void ServerManager::setDataProvider(std::function<std::string()> measure) {
    _measure = measure;
}

std::string ServerManager::parseDataToJson(const std::string& payload) {
    
    return R"({"device": "d_123", "sensor": "random", "payload": ")" + payload + "\"}";
}

//-------------------------------------------------------------------------------------------------

void ServerManager::connectToMqtt() {

    while (!_client_mqtt.connected()) {
        Serial.println("Connecting to MQTT.");

        if (_client_mqtt.connect("test")) {
            Serial.println("Connection established (MQTT).");
        } else {
            Serial.print("Connection failed (MQTT). State: ");
            Serial.print(_client_mqtt.state());
            Serial.print("\n");
            
            delay(5000); 
        }
    }
}

void ServerManager::sendMqttMessage(const std::string& body) {

    if (_client_mqtt.publish(_mqtt_topic.c_str(), body.c_str())) {
        Serial.println("MQTT message published.");
    } else {
        Serial.println("MQTT message error.");
    }
}

void ServerManager::loopMqttSTA() {

    if (!_client_mqtt.connected()) {
        connectToMqtt();
    }

    _client_mqtt.loop();

    _current_time = millis();
    if (_current_time - _last_publish_time >= _mqtt_delay) {
        _last_publish_time = _current_time;

        sendMqttMessage(parseDataToJson(_measure()));
    }
}