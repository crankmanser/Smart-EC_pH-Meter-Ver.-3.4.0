#ifndef HARDWARE_CONFIG_H
#define HARDWARE_CONFIG_H

// This file contains all project-wide compile-time constants and pin definitions.

// --- Firmware Version ---
#define FIRMWARE_VERSION "3.4.0"

// --- Screen dimensions & I2C ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define TCA_ADDRESS 0x70

// --- I2C Mux Channels ---
#define RTC_TCA_CHANNEL 0
#define OLED1_TCA_CHANNEL 7
#define OLED2_TCA_CHANNEL 5
#define OLED3_TCA_CHANNEL 2

// --- GPIO Pin Definitions ---
#define ENCODER_PIN_A 25
#define ENCODER_PIN_B 26
#define BTN_TOP_PIN 36
#define BTN_MIDDLE_PIN 39
#define BTN_BOTTOM_PIN 34

#define TOP_LED_RED_PIN 12
#define TOP_LED_GREEN_PIN 14
#define BOTTOM_LED_GREEN_PIN 27

#define ONE_WIRE_BUS 15
#define DHTPIN 13
#define DHTTYPE DHT11
#define SD_CS_PIN 5

#endif // HARDWARE_CONFIG_H