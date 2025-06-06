#pragma once

#include "modules/screens/Screen.h"
#include "project_types.h"
#include <memory>

class StateManager {
public:
    StateManager();
    void begin();
    void changeState(ScreenState newState);
    Screen* getCurrentState();

private:
    std::unique_ptr<HomeScreen> homeScreen;
    std::unique_ptr<MenuNavScreen> menuNavScreen;
    // Add other screens here as they are created
    
    Screen* currentState;
    bool needsRedraw = true;
};
