/***************************************************************************************************
** 7 Segment display clock with Boiler temperature display
** Uses 4 discrete latched shift registers to drive 4 7 segment displays without multiplexing
** Get the Boiler temp from a MQTT broker
** Measures room temperature, Humidity and current barametric pressure using a BME280 sensor
** 
**  Version 3.0 - [Current Date] - Robin Kluit
** 
**  1. Libraries and Configuration
**  2. Hardware Definitions
**  3. Global Variables and Objects
**  4. Function Declarations
**  5. Core Functionality Implementation
**  6. Task Definitions
**  7. Setup and Loop
** 
**  project/
**  ├── config.h           (Configuration, pins, debug settings)
**  ├── display.h          (7-segment display patterns and functions)
**  ├── sensors.h          (BME280 and other sensor functions)
**  ├── mqtt_handler.h     (MQTT configuration and functions)
**  ├── wifi_manager.h     (WiFi setup and management)
**  ├── tasks.h            (RTOS task definitions)
**  ├── system_monitor.h   (Watchdog and system monitoring)
**  └── main.ino          (Main program file)
*********************************************************************************************/

// Project headers
#include <Arduino.h>
#include "config.h"
#include "display.h"
#include "sensors.h"
#include "mqtt_handler.h"
#include "wifi_manager.h"
#include "tasks.h"
#include "system_monitor.h"

// Global objects
SensorHandler sensorHandler;
SystemMonitor systemMonitor;
CustomNetworkManager networkManager;
MQTTHandler mqttHandler;
DisplayHandler displayHandler;

// Task handles
TaskHandle_t sensorTaskHandle = NULL;
TaskHandle_t monitorTaskHandle = NULL;

void setup() {
    Serial.begin(115200);
    
    if (!sensorHandler.init()) {
        Serial.println("Sensor initialization failed!");
        return;
    }

    if (!systemMonitor.init()) {
        Serial.println("System monitor initialization failed!");
        return;
    }

    if (!networkManager.initialize()) {
        Serial.println("Network initialization failed!");
        return;
    }

    // Initialize MQTT after network is connected
    if (!mqttHandler.init()) {
        Serial.println("MQTT initialization failed!");
        return;
    }

    // Initialize DisplayHandler
    displayHandler.init();

    // Start the monitoring tasks
    xTaskCreatePinnedToCore(sensorTask, "SensorTask", 4096, NULL, 1, &sensorTaskHandle, 1);
    xTaskCreatePinnedToCore(monitorTask, "MonitorTask", 4096, NULL, 1, &monitorTaskHandle, 1);
}

void loop() {
    networkManager.process();
    mqttHandler.process();
    systemMonitor.update();
    displayHandler.updateTime();  // Replace update() with displayHandler.update()
    delay(10);
}

