#ifndef GAMEWINDOW
#define GAMEWINDOW
#include "raylib.h"
#include "constants.h"
#include "mineSweeper.h"

class MineSweeper;

class GameWindow {
    private:
        bool dynamicWindow;
        int screenWidth, screenHeight;
        MineSweeper* ms;

    public:
    GameWindow(bool dynamicWindow);
    ~GameWindow();
    void GameDynamicWindow();
    void GameFixedWindow();
};

#endif 