#include "mineSweeper.h"

// private:
//     int numRow, numCol, numMines;
//     std::vector<std::vector<int>> board;


// spreads the mines around the board using PURE randomness
void Minesweeper::randomMineAlgorithm() {
    int card[5] = {1, 0, -1, 0, 1};
    int diag[5] = {1, 1, -1, -1, 1};
    auto increaseNeighbours = [&](int dir[5], int r, int c) {
        for (int i = 0; i < 4; i++) {
            int newR = r+dir[i];
            int newC = c+dir[i+1];
            if (newR < 0 || newC < 0 || newR >= numRow || newC >= numCol) continue;
            board[helpy.convert2DTo1D(numCol, newR, newC)]++;
        }
    };

    std::vector<int> choices(numRow*numCol);
    std::iota(choices.begin(), choices.end(), 0);
    
    helpy.vectorShuffle(choices);
    for (int i = 0; i < numMines; i++) {
        auto [r, c] = helpy.convert1DTo2D(numCol, choices[i]);
        board[choices[i]] = CONSTANTS::MINE_VALUE;
        
        increaseNeighbours(card, r, c);
        increaseNeighbours(diag, r, c);
    }
}

// PUBLIC =======================================================================================
Minesweeper::Minesweeper(int rows, int cols, int mineAmounts) {
    numRow = rows, numCol = cols;
    numMines = std::min(mineAmounts, numRow*numCol);
    board.resize(numRow * numCol); 
    explored.resize(numRow * numCol, CONSTANTS::UNDISCOVERED);

    // populate board
    randomMineAlgorithm();
    helpy.board1DPrint(board, numRow, numCol);
}

void Minesweeper::restartGame() {
    randomMineAlgorithm();
    explored.assign(numRow*numCol, CONSTANTS::UNDISCOVERED);
}

int Minesweeper::discoverGrid(int r, int c) {
    int x = helpy.convert2DTo1D(numCol, r, c);
    if (board[x] < 0) {
        explored[x] = CONSTANTS::MINE_VALUE;
        return CONSTANTS::MINE_VALUE; // CLICKED ON A MINE!
    }

    std::queue<int> bfs;
    explored[x] = board[x];
    bfs.push(x);

    int dir[5] = {1, 0, -1, 0, 1};
    while (!bfs.empty()) {
        int curX = bfs.front(); bfs.pop();
        auto [r, c] = helpy.convert1DTo2D(numCol, curX); 
        
        if (explored[curX] != 0) continue;

        for (int i = 0; i < 4; i++) {
            int newR = r+dir[i];
            int newC = c+dir[i+1];
            if (newR < 0 || newC < 0 || newR >= numRow || newC >= numCol) continue;
            int newX = helpy.convert2DTo1D(numCol, newR, newC);
            if (explored[newX] == -1) {
                explored[newX] = board[newX];
                bfs.push(newX);
            }
        }
    }
    return explored[x];
}

// ENCAPSULATION --------------------------------------------------------------------------------
std::vector<int>& Minesweeper::getExplored() {
    return this->explored;
}


Minesweeper::~Minesweeper() {}


