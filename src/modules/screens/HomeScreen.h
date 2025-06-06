// FILE: src/modules/screens/HomeScreen.h

#pragma once

#include "modules/screens/Screen.h"

class HomeScreen : public Screen {
public:
    HomeScreen();
    void handleInput(ButtonManager& buttons, EncoderManager& encoder, StateManager& stateManager) override;
    void draw(DisplayManager& displayManager) override;
};