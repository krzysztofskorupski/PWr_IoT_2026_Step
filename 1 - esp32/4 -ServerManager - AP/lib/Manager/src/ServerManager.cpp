#include "ServerManager.h"
#include "webpage/MainPageAP.h"
#include <WiFi.h>

ServerManager::ServerManager() : _server(80) {}

// ------------------------------------------------------------------------

void ServerManager::startAP() {
    WiFi.softAPdisconnect(true);

    WiFi.softAP(_ap_ssid.c_str(), _ap_password.c_str());

    _server.on("/", [this]() { 
        _server.send(200, "text/html", CONFIG_PAGE);
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

bool ServerManager::loopAP() {
    _server.handleClient();

    return true;
}