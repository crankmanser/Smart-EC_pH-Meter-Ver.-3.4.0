#pragma once

#include <Arduino.h>

class ButtonManager {
public:
    void begin();
    void update();
    bool isTopButtonPressed();
    bool isMiddleButtonPressed();
    bool isBottomButtonPressed();

private:
    struct ButtonState {
        int pin;
        bool lastState = HIGH;
        bool currentState = HIGH;
        unsigned long lastDebounceTime = 0;
        bool pressed = false;
    };

    ButtonState topButton, middleButton, bottomButton;
    const unsigned long debounceDelay = 50;

    void updateButton(ButtonState& button);
};
