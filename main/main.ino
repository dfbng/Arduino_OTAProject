#include <WiFi.h>
#include <PubSubClient.h>
#include <Update.h>
#include "WiFiManager.h"
#include "MQTTClient.h"
#include "OTAHandler.h"

// Replace with your network credentials
const char* ssid = "your-SSID";        // WiFi SSID
const char* password = "your-PASSWORD"; // WiFi password

// Replace with your MQTT broker information
const char* mqttServer = "mqttexample.com"; // MQTT broker address
int mqttPort = 1883; // MQTT broker port (default is 1883)

WiFiManager wifiManager(ssid, password); // Create WiFiManager object to handle WiFi connection
WiFiClient espClient;  // WiFi client used by PubSubClient
PubSubClient client(espClient); // MQTT client initialized with the WiFiClient
MQTTClient mqttClient(client, mqttServer, mqttPort); // Custom MQTTClient object
OTAHandler otaHandler;  // OTAHandler object to handle over-the-air firmware updates

String otaUrl = ""; // Variable to store the firmware URL

void setup() {
    Serial.begin(115200); // Start Serial communication at 115200 baud

    wifiManager.connect(); // Connect to WiFi using WiFiManager
    client.setServer(mqttServer, mqttPort); // Set MQTT broker server and port
    client.setCallback([](char* topic, byte* payload, unsigned int length) { 
        mqttClient.callback(topic, payload, length); // Callback function for incoming MQTT messages
    });

    mqttClient.connect(); // Connect to MQTT broker
    mqttClient.subscribe("device/ota/start"); // Subscribe to topic to listen for OTA start command
    // Set a timeout for the OTA update (in milliseconds) before starting the update
    otaHandler.setTimeout(60000);  (you can change the Timeout as per your requirement)
}

void loop() {
    if (!wifiManager.isConnected()) { // Check if WiFi is connected
        wifiManager.reconnect(); // Reconnect to WiFi if not connected
    }

    client.loop(); // Keeps the MQTT client listening for messages

    // If the URL is received from MQTT, start OTA update
    if (otaUrl.length() > 0) {
        Serial.println("Starting OTA Update...");
        otaHandler.beginOTA(otaUrl.c_str()); // Start the OTA update with the received URL
        Serial.println("OTA update was successful.");
        otaUrl = ""; // Clear URL to avoid multiple updates
    }

    // Check for OTA commands from MQTT broker
    if (client.connected()) {  // Check if MQTT client is connected
        mqttClient.publishProgress("device/progress", 100);  //Publish the process
    }
}
