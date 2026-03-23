#include "ServerManager.h"
#include "webpage/MainPageAP.h"
#include <HTTPClient.h>
#include <WiFi.h>

void ServerManager::startAP() {
    WiFi.softAP(_ap_ssid, _ap_password);

    _server.on("/", [this]() { 
        _server.send(200, "text/html", CONFIG_PAGE);
    });

    _server.on("/save", HTTP_POST, [this]() {
        _sta_ssid = _server.arg("ssid").c_str();
        _sta_password = _server.arg("password").c_str();

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

    return _sta_ssid.empty() || _sta_password.empty();
}

IPAddress ServerManager::getIP() const {

    return WiFi.softAPIP();
}

//-------------------------------------------------------------------------------------------------

void ServerManager::startSTA() {
    WiFi.mode(WIFI_STA); 

    delay(100);

    WiFi.begin(_sta_ssid.c_str(), _sta_password.c_str());

    int retry = 0;
    while (WiFi.status() != WL_CONNECTED && retry++ < 20) {
        delay(500);
    }

    if (WiFi.status() != WL_CONNECTED) {
        Serial.print("Connection failed (STA). Rebooting...\n");

        delay(5000);
        
        ESP.restart();
    }
}

void ServerManager::loopRestSTA() {
    delay(_delay_ms);

    if (_data_provider) {
        std::string jsonBody = parseDataToJson(_data_provider());
        sendPostRequest(jsonBody);
    } else {
        Serial.print("No Data Provider set. Rebooting...\n");

        delay(5000);
        
        ESP.restart();
    }
}

//-------------------------------------------------------------------------------------------------

void ServerManager::setDataProvider(std::function<std::string()> callback) {
    _data_provider = callback;
}

std::string ServerManager::parseDataToJson(const std::string& payload) {
    return "{\"device\": \"" + _device + "\", \"sensor\": \"" + _sensor + "\", \"payload\": \"" + payload + "\"}";
}

void ServerManager::sendPostRequest(const std::string& body) {
    HTTPClient http;

    http.begin(_url_rest);
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST(body.c_str());

    if (httpResponseCode > 0) {
        std::string response = http.getString().c_str();
        Serial.printf("HTTP Response code: %d\n", httpResponseCode);
    } else {
        Serial.printf("Error code: %d\n", httpResponseCode);
    }
 
    http.end();
}
