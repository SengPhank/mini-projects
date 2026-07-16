
#include "raylib.h"
#include "helper.h"
#include "gameWindow.h"
#include "constants.h"

#include <iostream>
#include <math.h>
#include <cstdlib>
#include <ctime>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
    // ----------------- Initialization
    std::srand(std::time(NULL));
    int screenWidth = CONSTANTS::screenWidth;
    int screenHeight = CONSTANTS::screenHeight;
    HelperFunction helpy;

    // Raylib settings
    InitWindow(screenWidth, screenHeight, "Raylib - C++ Minesweeper");
    SetTargetFPS(CONSTANTS::targetFPS);
    Color colors[10] = {BLUE, VIOLET, GREEN, PURPLE, YELLOW, ORANGE, BROWN, LIME, GOLD, GRAY};

    // Minesweeper settings
    const int boardRow = 10;
    const int boardCol = 4;
    const int boardMines = 12;
    Minesweeper msGame(boardRow, boardCol, boardMines);
    std::vector<int>& explored = msGame.getExplored();
    const int totalGrid = boardRow*boardCol;


    // Minesweeper UI (Fixed window, mines tater to that window)
    // -----------------------------------------------------------------------------------
    const int borderPadding = 20;
    const int gridPadding = 5;

    Rectangle gridProperties[totalGrid] = { 0 };
    Color colorState[totalGrid];
    for (int i = 0; i < totalGrid; i++) colorState[i] = colors[rand()%10];

    int shorterScreen = std::min(screenWidth, screenHeight);
    int largerPop = std::max(boardCol, boardRow);
    int gridSize = (shorterScreen-borderPadding*2)/largerPop - gridPadding;
    for (int i = 0; i < boardRow; i++) {
        for (int j = 0; j < boardCol; j++) {
            int idx = boardCol*i + j;
            gridProperties[idx].width = gridSize;
            gridProperties[idx].height = gridSize;
            gridProperties[idx].x = borderPadding + (gridProperties[idx].width*j) + gridPadding*j;
            gridProperties[idx].y = borderPadding + (gridProperties[idx].height*i) + gridPadding*i;
            
        }
    }
    // ------------------------------------------------------------------------------------- 
    // Minesweeper UI (fixed mines, dynamic window)
    //--------------------------------------------------------------------------------------
    bool mouseDown = false;
    bool mouseOverGrid = false;
    int mouseDownGrid = CONSTANTS::INVALID;
    bool mouseDownLocked = false;
    int gridClicked = CONSTANTS::INVALID;
    Vector2 mousePos = { 0.0f, 0.0f };
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        mousePos = GetMousePosition();
        mouseOverGrid = false;

        
        // find the grid that the mouse is currently over
        for (int i = 0; i < totalGrid; i++) {
            if (mousePos.x >= gridProperties[i].x
                && mousePos.x <= gridProperties[i].x + gridSize
                && mousePos.y >= gridProperties[i].y
                && mousePos.y <= gridProperties[i].y + gridSize) {
                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                    if (!mouseDownLocked) mouseDownGrid = i;
                } else {
                    // IF CLICKED
                    if (mouseDownGrid == i) {
                        auto [r, c] = helpy.convert1DTo2D(CONSTANTS::boardCol, i);
                        msGame.discoverGrid(r, c);
                    }
                }

                mouseOverGrid = true;
                break;
            }
        }

        // Visual mouse effect
        (mouseOverGrid) ? SetMouseCursor(MOUSE_CURSOR_POINTING_HAND) : 
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);

        // Prevents weird drag-in-clicks
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            if (!mouseDownLocked) mouseDownLocked = true;
        } else {
            mouseDownGrid = CONSTANTS::INVALID;
            mouseDownLocked = false;
        }

        

        // let go of button, so "pressed" essentially
        // if (mouseDown && !IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        //     std::cout << "CLICKED ON " << hoveredGrid << std::endl;
        //     mouseDown = false;
        //     // "pressed" hoveredGrid button, randomize the chosen colour
        //     if (hoveredGrid != -1) {
        //         colorState[hoveredGrid] = colors[rand()%10];
        //     }
        // }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

            for (int i = 0; i < totalGrid; i++) {
                int discovered = explored[i];
                Color gridClr;
                if (discovered == CONSTANTS::MINE_VALUE) {
                    gridClr = RED;
                } else if (discovered < 0) {
                    gridClr = GRAY;
                } else {
                    gridClr = GREEN;
                }
                    
                DrawRectangleRec(gridProperties[i], gridClr);
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}