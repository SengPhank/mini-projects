#ifndef minesweeper
#define minesweeper

#include <vector>

#include <cstdlib>
#include <ctime>

class Minesweeper {
private:
    int numRow, numCol, numMines;
    std::vector<std::vector<int>> board;

public:
    Minesweeper(int rows, int cols, int mineAmounts) {
        std::srand(std::time(NULL)); // TODO: mv to main file

        numRow = rows, numCol = cols;
        numMines = std::min(mineAmounts, numRow*numCol);
        board.resize(numRow, std::vector<int>(numCol)); 
    }

    // spreads the mines around the board using PURE randomness
    void pureRandomSprinkler() {
        int mineRemaining = numMines;
        std::vector<int> valid(numRow*numCol);
        
        // (x - c) / n = r, find this using x%n 
        std::iota(valid.begin(), valid.end(), 0);
    }

    ~Minesweeper();
};

Minesweeper::Minesweeper(/* args */)
{
}

Minesweeper::~Minesweeper()
{
}


#endif