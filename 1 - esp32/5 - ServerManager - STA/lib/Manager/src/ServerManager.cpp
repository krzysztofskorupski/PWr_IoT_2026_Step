#include "ServerManager.h"
#include "webpage/MainPageAP.h"
#include <HTTPClient.h>
#include <WiFi.h>

ServerManager::ServerManager() : _server(80) {}

// ------------------------------------------------------------------------

void ServerManager::startAP() {
    WiFi.softAPdisconnect(true);

    WiFi.softAP(_ap_ssid.c_str(), _ap_password.c_str());

    _server.on("/", [this]() { 
        _server.send(200, "text/html", CONFIG_PAGE);
    });

    _server.on("/save", HTTP_POST, [this]() {
        if (_server.hasArg("ssid") && _server.hasArg("password")) {
            _sta_ssid = _server.arg("ssid").c_str();
            _sta_password = _server.arg("password").c_str();

            _server.send(200, "text/plain", "Credentials received.");
        } else {
            _server.send(400, "text/plain", "Invalid credentials");
        }
    });

    _server.begin();

    Serial.println("Access Point created.");

    Serial.printf("SSID    : %s\n", _ap_ssid.c_str());
    Serial.printf("Address : http://%s\n", WiFi.softAPIP().toString().c_str());
}

void ServerManager::stopAP() {
    _server.stop();

    WiFi.softAPdisconnect(true);

    Serial.printf("Access Point terminated.\n");
}

// ------------------------------------------------------------------------

void ServerManager::startSTA() {
    WiFi.mode(WIFI_STA); 

    delay(100);

    WiFi.begin(_sta_ssid.c_str(), _sta_password.c_str());

    Serial.print("Connecting to network.");

    int retry = 0;
    while (WiFi.status() != WL_CONNECTED && retry++ < 20) {
        delay(500);
        Serial.print(".");
    }

    Serial.println();

    if (WiFi.status() == WL_CONNECTED) {
        Serial.print("Connection established (network).\n");
    } else {
        Serial.print("Connection failed (network). Rebooting...\n");

        delay(5000);
        
        ESP.restart();
    }
}

// ------------------------------------------------------------------------

bool ServerManager::loopAP() {
    _server.handleClient();

    return _sta_ssid.empty() || _sta_password.empty();
}

void ServerManager::loopRestSTA() {
    delay(_delay_ms);

    Serial.println("Measurement");
}