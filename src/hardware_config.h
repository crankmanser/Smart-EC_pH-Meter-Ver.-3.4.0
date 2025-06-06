#pragma once

// --- Pin Definitions ---
// I2C
// (SDA, SCL are typically ESP32 defaults, e.g., 21, 22)

// TCA9548A I2C Multiplexer
#define TCA_ADDRESS 0x70
#define RTC_TCA_CHANNEL 0
#define OLED1_TCA_CHANNEL 7
#define OLED2_TCA_CHANNEL 5
#define OLED3_TCA_CHANNEL 2

// Inputs
#define ENCODER_PIN_A 25
#define ENCODER_PIN_B 26
#define BTN_TOP_PIN    36
#define BTN_MIDDLE_PIN 39
#define BTN_BOTTOM_PIN 34

// LEDs
#define TOP_LED_RED_PIN 12
#define TOP_LED_GREEN_PIN 14
#define BOTTOM_LED_GREEN_PIN 27

// Add other sensor pins here
