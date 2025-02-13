#include "OTAHandler.h"
#include <HTTPClient.h>
#include <Update.h>
#include <WiFi.h>

OTAHandler::OTAHandler() : lastUpdateTime(0), timeoutMillis(0), isUpdateInProgress(false) {}

bool OTAHandler::beginOTA(const char* url) {
    HTTPClient http;
    http.begin(url);  // Start the HTTP connection with the specified URL

    int httpCode = http.GET(); // Perform GET request to the server for the firmware
    if (httpCode != HTTP_CODE_OK) {
        Serial.print("HTTP GET failed with code: ");
        Serial.println(httpCode);
        http.end();
        return false;  // If GET fails, return false
    }

    WiFiClient* stream = http.getStreamPtr();  // Get a stream to read the firmware data
    if (!Update.begin(stream->available())) {  // Start the update with the available size
        Serial.println("Failed to start OTA update");
        http.end();
        return false;  // If Update.begin() fails, return false
    }

    size_t written = 0;
    byte buffer[128];  // Buffer to hold chunks of data
    isUpdateInProgress = true;

    // Read from the stream and write to the update
    while (stream->available() && isUpdateInProgress) {
        size_t bytesRead = stream->read(buffer, sizeof(buffer));  // Read data into the buffer
        written += Update.write(buffer, bytesRead);  // Write buffer contents to the update
        handleProgress(written, stream->available());  // Display the progress
        checkForTimeout();  // Check for timeout during the update process
    }

    if (Update.end()) {  // If the update ends successfully
        Serial.println("OTA Update Successful");
        http.end();
        return true;
    } else {
        Serial.println("OTA Update Failed");
        validateAndRollback();  // If the update fails, roll back to the previous firmware
    }

    http.end();
    return false;
}

void OTAHandler::handleProgress(size_t current, size_t total) {
    int progress = (current * 100) / total;  // Calculate the progress percentage
    Serial.print("Progress: ");
    Serial.print(progress);
    Serial.println("%");  // Output the progress in percentage
}

void OTAHandler::validateAndRollback() {
    Serial.println("Rolling back to previous firmware...");
    if (Update.rollBack()) {
        Serial.println("Rollback successful");
    } else {
        Serial.println("Rollback failed");
    }
}

void OTAHandler::checkForTimeout() {
    // Add timeout check during the OTA process to avoid hanging indefinitely
    if (millis() - lastUpdateTime > timeoutMillis) {
        Serial.println("OTA process timed out");
        isUpdateInProgress = false;
    }
}

void OTAHandler::setTimeout(unsigned long timeout) {
    timeoutMillis = timeout;
}
