#include "uiTask.h"
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "../modules/io/LedManager.h"
#include "../modules/state/StateManager.h"



// The main loop for the UI task
void uiTaskLoop(void *pvParameters) {
    Serial.println("uiTask: Starting on Core 1.");
    
    // --- Initialize UI Modules ---
    LedManager::init();

    // To test the LED state change, we will automatically switch
    // from BOOTING to IDLE after a short delay.
    delay(2000); // Simulate boot time
    State::setStatus(STATUS_IDLE);


    for (;;) {
        // --- Update UI Modules ---
        // This is the heart of the UI task. It calls the update function
        // for each active UI module on every loop.
        LedManager::update();
        
        // ButtonManager::update(); // will be added here later
        // EncoderManager::update(); // will be added here later
        // DisplayManager::update(); // will be added here later


        vTaskDelay(pdMS_TO_TICKS(20)); // Run frequently for responsive UI
    }
}

// Function to create and pin the task
void createUiTask() {
    xTaskCreatePinnedToCore(uiTaskLoop, "UITask", 8192, NULL, 2, NULL, 1);
}