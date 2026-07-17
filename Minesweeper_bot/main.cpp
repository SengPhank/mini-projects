
#include "raylib.h"
#include "helper.h"
#include "gameWindow.h"
#include "constants.h"
#include "gridMouseTracker.h"

#include <string>
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
    SetTargetFPS(9999999);
    Color colors[10] = {BLUE, VIOLET, GREEN, PURPLE, YELLOW, ORANGE, BROWN, LIME, GOLD, GRAY};

    // Minesweeper settings
    Minesweeper msGame(CONSTANTS::boardRow, CONSTANTS::boardCol, CONSTANTS::boardMines);
    std::vector<int>& explored = msGame.getExplored();
    std::vector<bool>& flagged = msGame.getFlagged();
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
    const int mineTextPadding = 5;
    const int mineTextSize = gridSize-mineTextPadding/2;
    
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
    // Minesweeper UI (fixed grids, or dynamic window)
    //--------------------------------------------------------------------------------------
    GridMouseTracker mouseTracker;
    Vector2 mousePos = { 0.0f, 0.0f };

    // --------------------------------------------------------------------------------------------
    // UI Helpers
    // --------------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        mousePos = GetMousePosition();
        mouseTracker.Update(mousePos, gridProperties, totalGrid, gridSize);

        SetMouseCursor(mouseTracker.IsOverGrid() ? MOUSE_CURSOR_POINTING_HAND : MOUSE_CURSOR_DEFAULT);

        if (mouseTracker.GetLeftClickedGrid() != CONSTANTS::INVALID) {
            auto [r, c] = helpy.convert1DTo2D(CONSTANTS::boardCol, mouseTracker.GetLeftClickedGrid());
            // std::cout << "LEFT: discovering: " << r << ", " << c << std::endl;
            msGame.discoverGrid(r, c);
        }

        if (mouseTracker.GetRightClickedGrid() != CONSTANTS::INVALID) {
            auto [r, c] = helpy.convert1DTo2D(CONSTANTS::boardCol, mouseTracker.GetRightClickedGrid());
            // std::cout << "RIGHT: flagging: " << r << ", " << c << std::endl;
            msGame.flagGrid(r, c); 
        }

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

            for (int i = 0; i < totalGrid; i++) {
                int discovered = explored[i];
                Color gridClr = GetColor(0xd9d9d9ff);
                if (discovered == CONSTANTS::MINE_VALUE) {
                    if (msGame.getGameWon()) {
                        gridClr = GREEN;
                    } else {
                        gridClr = RED;
                    }
                } else if (discovered < 0) {
                    gridClr = GRAY;
                } 
                DrawRectangleRec(gridProperties[i], gridClr);

                if (discovered >= 0) {
                    DrawText(TextFormat("%i", discovered), gridProperties[i].x + mineTextPadding, gridProperties[i].y + mineTextPadding, mineTextSize, BLACK);
                } else if (flagged[i]) {
                    DrawText("V", gridProperties[i].x + mineTextPadding, gridProperties[i].y + mineTextPadding, mineTextSize, RED);
                }
                
            }

            DrawFPS(screenWidth - 100, screenHeight - 30);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}