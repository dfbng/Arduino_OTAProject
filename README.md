# ESP32 OTA Firmware Update with MQTT Integration

This project demonstrates how to use Over-the-Air (OTA) firmware updates on an ESP32 using MQTT for progress reporting and managing OTA updates remotely. The system connects to a WiFi network, listens for OTA update commands via MQTT, and performs firmware updates. Progress is reported back to the MQTT broker.

## Features
- WiFi Manager: Handles WiFi connection automatically.
- MQTT Client: Connects to an MQTT broker to listen for OTA update commands and send progress updates.
- OTA Update: Supports OTA firmware updates directly from an HTTP URL.
- Progress Reporting: Sends progress updates to the MQTT broker while performing the OTA update.

## Components
- ESP32 microcontroller
- WiFi: A stable WiFi network for OTA and MQTT communication
- MQTT Broker: A server to handle MQTT communication, such as Mosquitto
- HTTP Server: A server hosting the firmware for OTA updates

## Libraries Used
- 'WiFi.h' (ESP32 library)
- 'PubSubClient.h' (MQTT library for Arduino)
- 'WiFiManager.h' (Simplified WiFi configuration)
- 'Update.h' (Arduino OTA library)

## Setup Instructions

1. Install Dependencies
   Install ESP32 Board Packages
    Make sure you have the following libraries installed via the Arduino Library Manager:
     - WiFi
     - PubSubClient
     - WiFiManager

2. Configure WiFi and MQTT Settings
Open the 'main.ino' file and update the following lines with your WiFi and MQTT broker credentials:

const char* ssid = "your-SSID";
const char* password = "your-PASSWORD";
const char* mqttServer = "mqtt.example.com";
int mqttPort = 1883;

3. Upload the Code to the ESP32
- Connect your ESP32 to the computer.
- Select the correct board and port in the Arduino IDE.
- Upload the main.ino file to your ESP32.

4. OTA Update
- Once the ESP32 is running, it will connect to your WiFi network.
- The device subscribes to the topic "device/ota/start".
- Send an MQTT message to this topic with the URL of the firmware file to trigger the OTA update.
- Progress updates will be sent to the topic "device/progress".

5. Example MQTT Command (Start OTA):
You can use an MQTT client (another device) to send a message to start the OTA update.
Example:
Topic: device/ota/start Payload: "http://your-server.com/firmware.bin"
The device will then attempt to download and apply the firmware from the URL.

## File Structure

├── main.ino                # Main application file
├── WiFiManager.h            # WiFi Manager class header
├── WiFiManager.cpp          # WiFi Manager class implementation
├── MQTTClient.h             # MQTTClient class header
├── MQTTClient.cpp           # MQTTClient class implementation
├── OTAHandler.h             # OTAHandler class header
├── OTAHandler.cpp           # OTAHandler class implementation
└── design.md                # Design document

## Troubleshooting
No progress updates: Ensure that the MQTT broker is running and your ESP32 is correctly connected.
OTA fails: Check that the URL for the firmware is accessible and the firmware is compatible with your ESP32 model.
WiFi issues: Ensure that the SSID and password are correct.
