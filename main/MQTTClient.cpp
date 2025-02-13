#include "MQTTClient.h"
#include <PubSubClient.h>

extern String otaUrl;

MQTTClient::MQTTClient(PubSubClient &client, const char* server, int port)
    : client(client), server(server), port(port) {}

void MQTTClient::connect() {
    while (!client.connected()) {
        Serial.println("Connecting to MQTT...");
        if (client.connect("ESP32Client")) {  // Try connecting with the client ID Example name:"ESP32Client"
            Serial.println("Connected to MQTT");
        } else {
            Serial.print("Failed, rc=");
            Serial.print(client.state());  // Print error if connection fails
            delay(5000);
        }
    }
}

void MQTTClient::subscribe(const char* topic) {
    Serial.print("Subscribing to topic: ");
    Serial.println(topic);
    client.subscribe(topic);  // Subscribe to the topic
}

void MQTTClient::publishProgress(const char* topic, int progress) {
    char message[50];
    snprintf(message, sizeof(message), "%d", progress);  // Format the progress as a string
    Serial.print("Publishing progress: ");
    Serial.print(progress);
    Serial.print(" to topic: ");
    Serial.println(topic);
    client.publish(topic, message);  // Publish the progress to the topic
}

void MQTTClient::callback(char* topic, byte* payload, unsigned int length) {
    payload[length] = '\0';  // Null-terminate the payload
    String message = String((char*)payload); // Convert payload to string

    if (String(topic) == "device/ota/start") { // If message is on "device/ota/start" topic
        Serial.print("Received OTA URL: ");
        Serial.println(message);
        otaUrl = message; // Store the received URL for OTA
    }
}
