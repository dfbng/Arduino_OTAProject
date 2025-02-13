#include "WiFiManager.h"
#include <WiFi.h>

WiFiManager::WiFiManager(const char* ssid, const char* password)
    : ssid(ssid), password(password) {}

void WiFiManager::connect() {
    Serial.println("Connecting to WiFi...");
    WiFi.begin(ssid, password);  // Start the connection process
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);  // Wait until connected
        Serial.print(".");
    }
    Serial.println("Connected to WiFi");
}

void WiFiManager::reconnect() {
    if (WiFi.status() != WL_CONNECTED) {
        connect();  // If disconnected, reconnect to WiFi
    }
}

bool WiFiManager::isConnected() {
    return WiFi.status() == WL_CONNECTED;  // Return whether the WiFi is connected
}
