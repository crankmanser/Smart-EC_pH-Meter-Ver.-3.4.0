#pragma once

// Forward declaration for function pointer
class StateManager;

// Enum for identifying screens
enum class ScreenState {
    BOOT_SCREEN, // New state for boot-up
    HOME_SCREEN,
    MENU_NAV_SCREEN,
    // Add other states like RTC_ADJUST_SCREEN etc.
    ACTION_PLACEHOLDER // A temporary state for placeholder actions
};

// --- Data-Driven Menu Structure ---
struct MenuItem {
    const char* label;
    ScreenState targetState; // The screen to switch to
    const MenuItem* subMenu; // Pointer to an array of sub-items
    int numSubItems;         // Number of items in the sub-menu
    void (*action)(StateManager*); // Function pointer for actions
};
