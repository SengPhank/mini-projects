#ifndef minesweeper
#define minesweeper

#include <iostream>
#include <vector>
#include <numeric>

class Minesweeper {
private:
    int numRow, numCol, numMines;
    std::vector<std::vector<int>> board;

public:
    Minesweeper(int rows, int cols, int mineAmounts);
    
    void vectorShuffle(std::vector<int>& v);
    void boardPrint();

    // === Methods of occupying minesweeper board

    // Random: spreads the mines around the board using PURE randomness
    void randomMineAlgorithm();

    ~Minesweeper();
};

#endif