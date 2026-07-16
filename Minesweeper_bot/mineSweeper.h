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
    int numRow, numCol, numMines;
    std::vector<int> board; // < 0 for mines, X for how many mines are surrounding
    std::vector<int> explored; // < 0for unexplored, X for board value

    // HELPERS
    // ----------------------------------------------------------------------- /
    HelperFunction helpy;
    // BFS 

    // Methods of occupying minesweeper board
    // ------------------------------------------------------------------------ / 
    // Random: spreads the mines around the board using PURE randomness
    void randomMineAlgorithm();

public:
    Minesweeper(int rows, int cols, int mineAmounts);
    ~Minesweeper();

    // User interactions
    // ---------------------------------------------------------------------- /
    void restartGame();
    int discoverGrid(int r, int c);
    std::vector<int>& getExplored();
};

#endif