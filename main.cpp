#include <WiFi.h>
#include <PubSubClient.h>
#include <Update.h>
#include "WiFiManager.h"
#include "MQTTClient.h"
#include "OTAHandler.h"

// Replace with your network credentials
const char* ssid = "your-SSID";
const char* password = "your-PASSWORD";

// Replace with your MQTT broker information
const char* mqttServer = "mqtt.example.com";
int mqttPort = 1883;

WiFiManager wifiManager(ssid, password);
WiFiClient espClient;
PubSubClient client(espClient);
MQTTClient mqttClient(client, mqttServer, mqttPort);
OTAHandler otaHandler;

void setup() {
    Serial.begin(115200);

    wifiManager.connect();
    client.setServer(mqttServer, mqttPort);
    client.setCallback([](char* topic, byte* payload, unsigned int length) {
        mqttClient.callback(topic, payload, length);
    });

    mqttClient.connect();
    mqttClient.subscribe("device/ota/start");
}

void loop() {
    if (!wifiManager.isConnected()) {
        wifiManager.reconnect();
    }

    client.loop();

    // Check for OTA commands from MQTT broker
    if (client.connected()) {
        mqttClient.publishProgress("device/progress", 100); // Just an example
    }
}
