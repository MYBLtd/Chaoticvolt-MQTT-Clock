#ifndef CONFIG_H
#define CONFIG_H
#include <stdint.h> 
// System status structure
struct SystemStatus {
    bool wifiConnected;
    bool mqttConnected;
    bool bmeWorking;
    bool rtcWorking;
    uint32_t freeHeap;
    uint32_t uptime;
    float cpuTemperature;
    float temperature;
    float humidity;
    float pressure;
    bool fanStatus;
    unsigned long lastUpdate;
};

// BME280 sensor data structure
struct BME280Data {
    float temperature;
    float humidity;
    float pressure;
    bool valid;
};

// Debug settings
#ifdef DEBUG_MODE
    #define DEBUG_PRINT(x) Serial.print(x)
    #define DEBUG_PRINTLN(x) Serial.println(x)
#else
    #define DEBUG_PRINT(x)
    #define DEBUG_PRINTLN(x)
#endif

// I2C Pins
#define I2C_SDA 21
#define I2C_SCL 22

// Display pins
#define SER_Pin 26    // Serial data pin
#define RCLK_Pin 33   // Register clock pin
#define SRCLK_Pin 32  // Shift register clock pin
#define NUM_DISPLAYS 4  // Renamed from DISPLAY_COUNT

// MQTT Settings
#define MQTT_BROKER "IP or url of the mqtt broker"
#define MQTT_PORT 1883
#define MQTT_USER "YourUser"
#define MQTT_PASSWORD "YourPass"

// NTP Settings
#define NTP_SERVER "pool.ntp.org"
#define TZ_INFO "CET-1CEST,M3.5.0,M10.5.0/3"

// Task Settings
#define TASK_STACK_SIZE 4096
#define QUEUE_SIZE 10
#define BME280_UPDATE_INTERVAL 30000  // 30 seconds
#define WATCHDOG_TIMEOUT_SECONDS 30

// Task delays (in milliseconds)
#define MONITOR_TASK_DELAY 1000  // 1 second delay for monitor task

// ... rest of your existing config.h content ...

#endif // CONFIG_H
