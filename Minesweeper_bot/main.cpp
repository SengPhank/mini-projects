
#include "raylib.h"
#include "mineSweeper.h"

#include <cstdlib>
#include <ctime>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
    // ----------------- Initialization
    const int screenWidth = 600;
    const int screenHeight = 1200;

    // Raylib settings
    InitWindow(screenWidth, screenHeight, "Raylib - C++ Minesweeper");
    SetTargetFPS(60);
    Color colors[10] = {BLUE, VIOLET, GREEN, RED, YELLOW, ORANGE, BROWN, LIME, GOLD, GRAY};

    // Minesweeper settings
    std::srand(std::time(NULL));
    const int boardRow = 13;
    const int boardCol = 13;
    const int boardMines = 12;
    Minesweeper msGame(boardRow, boardCol, boardMines);
    const int totalGrid = boardRow*boardCol;


    // Minesweeper UI (Fixed window, mines tater to that window)
    // -----------------------------------------------------------------------------------
    Vector2 gridSize = {100, 100};
    const int borderPadding = 10;
    const int gridPadding = 5;

    Rectangle gridProperties[totalGrid] = {0};
    Color colorState[totalGrid];
    for (int i = 0; i < totalGrid; i++) colorState[i] = colors[rand()%10];

    for (int i = 0; i < boardRow; i++) {
        for (int j = 0; j < boardCol; j++) {
            int idx = boardCol*i + j;
            int shorterScreen = std::min(screenWidth, screenHeight);
            int largerPop = std::max(boardCol, boardRow);
            gridProperties[idx].width = (shorterScreen-borderPadding*2)/largerPop - gridPadding;
            gridProperties[idx].height = (shorterScreen-borderPadding*2)/largerPop - gridPadding;
            gridProperties[idx].x = borderPadding + (gridProperties[idx].width*j) + gridPadding*j + borderPadding;
            gridProperties[idx].y = borderPadding + (gridProperties[idx].height*i) + gridPadding*i + borderPadding;
            
            
        }
    }
    // ------------------------------------------------------------------------------------- 
    // Minesweeper UI (fixed mines, dynamic window)
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
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