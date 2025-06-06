#include "sensorTask.h"

void sensorTask(void *pvParameters) {
    Serial.println("sensorTask: Starting on Core 0.");
    // Sensor initialization would go here

    for (;;) {
        // Sensor reading logic will go here
        // e.g., read DHT, DS18B20, INA219
        // and send data to a queue for the uiTask
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
