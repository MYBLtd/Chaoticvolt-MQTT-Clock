// In system_monitor.cpp
#include "system_monitor.h"

#define WDT_TIMEOUT 5 // Define WDT_TIMEOUT with an appropriate value

SystemMonitor::SystemMonitor() : initialized(false) {}

bool SystemMonitor::init() {
    if (initialized) return true;
    
    esp_task_wdt_init(WDT_TIMEOUT, true);
    esp_task_wdt_add(NULL);
    
    initialized = true;
    return true;
}

void SystemMonitor::update() {
    if (initialized) {
        esp_task_wdt_reset();
    }
}