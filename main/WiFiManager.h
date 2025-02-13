#ifndef WiFiManager_H
#define WiFiManager_H

#include <WiFi.h>

class WiFiManager {
public:
    WiFiManager(const char* ssid, const char* password);  // Constructor
    void connect();  // Connect to WiFi
    void reconnect();  // Reconnect to WiFi if disconnected
    bool isConnected();  // Check if WiFi is connected
    
private:
    const char* ssid;  // WiFi SSID
    const char* password;  // WiFi password
};

#endif
