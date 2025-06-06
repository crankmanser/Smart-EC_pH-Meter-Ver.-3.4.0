// FILE: src/modules/screens/HomeScreen.cpp

#include "modules/screens/HomeScreen.h"
#include "modules/state/StateManager.h"

HomeScreen::HomeScreen() {
    stateID = ScreenState::HOME_SCREEN;
}

void HomeScreen::handleInput(ButtonManager& buttons, EncoderManager& encoder, StateManager& stateManager) {
    if (buttons.isBottomButtonPressed()) {
        stateManager.changeState(ScreenState::MENU_NAV_SCREEN);
    }
}

void HomeScreen::draw(DisplayManager& displayManager) {
    // OLED 1 - Ambient
    Adafruit_SSD1306& oled1 = displayManager.getOLED(1);
    oled1.clearDisplay();
    oled1.setTextSize(1);
    oled1.setCursor(5, 5);
    oled1.println("A.Tmp: --.- C");
    oled1.setCursor(5, 20);
    oled1.println("Hum:   -- %");
    displayManager.drawButtonPrompt(oled1, "Menu");

    // OLED 2 - Probes
    Adafruit_SSD1306& oled2 = displayManager.getOLED(2);
    oled2.clearDisplay();
    oled2.setTextSize(1);
    oled2.setCursor(5, 5);
    oled2.println("EC:  ---- uS");
    oled2.setCursor(5, 20);
    oled2.println("pH:   -.-");
    oled2.setCursor(5, 35);
    oled2.println("W.Tmp: --.- C");
    
    // OLED 3 - System
    Adafruit_SSD1306& oled3 = displayManager.getOLED(3);
    oled3.clearDisplay();
    oled3.setTextSize(1);
    oled3.setCursor(5, 5);
    oled3.println("Pack: -.-- V");
    oled3.setCursor(5, 20);
    oled3.println("Load: -.-- A");
    oled3.setCursor(5, 35);
    oled3.println("Rem:  --- %");
}