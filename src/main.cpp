#include <Arduino.h>
#include "hardware_config.h"
#include "project_types.h"
#include "tasks/uiTask.h"
#include "tasks/sensorTask.h"

#include "modules/display/DisplayManager.h"
#include "modules/io/ButtonManager.h"
#include "modules/io/EncoderManager.h"
#include "modules/state/StateManager.h"

// Global Manager Objects
DisplayManager displayManager;
ButtonManager buttonManager;
EncoderManager encoderManager;
StateManager stateManager;

// FreeRTOS Task Handles
TaskHandle_t uiTaskHandle = NULL;
TaskHandle_t sensorTaskHandle = NULL;

void setup() {
    Serial.begin(115200);
    while (!Serial); // Wait for serial port to connect
    Serial.println("\nSmart EC & pH Meter - Version 3.4.0 Booting...");

    // Initialize all hardware managers
    displayManager.begin();
    buttonManager.begin();
    encoderManager.begin();
    
    // Initialize the main StateManager. It will start in the BOOT_SCREEN state.
    stateManager.begin();
    
    // Create and launch the main application tasks
    xTaskCreatePinnedToCore(sensorTask, "SensorTask", 4096, NULL, 1, &sensorTaskHandle, 0);
    xTaskCreatePinnedToCore(uiTask, "UITask", 8192, NULL, 2, &uiTaskHandle, 1);

    Serial.println("Main setup() complete. Tasks launched.");
    
    // Setup is done, no need for the core that ran setup anymore.
    vTaskDelete(NULL); 
}

void loop() {
    // Is not used when using FreeRTOS.
}
