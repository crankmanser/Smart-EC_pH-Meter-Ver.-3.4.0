#include "uiTask.h"
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

void uiTaskLoop(void *pvParameters) {
    Serial.println("uiTask: Starting on Core 1.");
    for (;;) {
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}

void createUiTask() {
    xTaskCreatePinnedToCore(uiTaskLoop, "UITask", 8192, NULL, 2, NULL, 1);
}