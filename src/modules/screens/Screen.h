// FILE: src/modules/screens/Screen.h

#pragma once

#include "modules/display/DisplayManager.h"
#include "modules/io/ButtonManager.h"
#include "modules/io/EncoderManager.h"
#include "project_types.h"

class StateManager; 

class Screen {
public:
    virtual ~Screen() {}
    virtual void enter() { needsRedraw = true; } 
    virtual void leave() {}
    virtual void handleInput(ButtonManager& buttons, EncoderManager& encoder, StateManager& stateManager) = 0;
    virtual void update(StateManager& stateManager); 
    virtual void draw(DisplayManager& displayManager) = 0;
    
    ScreenState getStateID() const { return stateID; }
    bool isDirty() const { return needsRedraw; }
    void clearDirty() { needsRedraw = false; }

protected:
    ScreenState stateID;
    bool needsRedraw = true;
};