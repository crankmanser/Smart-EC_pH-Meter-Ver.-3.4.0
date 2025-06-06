#include "BootScreen.h"
#include "hardware_config.h" 
#include "modules/state/StateManager.h"

BootScreen::BootScreen() {
    stateID = ScreenState::BOOT_SCREEN;
}

void BootScreen::enter() {
    needsRedraw = true;
    startTime = millis();
    lastAnimationTime = startTime;
    animationPhase = 0;
}

void BootScreen::update(StateManager& stateManager) {
    // Check if the boot duration has passed
    if (millis() - startTime > BOOT_DURATION_MS) {
        stateManager.changeState(ScreenState::HOME_SCREEN);
        return; // Stop further updates
    }
    
    // Cycle the animation
    if (millis() - lastAnimationTime > 300) {
        animationPhase = (animationPhase + 1) % 4;
        lastAnimationTime = millis();
        needsRedraw = true; // Mark screen as dirty to trigger a redraw
    }
}

void BootScreen::draw(DisplayManager& displayManager) {
    // Draw "Starting" text on the middle screen
    displayManager.selectOLED(OLED2_TCA_CHANNEL);
    Adafruit_SSD1306& oled2 = displayManager.getOLED(2);
    oled2.clearDisplay();
    oled2.setTextSize(2);
    oled2.setCursor(10, 15);
    oled2.print("Starting");

    // Draw animated dots on the middle screen
    oled2.setCursor(30, 40);
    switch (animationPhase) {
        case 0: oled2.print(".");     break;
        case 1: oled2.print("..");    break;
        case 2: oled2.print("...");   break;
        case 3: oled2.print("....");  break;
    }

    // Clear the other two screens to keep them blank during boot
    displayManager.selectOLED(OLED1_TCA_CHANNEL);
    displayManager.getOLED(1).clearDisplay();
    displayManager.selectOLED(OLED3_TCA_CHANNEL);
    displayManager.getOLED(3).clearDisplay();
}
