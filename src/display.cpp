#include "display.h"
#include <ctime>
#include <cstdio>

SemaphoreHandle_t displayMutex;
bool lastDisplayState[DISPLAY_COUNT] = {false};
bool dotState = false;
byte displayData[DISPLAY_COUNT] = {0, 0, 0, 0};
bool TickTock = false;
bool displayNeedsUpdate = true;

const int displayCount = 4;


DisplayHandler::DisplayHandler() {
    displayMutex = xSemaphoreCreateMutex();
    // Initialize display pins
    for (int i = 0; i < DISPLAY_COUNT; i++) {
        sr.setPin(i, false);
    }
}

void DisplayHandler::init() {
    sr.setAllLow();
}

void DisplayHandler::update() {
    if (xSemaphoreTake(displayMutex, portMAX_DELAY)) {
        std::time_t now = std::time(nullptr);
        std::tm *ltm = std::localtime(&now);
        int hour = ltm->tm_hour;
        int minute = ltm->tm_min;
        int second = ltm->tm_sec;

        // Update displayData based on current time
        displayData[0] = hour / 10;
        displayData[1] = hour % 10;
        displayData[2] = minute / 10;
        displayData[3] = minute % 10;

        // Toggle dot on the 2nd display every second
        dotState = (second % 2 == 0);

        for (int i = 0; i < DISPLAY_COUNT; i++) {
            if (lastDisplayState[i] != displayData[i]) {
                sr.setPin(i, displayData[i]);
                lastDisplayState[i] = displayData[i];
            }
        }

        // Control the dot on the 2nd display (index 1)
        sr.setDot(1, dotState);

        xSemaphoreGive(displayMutex);
    }
}

void DisplayHandler::updateValues(float temp, float hum, float pres) {
    if (xSemaphoreTake(displayMutex, portMAX_DELAY)) {
        // Update display data based on values
        displayNeedsUpdate = true;
        xSemaphoreGive(displayMutex);
    }
}

void DisplayHandler::updateTime(int hours, int minutes, bool showDot) {
/***************************************************************************************************
**  update 7 segment display with actual time                                                     **
***************************************************************************************************/
void updateDisplayTime(int hours, int minutes, int mydp) {
  // update displayData array with new values
  if (mydp==4) {displayData[4] = digitFont_dp[minutes % 10];} else {displayData[4] = digitFont[minutes % 10];}
  if (mydp==3) {displayData[3] = digitFont_dp[minutes / 10];} else {displayData[3] = digitFont[minutes / 10];}
  if (mydp==2) {displayData[2] = digitFont_dp[hours % 10];} else {displayData[2] = digitFont[hours % 10];}
  if (mydp==1) {displayData[1] = digitFont_dp[hours / 10];} else {displayData[1] = digitFont[hours / 10];}
  // update all displays with new data
  for (int i = displayCount ; i >= 1; i--) {
    shiftOut(SER_Pin, SRCLK_Pin, MSBFIRST, displayData[i]);  // send data for this display
    digitalWrite(RCLK_Pin, HIGH);  // set storage register clock input high
    delay(1);  // delay to avoid ghosting
    digitalWrite(RCLK_Pin, LOW);  // set storage register clock input low
  }
}

/***************************************************************************************************
**  update 7 segment display with remote data                                                   **
***************************************************************************************************/
void DisplayHandler::updateRemoteData(int sensorType,float sensorData) {
  int tempC = (sensorData*100);
  displayData[1] = digitFont[sensorType];
  displayData[2] = digitFont[(int(tempC)/1000)];
  displayData[3] = digitFont_dp[(int(tempC)%1000)/100];
  displayData[4] = digitFont[(int(tempC)%100)%10];
  // update all displays with new data
  for (int i = displayCount ; i >= 1; i--) 
    shiftOut(SER_Pin, SRCLK_Pin, MSBFIRST, displayData[i]);  // send data for this display
    digitalWrite(RCLK_Pin, HIGH);  // set storage register clock input high
    delay(1);  // delay to avoid ghosting
    digitalWrite(RCLK_Pin, LOW);  // set storage register clock input low
}

