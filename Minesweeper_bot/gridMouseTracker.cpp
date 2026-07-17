#include "gridMouseTracker.h"

void GridMouseTracker::UpdateButton(ButtonState& state, MouseButton button, int hoverGrid, bool overGrid) {
    bool down = IsMouseButtonDown(button);

    if (down) {
        if (!state.downLocked) {
            state.downLocked = true;
            state.downGrid = overGrid ? hoverGrid : CONSTANTS::INVALID; // click started here (or off-grid)
        }
    } else {
        // button released this frame
        if (state.downLocked && overGrid && state.downGrid == hoverGrid) {
            state.clickedGrid = hoverGrid; // press and release on same grid = click
        }
        state.downLocked = false;
        state.downGrid = CONSTANTS::INVALID;
    }
}

void GridMouseTracker::Update(Vector2 mousePos, const Rectangle* gridProperties, int totalGrid, float gridSize) {
    mouseOverGrid = false;
    left.clickedGrid = CONSTANTS::INVALID;
    right.clickedGrid = CONSTANTS::INVALID;

    int hoverGrid = CONSTANTS::INVALID;
    for (int i = 0; i < totalGrid; i++) {
        const Rectangle& g = gridProperties[i];
        if (mousePos.x >= g.x && mousePos.x <= g.x + gridSize &&
            mousePos.y >= g.y && mousePos.y <= g.y + gridSize) {
            hoverGrid = i;
            mouseOverGrid = true;
            break;
        }
    }

    UpdateButton(left,  MOUSE_BUTTON_LEFT,  hoverGrid, mouseOverGrid);
    UpdateButton(right, MOUSE_BUTTON_RIGHT, hoverGrid, mouseOverGrid);
}

// ENCAPSULATION ------------------------------------------------
bool GridMouseTracker::IsOverGrid() const { 
    return this->mouseOverGrid; 
}
int GridMouseTracker::GetLeftClickedGrid() const { 
    return this->left.clickedGrid; 
}
int GridMouseTracker::GetRightClickedGrid() const { 
    return this->right.clickedGrid; 
}