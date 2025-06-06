#include <Arduino.h>
#include "hardware_config.h" // For FIRMWARE_VERSION
#include "tasks/sensorTask.h"
#include "tasks/uiTask.h"
#include "modules/state/StateManager.h"

void setup() {
    Serial.begin(115200);
    delay(1000); 
    Serial.println("\n\nBooting Smart EC & pH Meter...");
    Serial.print("Firmware Version: ");
    Serial.println(FIRMWARE_VERSION);

    // Initialize the central state manager
    State::init();

    // Create and start the core tasks
    createSensorTask();
    createUiTask();

    Serial.println("Main setup() complete. All tasks launched.");
}

void loop() {
    vTaskDelay(pdMS_TO_TICKS(1000));
}