// GridMouseTracker.h
#ifndef GRID_MOUSE_TRACKER
#define GRID_MOUSE_TRACKER
#include "raylib.h"
#include "constants.h"

class GridMouseTracker {
    private:
        struct ButtonState {
            bool downLocked = false;
            int downGrid = CONSTANTS::INVALID;
            int clickedGrid = CONSTANTS::INVALID;
        };
        
        ButtonState left;
        ButtonState right;
        bool mouseOverGrid = false;
        
        // checks if the button is purely clicked, no drag-ins
        void UpdateButton(ButtonState& state, MouseButton button, int hoverGrid, bool overGrid);

    public:
        void Update(Vector2 mousePos, const Rectangle* gridProperties, int totalGrid, float gridSize);

        bool IsOverGrid() const;
        int GetLeftClickedGrid() const;
        int GetRightClickedGrid() const;
};

#endif