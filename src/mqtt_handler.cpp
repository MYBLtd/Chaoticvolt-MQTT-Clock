// In mqtt_handler.cpp
#include "mqtt_handler.h"

bool MQTTHandler::init() {
    if (initialized) {
        return true;
    }
    
    client.setServer(mqtt_server, mqtt_port);
    initialized = true;
    return connect();
}

void MQTTHandler::process() {
    if (!client.connected()) {
        connect();
    }
    client.loop();
}