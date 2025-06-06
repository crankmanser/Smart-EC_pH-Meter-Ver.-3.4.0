// FILE: src/modules/screens/BootScreen.h

#pragma once

#include "modules/screens/Screen.h"

class BootScreen : public Screen {
public:
    BootScreen();
    void enter() override;
    void handleInput(ButtonManager& buttons, EncoderManager& encoder, StateManager& stateManager) override {} 
    void update(StateManager& stateManager) override;
    void draw(DisplayManager& displayManager) override;

private:
    static const uint32_t BOOT_DURATION_MS = 5000;
    int animationPhase = 0;
    unsigned long startTime = 0;
    unsigned long lastAnimationTime = 0;
};