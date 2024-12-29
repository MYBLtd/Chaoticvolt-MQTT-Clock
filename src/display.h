/***************************************************************************************************
** Display Handler
** Manages 7-segment display patterns and display functions
***************************************************************************************************/

#ifndef DISPLAY_H
#define DISPLAY_H

#include "config.h"
#include <Arduino.h>
#include <ShiftRegister74HC595.h>

#define DISPLAY_COUNT 4

// Display modes
enum DisplayMode {
    DISPLAY_TIME = 0,
    DISPLAY_DATE = 1,
    DISPLAY_TEMP = 2,
    DISPLAY_HUM = 3,
    DISPLAY_PRESS = 4,
    DISPLAY_BOILER = 5
};

// Digit patterns for 7-segment display (A,B,C,D,E,F,G,DP)
const byte digitFont[] = {  // seven segment display font for digits 0 to 9
  B11000000, // 0
  B11111001, // 1
  B10100100, // 2
  B10110000, // 3
  B10011001, // 4
  B10010010, // 5
  B10000010, // 6
  B11111000, // 7
  B10000000, // 8
  B10010000, // 9
  B10000111, // t
  B10001011, // h
  B10000110, // E
  B10000011, // b
  B00000011, // b + dp
  B11111111  // blank
};
const byte digitFont_dp[] = {  // seven segment display font for digits 0 to 9 with decimal point
  B01000000, // 0
  B01111001, // 1
  B00100100, // 2
  B00110000, // 3
  B00011001, // 4
  B00010010, // 5
  B00000010, // 6
  B01111000, // 7
  B00000000, // 8
  B00010000, // 9
  B00000111, // t
  B00001011, // h
  B00000110, // E
  B00000011, // b
  B00000011, // b + dp
  B01111111  // blank
};

byte displayData[displayCount] = {  // data for each display
  0, 0, 0, 0
};

// Display message structure
struct DisplayMessage {
    DisplayMode mode;
    float value;
    bool dotState;
};

// Display state tracking
class DisplayHandler {
private:
    ShiftRegister74HC595<1> sr;
    SemaphoreHandle_t displayMutex;
    uint8_t currentDisplay[DISPLAY_COUNT];
    
public:
    DisplayHandler();
    bool init();
    void updateDisplay(const DisplayMessage& msg);
    void setDigit(int position, uint8_t pattern, bool dot = false);
    void displayNumber(int number, bool leadingZeros = false, int dots = 0);
    void displayFloat(float value, int decimals = 1);
    void updateValues(float temp, float hum, float pres);
    void updateTime();
    void updateRemote();
};

#endif // DISPLAY_H