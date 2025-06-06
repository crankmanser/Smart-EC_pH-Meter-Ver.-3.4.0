// FILE: src/tasks/uiTask.cpp

#include "tasks/uiTask.h"
#include "modules/display/DisplayManager.h"
#include "modules/io/ButtonManager.h"
#include "modules/io/EncoderManager.h"
#include "modules/state/StateManager.h"
#include "modules/screens/Screen.h"

extern DisplayManager displayManager;
extern ButtonManager buttonManager;
extern EncoderManager encoderManager;
extern StateManager stateManager;

void uiTask(void *pvParameters) {
    Serial.println("uiTask: Starting on Core 1.");

    for (;;) {
        buttonManager.update();
        
        Screen* currentScreen = stateManager.getCurrentState();
        if (currentScreen) {
            
            // This is the clean, polymorphic way to handle updates.
            // BootScreen will do its timed transition; other screens will do nothing by default.
            currentScreen->update(stateManager);

            currentScreen->handleInput(buttonManager, encoderManager, stateManager);

            if (currentScreen->isDirty()) {
                currentScreen->draw(displayManager);
                displayManager.displayAll();
                currentScreen->clearDirty(); 
            }
        }
        
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}