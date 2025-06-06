#include "StateManager.h"

// --- Private State Variables ---
// These are static, so they are only visible inside this .cpp file.
static DeviceStatus _currentDeviceStatus;
static MenuState _currentMenuState;
// ... other state variables will be defined here

void State::init() {
    _currentDeviceStatus = STATUS_BOOTING;
    _currentMenuState = STATE_HOME_SCREEN;
}

DeviceStatus State::getStatus() {
    return _currentDeviceStatus;
}

void State::setStatus(DeviceStatus newStatus) {
    // We could add logic here to prevent invalid state transitions if needed
    _currentDeviceStatus = newStatus;
}

MenuState State::getMenuState() {
    return _currentMenuState;
}

void State::setMenuState(MenuState newMenuState) {
    _currentMenuState = newMenuState;
}