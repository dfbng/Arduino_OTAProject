#ifndef MQTTClient_H
#define MQTTClient_H

#include <PubSubClient.h>

class MQTTClient {
public:
    MQTTClient(PubSubClient &client, const char* server, int port);  // Constructor
    void connect();  // Connect to the MQTT broker
    void subscribe(const char* topic);  // Subscribe to an MQTT topic
    void publishProgress(const char* topic, int progress);  // Publish progress to a topic
    void callback(char* topic, byte* payload, unsigned int length);  // Handle received MQTT messages
    
private:
    PubSubClient &client;  // The MQTT client reference
    const char* server;  // MQTT broker server address
    int port;  // MQTT broker port
};

#endif
