#include "EncoderManager.h"
#include "hardware_config.h"

// Initialize static members
volatile long EncoderManager::rawPulses = 0;
volatile uint8_t EncoderManager::lastABState = 0;
// Quadrature Encoder State Machine Table
const int8_t EncoderManager::qem_decode_table[] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};

void IRAM_ATTR EncoderManager::isr() {
    uint8_t pinA = digitalRead(ENCODER_PIN_A);
    uint8_t pinB = digitalRead(ENCODER_PIN_B);
    uint8_t currentState = (pinB << 1) | pinA;
    
    if (currentState != lastABState) {
        // Accumulate raw pulses from the encoder hardware
        rawPulses += qem_decode_table[(lastABState << 2) | currentState];
        lastABState = currentState;
    }
}

void EncoderManager::begin() {
    pinMode(ENCODER_PIN_A, INPUT_PULLUP);
    pinMode(ENCODER_PIN_B, INPUT_PULLUP);

    // Initialize the starting state
    uint8_t pinA = digitalRead(ENCODER_PIN_A);
    uint8_t pinB = digitalRead(ENCODER_PIN_B);
    lastABState = (pinB << 1) | pinA;

    attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_A), isr, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_B), isr, CHANGE);
}

int EncoderManager::getChange() {
    // --- Speed Engine Logic (ported from v3.3.0) ---

    long pulsesSinceLastCheck;

    // Atomically get the pulses from the ISR and reset the counter
    noInterrupts();
    pulsesSinceLastCheck = rawPulses;
    rawPulses = 0;
    interrupts();

    if (pulsesSinceLastCheck == 0) {
        return 0; // No change, no need to process further
    }

    // Add the new pulses to our ongoing accumulator
    accumulatedPulses += pulsesSinceLastCheck;

    // Determine the effective "pulses per step" based on the speed of the turn
    long turn_speed = abs(pulsesSinceLastCheck);
    int effectivePulsesPerStep = PULSES_PER_STEP_FINE;

    if (turn_speed < SPEED_THRESHOLD_SLOW_MAX) {
        effectivePulsesPerStep = PULSES_PER_STEP_FINE;
    } else if (turn_speed < SPEED_THRESHOLD_MEDIUM_MAX) {
        effectivePulsesPerStep = PULSES_PER_STEP_MEDIUM;
    } else {
        effectivePulsesPerStep = PULSES_PER_STEP_FAST;
    }

    // Calculate how many UI steps we can get from the accumulated pulses
    int ui_steps = 0;
    if (accumulatedPulses >= effectivePulsesPerStep) {
        ui_steps = accumulatedPulses / effectivePulsesPerStep;
        accumulatedPulses %= effectivePulsesPerStep; // Keep the remainder
    } else if (accumulatedPulses <= -effectivePulsesPerStep) {
        ui_steps = accumulatedPulses / effectivePulsesPerStep;
        accumulatedPulses %= -effectivePulsesPerStep; // Keep the remainder
    }
    
    return ui_steps;
}
