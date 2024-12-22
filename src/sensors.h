#ifndef SENSORS_H
#define SENSORS_H
#include <Wire.h>
#include <BME280I2C.h>
#include "debug.h"

class SensorHandler {
private:
    BME280I2C bme;
    bool initialized;

public:
    SensorHandler() : initialized(false) {}

    bool init() {
        Wire.begin();
        
        while(!bme.begin()) {
            DEBUG_PRINTLN("BME280 sensor not found!");
            delay(1000);
        }

        switch(bme.chipModel()) {
            case BME280::ChipModel_BME280:
                DEBUG_PRINTLN("Found BME280 sensor");
                break;
            case BME280::ChipModel_BMP280:
                DEBUG_PRINTLN("Found BMP280 sensor - No Humidity available");
                break;
            default:
                DEBUG_PRINTLN("Found UNKNOWN sensor");
                break;
        }

        initialized = true;
        return true;
    }

    BME280Data readSensors() {
        BME280Data data;
        
        if (!initialized) {
            DEBUG_PRINTLN("Sensor not initialized!");
            return data;
        }

        float temp(NAN), hum(NAN), pres(NAN);
        BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
        BME280::PresUnit presUnit(BME280::PresUnit_hPa);

        bme.read(pres, temp, hum, tempUnit, presUnit);

        data.temperature = temp;
        data.humidity = hum;
        data.pressure = pres;
        data.valid = true;

        return data;
    }
};

void IRAM_ATTR resetModule() {
    esp_restart();
}

#endif // SENSORS_H