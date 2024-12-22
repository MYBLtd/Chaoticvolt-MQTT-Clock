#ifndef MQTT_HANDLER_H
#define MQTT_HANDLER_H

#include <PubSubClient.h>
#include <WiFi.h>
#include "config.h"
#include "debug.h"

class MQTTHandler {
private:
    WiFiClient espClient;
    PubSubClient client;
    const char* mqtt_server;
    const char* mqtt_username;
    const char* mqtt_password;
    const int mqtt_port;
    bool initialized;

public:
    MQTTHandler() : 
        client(espClient),
        mqtt_server(MQTT_BROKER),
        mqtt_username(MQTT_USER),
        mqtt_password(MQTT_PASSWORD),
        mqtt_port(MQTT_PORT),
        initialized(false) {}

    bool init();
    void process();  // Add periodic MQTT operations

    bool connect() {
        if (!initialized) {
            DEBUG_PRINTLN("MQTT not initialized!");
            return false;
        }

        if (client.connected()) {
            return true;
        }

        DEBUG_PRINT("Attempting MQTT connection...");
        
        // Create a random client ID
        String clientId = "ESP32Client-";
        clientId += String(random(0xffff), HEX);

        // Attempt to connect
        if (client.connect(clientId.c_str(), mqtt_username, mqtt_password)) {
            DEBUG_PRINTLN("connected");
            return true;
        } else {
            DEBUG_PRINT("failed, rc=");
            DEBUG_PRINT(client.state());
            DEBUG_PRINTLN(" retrying in next cycle");
            return false;
        }
    }

    bool isConnected() {
        return client.connected();
    }

    void loop() {
        if (initialized) {
            client.loop();
        }
    }

    bool publish(const char* topic, const char* payload) {
        if (!client.connected()) {
            return false;
        }
        return client.publish(topic, payload, true);  // retained message
    }
};

#endif // MQTT_HANDLER_H
