#pragma once

#include <Arduino.h>

class EncoderManager {
public:
    void begin();
    int getChange();

private:
    // --- Speed Engine Constants (from v3.3.0) ---
    // These values determine how many ISR pulses are needed per single UI "step"
    // at different turn speeds. Lower value = faster scrolling.
    static const int PULSES_PER_STEP_FINE = 433;
    static const int PULSES_PER_STEP_MEDIUM = 161;
    static const int PULSES_PER_STEP_FAST = 77;

    // These values are the thresholds of "pulses since last check" to determine speed.
    static const int SPEED_THRESHOLD_SLOW_MAX = 55;
    static const int SPEED_THRESHOLD_MEDIUM_MAX = 165;


    // --- ISR-related static members ---
    static void IRAM_ATTR isr(); 
    static volatile long rawPulses;
    static volatile uint8_t lastABState;
    static const int8_t qem_decode_table[];
    
    // --- Member variables for tracking state ---
    int accumulatedPulses = 0;
};
