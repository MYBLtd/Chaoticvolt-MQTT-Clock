#ifndef TASKS_H
#define TASKS_H

#include <Arduino.h>
#include "config.h"  // Add this include
#include "system_monitor.h"
#include "sensors.h"
#include "mqtt_handler.h"
#include "display.h"
#include "debug.h"

// External objects declared in main file
extern SensorHandler sensorHandler;
extern MQTTHandler mqttHandler;
extern DisplayHandler displayHandler;
extern SystemMonitor systemMonitor;  // Match name from main.cpp

void sensorTask(void *parameter) {
    const TickType_t xDelay = pdMS_TO_TICKS(2000);

    while(1) {
        BME280Data data = sensorHandler.readSensors();
        
        if (data.valid) {
            char tempStr[10], humStr[10], presStr[10];
            
            dtostrf(data.temperature, 1, 2, tempStr);
            dtostrf(data.humidity, 1, 2, humStr);
            dtostrf(data.pressure, 1, 2, presStr);
            
            if (mqttHandler.isConnected()) {
                mqttHandler.publish("bathroom/temperature", tempStr);
                mqttHandler.publish("bathroom/humidity", humStr);
                mqttHandler.publish("bathroom/pressure", presStr);
                
                DEBUG_PRINTLN("Published sensor data:");
                DEBUG_PRINT("Temp: "); DEBUG_PRINTLN(tempStr);
                DEBUG_PRINT("Hum: "); DEBUG_PRINTLN(humStr);
                DEBUG_PRINT("Pres: "); DEBUG_PRINTLN(presStr);
            }

            // Update display
            displayHandler.updateValues(data.temperature, data.humidity, data.pressure);
        }
        
        vTaskDelay(xDelay);
    }
}

void displayTask(void *parameter) {
    const TickType_t xDelay = pdMS_TO_TICKS(100);
    
    while(1) {
        displayHandler.updateTime();
        vTaskDelay(xDelay);
    }
}

void monitorTask(void *parameter) {
    for(;;) {
        systemMonitor.update();  // Change method name to match
        vTaskDelay(pdMS_TO_TICKS(MONITOR_TASK_DELAY));
    }
}

void mqttTask(void *parameter) {
    const TickType_t xDelay = pdMS_TO_TICKS(10);
    
    while(1) {
        mqttHandler.loop();
        vTaskDelay(xDelay);
    }
}

#endif // TASKS_H