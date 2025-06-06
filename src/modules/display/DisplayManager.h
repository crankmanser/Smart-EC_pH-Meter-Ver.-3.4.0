#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include "hardware_config.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

class DisplayManager {
public:
    DisplayManager();
    bool begin();
    void selectOLED(uint8_t oled_index);
    void clearAllDisplays();
    void displayAll();
    void clearAndDisplayAll();

    Adafruit_SSD1306& getOLED(uint8_t index);

    void drawButtonPrompt(Adafruit_SSD1306& oled, const char* text);
    void drawHeader(Adafruit_SSD1306& oled, const char* title);


private:
    Adafruit_SSD1306 oled1;
    Adafruit_SSD1306 oled2;
    Adafruit_SSD1306 oled3;
};
