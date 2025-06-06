#include "ButtonManager.h"
#include "hardware_config.h"

void ButtonManager::begin() {
    topButton.pin = BTN_TOP_PIN;
    middleButton.pin = BTN_MIDDLE_PIN;
    bottomButton.pin = BTN_BOTTOM_PIN;

    pinMode(topButton.pin, INPUT_PULLUP);
    pinMode(middleButton.pin, INPUT_PULLUP);
    pinMode(bottomButton.pin, INPUT_PULLUP);
}

void ButtonManager::update() {
    // Reset pressed flags at the start of each update cycle
    topButton.pressed = false;
    middleButton.pressed = false;
    bottomButton.pressed = false;

    updateButton(topButton);
    updateButton(middleButton);
    updateButton(bottomButton);
}

void ButtonManager::updateButton(ButtonState& button) {
    bool reading = digitalRead(button.pin);

    if (reading != button.lastState) {
        button.lastDebounceTime = millis();
    }

    if ((millis() - button.lastDebounceTime) > debounceDelay) {
        if (reading != button.currentState) {
            button.currentState = reading;
            if (button.currentState == LOW) {
                button.pressed = true; // Set pressed flag
            }
        }
    }
    button.lastState = reading;
}

bool ButtonManager::isTopButtonPressed() {
    return topButton.pressed;
}

bool ButtonManager::isMiddleButtonPressed() {
    return middleButton.pressed;
}

bool ButtonManager::isBottomButtonPressed() {
    return bottomButton.pressed;
}
