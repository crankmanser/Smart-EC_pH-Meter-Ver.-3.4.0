#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include "../../project_types.h"

namespace State {
    void init();
    DeviceStatus getStatus();
    void setStatus(DeviceStatus newStatus);

    MenuState getMenuState();
    void setMenuState(MenuState newMenuState);
    
    // We will add more getters/setters here for other state variables
}

#endif // STATE_MANAGER_H