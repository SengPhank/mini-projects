
#include "raylib.h"
#include "gameWindow.h"
#include "constants.h"

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

    // Raylib settings
    InitWindow(screenWidth, screenHeight, "Raylib - C++ Minesweeper");
    SetTargetFPS(CONSTANTS::targetFPS);
    Color colors[10] = {BLUE, VIOLET, GREEN, RED, YELLOW, ORANGE, BROWN, LIME, GOLD, GRAY};

    // Minesweeper settings
    
    const int boardRow = 13;
    const int boardCol = 13;
    const int boardMines = 12;
    Minesweeper msGame(boardRow, boardCol, boardMines);
    const int totalGrid = boardRow*boardCol;


    // Minesweeper UI (Fixed window, mines tater to that window)
    // -----------------------------------------------------------------------------------
    const int borderPadding = 10;
    const int gridPadding = 5;

    Rectangle gridProperties[totalGrid] = {0};
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
            gridProperties[idx].x = borderPadding + (gridProperties[idx].width*j) + gridPadding*j + borderPadding;
            gridProperties[idx].y = borderPadding + (gridProperties[idx].height*i) + gridPadding*i + borderPadding;
            
        }
    }
    // ------------------------------------------------------------------------------------- 
    // Minesweeper UI (fixed mines, dynamic window)
    //--------------------------------------------------------------------------------------
    bool mouseDown = false;
    int hoveredGrid = -1;
    Vector2 mousePos = { 0, 0 };
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        mousePos = GetMousePosition();
        if (mouseDown || IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            // find the grid that is interacted
            for (int i = 0; i < totalGrid; i++) {
                float distX = fabsf(gridProperties[i].x - mousePos.x);
                float distY = fabsf(gridProperties[i].y - mousePos.y);
                if (distX <= gridSize && distY <= gridSize) {
                    hoveredGrid = i;
                }
            }
        } else {
            if (mouseDown && hoveredGrid != -1) {} 
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

            for (int i = 0; i < totalGrid; i++) {
                DrawRectangleRec(gridProperties[i], colorState[i]);
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