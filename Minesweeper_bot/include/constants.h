#ifndef CONSTANTS
#define CONSTANTS
#include <cstdint> 

const int MINE_VALUE = INT32_MIN;
const int UNDISCOVERED = -1;
const int INVALID = -1;
// ========================= Window (UI) settings ===============================
const int targetFPS = 60;
const int borderPadding = 10;
const int gridPadding = 5;
// set window size based on the minesweeper board size?
const bool dynamicWindow = false; 
// Dynamic window = true ---------------------------------------------------
const int gridWidth = 25;
// Dynamic window = false --------------------------------------------------
const int screenWidth = 300;
const int screenHeight = 400;

// ======================== Game Settings ========================================
const int boardRow = 3;
const int boardCol = 3;
const int boardMines = 2;
#endif