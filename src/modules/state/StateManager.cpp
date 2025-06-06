#include "StateManager.h"
#include "modules/screens/Screen.h" 
#include "modules/screens/BootScreen.h"
#include "modules/screens/HomeScreen.h"
#include "modules/screens/MenuNavScreen.h"


StateManager::StateManager() : currentState(nullptr) {}

void StateManager::begin() {
    // C++11 compatible way to create unique_ptr
    bootScreen.reset(new BootScreen());
    homeScreen.reset(new HomeScreen());
    menuNavScreen.reset(new MenuNavScreen());
    
    // Default to BOOT_SCREEN state on startup
    currentState = bootScreen.get();
    currentState->enter();
}

void StateManager::changeState(ScreenState newState) {
    if (currentState && currentState->getStateID() == newState) {
        return; // No change
    }

    if (currentState) {
        currentState->leave();
    }

    switch (newState) {
        case ScreenState::BOOT_SCREEN:
            currentState = bootScreen.get();
            break;
        case ScreenState::HOME_SCREEN:
            currentState = homeScreen.get();
            break;
        case ScreenState::MENU_NAV_SCREEN:
            currentState = menuNavScreen.get();
            break;
        default:
            currentState = homeScreen.get(); // Fallback to home
            break;
    }

    currentState->enter();
}

Screen* StateManager::getCurrentState() {
    return currentState;
}
