#include "sensorTask.h"
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

void sensorTaskLoop(void *pvParameters) {
    Serial.println("sensorTask: Starting on Core 0.");
    for (;;) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void createSensorTask() {
    xTaskCreatePinnedToCore(sensorTaskLoop, "SensorTask", 4096, NULL, 1, NULL, 0);
}