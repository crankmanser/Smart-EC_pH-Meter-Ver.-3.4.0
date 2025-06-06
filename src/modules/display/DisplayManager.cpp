#include "DisplayManager.h"

DisplayManager::DisplayManager() :
    oled1(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1),
    oled2(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1),
    oled3(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1)
{}

void DisplayManager::selectOLED(uint8_t oled_index) {
    if (oled_index > 7) return;
    Wire.beginTransmission(TCA_ADDRESS);
    Wire.write(1 << oled_index);
    Wire.endTransmission();
}

bool DisplayManager::begin() {
    Wire.begin();
    
    bool success = true;
    
    selectOLED(OLED1_TCA_CHANNEL);
    if (!oled1.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("OLED1 allocation failed"));
        success = false;
    }

    selectOLED(OLED2_TCA_CHANNEL);
    if (!oled2.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("OLED2 allocation failed"));
        success = false;
    }

    selectOLED(OLED3_TCA_CHANNEL);
    if (!oled3.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("OLED3 allocation failed"));
        success = false;
    }
    
    // --- FIX: Increase stabilization delay significantly ---
    delay(250);

    clearAllDisplays();
    displayAll();
    delay(100); // And another one after the first clear for good measure

    return success;
}

Adafruit_SSD1306& DisplayManager::getOLED(uint8_t index) {
    if (index == 1) return oled1;
    if (index == 2) return oled2;
    return oled3;
}

void DisplayManager::clearAllDisplays() {
    selectOLED(OLED1_TCA_CHANNEL);
    oled1.clearDisplay();
    selectOLED(OLED2_TCA_CHANNEL);
    oled2.clearDisplay();
    selectOLED(OLED3_TCA_CHANNEL);
    oled3.clearDisplay();
}

void DisplayManager::displayAll() {
    selectOLED(OLED1_TCA_CHANNEL);
    oled1.display();
    selectOLED(OLED2_TCA_CHANNEL);
    oled2.display();
    selectOLED(OLED3_TCA_CHANNEL);
    oled3.display();
}

void DisplayManager::clearAndDisplayAll() {
    clearAllDisplays();
    displayAll();
}

void DisplayManager::drawButtonPrompt(Adafruit_SSD1306& oled, const char* text) {
    int16_t x1, y1;
    uint16_t w, h;
    const int padding = 4;

    oled.setTextSize(1);
    oled.setFont(nullptr);
    oled.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
    
    int rect_h = h + padding;
    int rect_y = SCREEN_HEIGHT - rect_h;
    int text_y = rect_y + (padding / 2) + 1;
    
    oled.fillRect(0, rect_y, SCREEN_WIDTH, rect_h, SSD1306_WHITE);
    oled.setTextColor(SSD1306_BLACK);
    oled.setCursor((SCREEN_WIDTH - w) / 2, text_y);
    oled.print(text);
    oled.setTextColor(SSD1306_WHITE); // Reset text color
}

void DisplayManager::drawHeader(Adafruit_SSD1306& oled, const char* title) {
    oled.setTextSize(2);
    oled.setCursor( (SCREEN_WIDTH - (strlen(title) * 12)) / 2, 5);
    oled.print(title);
    oled.drawFastHLine(0, 25, SCREEN_WIDTH, SSD1306_WHITE);
    oled.setTextSize(1);
}
