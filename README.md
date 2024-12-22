# ESP32 MQTT Clock with Environmental Monitoring

A sophisticated ESP32-based project that combines a 7-segment display clock with environmental monitoring and MQTT integration. The system uses RTOS for efficient task management and provides real-time display of time and temperature data.

## Key Features

- Real-time clock display using 4 non-multiplexed 7-segment displays
- Boiler temperature monitoring via MQTT
- Environmental sensing with BME280 sensor:
  - Room temperature
  - Humidity
  - Barometric pressure
- RTOS-based task management
- Robust system monitoring with watchdog
- WiFi management with fallback configuration portal

## Technical Specifications

### Hardware Components
- ESP32 microcontroller
- 4× 7-segment displays with shift registers
- BME280 environmental sensor
- Power supply unit

### Software Architecture
- FreeRTOS task management
- Non-blocking operations
- Modular component design:
  - Display management
  - Sensor handling
  - MQTT communication
  - Network management
  - System monitoring

## System Architecture

```
├── Core Components
│   ├── Display Handler (non-multiplexed 7-segments)
│   ├── Sensor Manager (BME280)
│   ├── MQTT Client
│   └── System Monitor
└── Task Management
    ├── Sensor Task
    └── Monitor Task
```

## Setup and Configuration

1. Clone the repository
2. Install required libraries:
   - WiFiManager
   - PubSubClient
   - Adafruit BME280
3. Configure MQTT broker settings in `mqtt_handler.h`
4. Set up pin configurations in `config.h`
5. Upload to ESP32

## Development

Built using PlatformIO with Arduino framework. The project follows a modular architecture with separate components for:
- Display management
- Sensor operations
- Network connectivity
- MQTT communication
- System monitoring

## Contributing

Feel free to submit issues and pull requests.

## License

BSD 3-Clause "New" or "Revised" License

## Author
Have fun with this project!
Robin Kluit
