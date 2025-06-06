#ifndef PROJECT_TYPES_H
#define PROJECT_TYPES_H

struct MenuItem; // Forward declaration

// Enum for overall device status
enum DeviceStatus {
    STATUS_BOOTING, STATUS_IDLE, STATUS_MEASURING, STATUS_CALIBRATING,
    STATUS_ERROR, STATUS_SAVING, STATUS_SD_ERROR
};

// Enum for temperature units
enum TempUnit { UNIT_CELSIUS, UNIT_FAHRENHEIT, UNIT_KELVIN };

// Enum for the primary UI state machine
enum MenuState {
    STATE_HOME_SCREEN,
    STATE_MENU_NAV,
    STATE_SETTINGS_RTC_ADJUST,
    STATE_SETTINGS_BATTERY_INFO
};

// Struct defining a menu item for the UI
struct MenuItem {
    const char* label;
    MenuState targetStateOnSelect;
    const MenuItem* subMenu;
    int numSubItems;
    void (*actionFunction)();
};

// Struct for passing data from the sensor core to the UI core
typedef struct {
    float ds18b20_temperatureC;
    bool ds18b20_sensorFound;
    // ... we will add more fields here as we integrate sensors
} SensorCoreData_t;

#endif // PROJECT_TYPES_H