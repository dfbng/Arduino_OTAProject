# Design Document for ESP32 OTA Update with MQTT

## Overview
This project involves implementing Over-the-Air (OTA) firmware updates on an ESP32, with the added functionality of reporting progress via MQTT. The ESP32 will listen for commands from an MQTT broker to trigger OTA updates, download firmware, and then apply it. The progress of the update will be reported back to the broker via MQTT, providing real-time feedback.

### High-Level System Design
- WiFiManager: Manages the WiFi connection automatically. If disconnected, it will attempt to reconnect.
- MQTTClient: Handles communication with the MQTT broker for receiving OTA commands and sending progress updates.
- OTAHandler: Manages the actual OTA update process, downloads the firmware, applies it, and reports progress.

## Components & Classes

### WiFiManager
- Purpose: Handles WiFi connection to the network.
- Methods:
  - connect(): Attempts to connect to a predefined WiFi network.
  - reconnect(): Reconnects to the WiFi network if the connection is lost.
  - isConnected(): Checks if the device is connected to WiFi.

### MQTTClient
- Purpose: Manages MQTT communication with the broker.
- Methods:
  - connect(): Connects to the MQTT broker.
  - subscribe(): Subscribes to an MQTT topic.
  - publishProgress(): Publishes progress to an MQTT topic.
  - callback(): Handles incoming messages on subscribed topics regarding firmware updates and URLs.

### OTAHandler
- Purpose: Manages the OTA update process.
- Methods:
  - beginOTA(url): Starts the OTA update using a given URL (the location of the firmware file).
  - handleProgress(current, total): Tracks and reports the update progress.
  - validateAndRollback(): Rolls back the update if it fails.
  - checkForTimeout(): Ensures the OTA update does not hang indefinitely.
  - setTimeout(timeout): Configures the timeout period for the OTA update.

## Sequence Diagram

1. WiFi Connection
   - The ESP32 starts up and attempts to connect to the WiFi using the 'WiFiManager'.
   - Once connected, the device subscribes to MQTT topics.

2. MQTT Communication
   - The ESP32 listens for an MQTT message on the "device/ota/start" topic.
   - Upon receiving a valid message (firmware URL), it triggers the 'beginOTA()' method in 'OTAHandler'.
   
3. OTA Process
   - The ESP32 downloads the firmware from the provided URL.
   - It writes the firmware data in chunks and reports progress via MQTT using 'mqttClient.publishProgress()'.
   
4. Progress Updates
   - The ESP32 continuously sends progress updates to the MQTT broker.
   - The update progress is published on the "device/progress" topic.

5. Completion
   - If the update is successful, it completes and reboots.
   - If the update fails, the device rolls back to the previous firmware.

## System Flow

- Initial Setup: The ESP32 connects to WiFi and MQTT.
- Start OTA Update: The device receives an MQTT message to start the update.
- OTA Download: The firmware is downloaded and written to the device.
- Progress Reporting: Progress is sent to the MQTT broker.
- Completion/Failure: The device either reboots with the new firmware or rolls back in case of failure.

## Communication Flow

- WiFi: The device uses 'WiFiManager' to connect to a WiFi network.
- MQTT: The device communicates with an MQTT broker using the 'MQTTClient' class for receiving commands and publishing progress.
- HTTP: The firmware is downloaded using an HTTP GET request to the provided URL.

## Timeout Handling
The OTA update has a timeout feature, which will cancel the update if it takes too long (set using 'setTimeout()'), preventing the system from hanging indefinitely.


### Future Improvements

- Error Handling: Enhance error handling for various edge cases during OTA, such as network errors or partial downloads.
- Security: Add encryption to the firmware download and MQTT communication to improve security.
- User Interface: Implement a simple web interface to monitor progress and initiate updates.


Let me know if you need more details or additional sections in the documents!
