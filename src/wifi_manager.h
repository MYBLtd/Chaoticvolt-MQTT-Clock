#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFiManager.h>
#include "config.h"

class CustomNetworkManager {
private:
    WiFiManager wifiManager;
    String timezone;

public:
    CustomNetworkManager() {
        wifiManager.setDebugOutput(true);
    }

    bool initialize() {
        WiFiManagerParameter custom_timezone("tz", "Timezone", "Europe/Amsterdam", 40);
        wifiManager.addParameter(&custom_timezone);
        wifiManager.setConfigPortalTimeout(180);

        if (!wifiManager.autoConnect("ESP32_AP", "password123")) {
            DEBUG_PRINTLN("Failed to connect and hit timeout");
            delay(3000);
            ESP.restart();
            return false;
        }

        timezone = custom_timezone.getValue();
        DEBUG_PRINTLN("Connected to WiFi");
        return true;
    }

    void process() {
        // Add any periodic network checks here
    }

    void reset() {
        wifiManager.resetSettings();
        ESP.restart();
    }

    String getTimezone() const {
        return timezone;
    }
};

#endif // WIFI_MANAGER_H