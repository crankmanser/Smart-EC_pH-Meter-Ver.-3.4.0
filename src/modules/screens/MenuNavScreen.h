// FILE: src/modules/screens/MenuNavScreen.h

#pragma once

#include "modules/screens/Screen.h"
#include "project_types.h" // Needs MenuItem
#include <vector>

class MenuNavScreen : public Screen {
public:
    MenuNavScreen();
    void enter() override;
    void handleInput(ButtonManager& buttons, EncoderManager& encoder, StateManager& stateManager) override;
    void draw(DisplayManager& displayManager) override;
    void setMenu(const MenuItem* menu, int numItems, const char* title);

private:
    const MenuItem* currentMenuItems = nullptr;
    int numCurrentMenuItems = 0;
    int selectedIndex = 0;
    const char* currentTitle = "Menu";
    std::vector<const char*> breadcrumbs;
};