#ifndef OTAHandler_H
#define OTAHandler_H

#include <Arduino.h>
#include <Update.h>

// Define the OTAHandler class for OTA functionality
class OTAHandler {
public:
    OTAHandler();  // Constructor
    bool beginOTA(const char* url);  // Start the OTA update process using a URL
    void handleProgress(size_t current, size_t total);  // Handle and display update progress
    void validateAndRollback();  // Rollback to the previous firmware in case of failure
    void checkForTimeout();  // Check for timeout during OTA
    void setTimeout(unsigned long timeout);  // Set timeout for OTA process
    
private:
    unsigned long lastUpdateTime;  // Variable to store the last update time
    unsigned long timeoutMillis;   // Timeout variable for OTA process
    bool isUpdateInProgress;       // Flag to track if OTA is in progress
};

#endif
