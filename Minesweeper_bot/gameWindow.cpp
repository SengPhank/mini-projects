#include "gameWindow.h"

/*
bool dynamicWindow;
int screenWidth, screenHeight;
MineSweeper* ms;
*/
GameWindow::GameWindow(bool dynamicWindow) {
    this->dynamicWindow = dynamicWindow;
    if (dynamicWindow) {
        GameDynamicWindow();
    } else {
        GameFixedWindow();
    }
} 

void GameWindow::GameDynamicWindow() {

}

void GameWindow::GameFixedWindow() {

}

GameWindow::~GameWindow() {

}
