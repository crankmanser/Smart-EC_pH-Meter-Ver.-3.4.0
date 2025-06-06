// FILE: src/modules/screens/MenuNavScreen.cpp

#include "modules/screens/MenuNavScreen.h"
#include "modules/state/StateManager.h"
#include "modules/state/MenuData.h"

MenuNavScreen::MenuNavScreen() {
    stateID = ScreenState::MENU_NAV_SCREEN;
}

void MenuNavScreen::enter() {
    needsRedraw = true;
    // Set the top-level menu when entering the screen for the first time
    setMenu(mainMenuItems, numMainMenuItems, "Menu");
}

void MenuNavScreen::setMenu(const MenuItem* menu, int numItems, const char* title) {
    currentMenuItems = menu;
    numCurrentMenuItems = numItems;
    currentTitle = title;
    selectedIndex = 0;
    needsRedraw = true;

    // A simple way to manage breadcrumbs for now
    if (strcmp(title, "Menu") == 0) {
        breadcrumbs.clear();
        breadcrumbs.push_back("Menu");
    }
}

void MenuNavScreen::handleInput(ButtonManager& buttons, EncoderManager& encoder, StateManager& stateManager) {
    if (buttons.isTopButtonPressed()) { // BACK
        if (breadcrumbs.size() > 1) {
            breadcrumbs.pop_back();
            // This is a simplified back navigation. A more robust implementation
            // would track the parent menu to navigate back to. For now, it returns to main menu.
            setMenu(mainMenuItems, numMainMenuItems, "Menu");
        } else {
            stateManager.changeState(ScreenState::HOME_SCREEN);
        }
        return;
    }
    
    if (buttons.isMiddleButtonPressed()) { // HOME
        stateManager.changeState(ScreenState::HOME_SCREEN);
        return;
    }

    if (buttons.isBottomButtonPressed()) { // SELECT
        const MenuItem& selected = currentMenuItems[selectedIndex];
        if (selected.action) {
            // If there's an action, execute it
            selected.action(&stateManager);
        } else if (selected.subMenu) {
            // If there's a submenu, navigate to it
            breadcrumbs.push_back(selected.label);
            setMenu(selected.subMenu, selected.numSubItems, selected.label);
        } else {
            // Otherwise, just change to the target state
            stateManager.changeState(selected.targetState);
        }
        return;
    }

    int encoder_change = encoder.getChange();
    if (encoder_change != 0) {
        selectedIndex -= encoder_change; // Invert for natural feel
        if (selectedIndex < 0) {
            selectedIndex = numCurrentMenuItems - 1;
        } else if (selectedIndex >= numCurrentMenuItems) {
            selectedIndex = 0;
        }
        needsRedraw = true;
    }
}

void MenuNavScreen::draw(DisplayManager& displayManager) {
    const MenuItem& selected = currentMenuItems[selectedIndex];

    // OLED 1 - Contextual Detail
    Adafruit_SSD1306& oled1 = displayManager.getOLED(1);
    oled1.clearDisplay();
    oled1.setTextSize(1);
    oled1.setCursor(5, 15);
    oled1.print("Selected:");
    oled1.setTextSize(2);
    oled1.setCursor(5, 30);
    oled1.print(selected.label);
    displayManager.drawButtonPrompt(oled1, "Select");

    // OLED 2 - Primary Menu
    Adafruit_SSD1306& oled2 = displayManager.getOLED(2);
    oled2.clearDisplay();
    displayManager.drawHeader(oled2, currentTitle);
    
    oled2.setTextSize(1);
    // Determine previous index for wrapped scrolling display
    int prevIndex = (selectedIndex == 0) ? numCurrentMenuItems - 1 : selectedIndex - 1;
    oled2.setCursor(10, 30);
    oled2.print(currentMenuItems[prevIndex].label);

    // Draw selected item (highlighted)
    oled2.fillRect(0, 40, SCREEN_WIDTH, 10, SSD1306_WHITE);
    oled2.setTextColor(SSD1306_BLACK);
    oled2.setCursor(10, 41);
    oled2.print(selected.label);
    oled2.setTextColor(SSD1306_WHITE);

    // Determine next index for wrapped scrolling display
    int nextIndex = (selectedIndex == numCurrentMenuItems - 1) ? 0 : selectedIndex + 1;
    oled2.setCursor(10, 52);
    oled2.print(currentMenuItems[nextIndex].label);
    
    displayManager.drawButtonPrompt(oled2, "Home");
    
    // OLED 3 - Breadcrumb & Status
    Adafruit_SSD1306& oled3 = displayManager.getOLED(3);
    oled3.clearDisplay();
    oled3.setTextSize(1);
    oled3.setCursor(5, 5);
    oled3.println("System Status..."); // Placeholder
    
    // Draw Breadcrumbs
    String path = "";
    for(const auto& crumb : breadcrumbs) {
        path += "/";
        path += crumb;
    }
    oled3.setCursor(5, 30);
    oled3.print("Path: ");
    oled3.print(path);

    displayManager.drawButtonPrompt(oled3, "Back");
}