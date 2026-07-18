#ifndef minesweeper
#define minesweeper

#include "constants.h"
#include "helper.h"

#include <iostream>
#include <vector>
#include <numeric>
#include <utility>
#include <queue>

class Minesweeper {
private:
    const int numRow, numCol;
    int numMines, safeGridsLeft;
    bool exploredMine = false;
    bool gameOver = false, gameWon = false;
    std::vector<int> board; // < 0 for mines, X for how many mines are surrounding
    std::vector<int> explored; // < 0 for unexplored, X for board value
    std::vector<bool> flagged;

    std::vector<int> mineSeeds; // All [r,c] positions to be randomized
    // HELPERS
    // ----------------------------------------------------------------------- /
    HelperFunction helpy;
    void revealMines();
    void clickedMine();
    void wonGame();
    // -------------------------------------------------------------------------/

    // Methods of occupying minesweeper board
    // ------------------------------------------------------------------------ / 
    // Random: spreads the mines around the board using PURE randomness
    void randomMineAlgorithm();

    // XYZ algorithm: TBA

    // ------------------------------------------------------------------------ / 

public:
    Minesweeper(int rows, int cols, int mineAmounts);
    ~Minesweeper();

    // User interactions
    // ---------------------------------------------------------------------- /
    void restartGame();
    void discoverGrid(int r, int c);
    void flagGrid(int r, int c);
    
    bool getGameWon();
    std::vector<int>& getExplored();
    std::vector<bool>& getFlagged();
};

#endif