#ifndef SYSTEM_MONITOR_H
#define SYSTEM_MONITOR_H

#include <esp_task_wdt.h>
#include "config.h"

class SystemMonitor {
public:
    SystemMonitor();
    bool init();
    void update();  // Ensure this matches the method name used
private:
    bool initialized;
};

#endif