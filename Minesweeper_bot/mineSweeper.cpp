#include "mineSweeper.h"

// private:
//     int numRow, numCol, numMines;
//     std::vector<std::vector<int>> board;

Minesweeper::Minesweeper(int rows, int cols, int mineAmounts) {
    numRow = rows, numCol = cols;
    numMines = std::min(mineAmounts, numRow*numCol);
    board.resize(numRow, std::vector<int>(numCol)); 

    // populate board
    randomMineAlgorithm();
    boardPrint();
}

// randomly shuffles the given vector (Durstenfeld's algorithm)
void Minesweeper::vectorShuffle(std::vector<int>& v) {
    for (int i = v.size()-1; i >= 0; i--) {
        int randNum = rand() % (i+1);
        std::swap(v[i], v[randNum]);
    }   
}

// spreads the mines around the board using PURE randomness
void Minesweeper::randomMineAlgorithm() {
    int card[5] = {1, 0, -1, 0, 1};
    int diag[5] = {1, 1, -1, -1, 1};
    auto increaseNeighbours = [&](int dir[5], int r, int c) {
        for (int i = 0; i < 4; i++) {
            int newR = r+dir[i];
            int newC = c+dir[i+1];
            if (newR < 0 || newC < 0 || newR >= numRow || newC >= numCol) continue;
            board[newR][newC]++;
        }
    };

    std::vector<int> choices(numRow*numCol);
    std::iota(choices.begin(), choices.end(), 0);
    
    vectorShuffle(choices);
    // (x - c) / n = r, and find c using x%n 
    for (int i = 0; i < numMines; i++) {
        int c = choices[i]%numCol;
        int r = (choices[i] - c) / numCol;

        board[r][c] = -10;
        
        increaseNeighbours(card, r, c);
        increaseNeighbours(diag, r, c);
    }
}

void Minesweeper::boardPrint(){
    for (int i = 0; i < numRow; i++) {
        for (int j = 0; j < numCol; j++) {
            std::cout << (char) ((board[i][j] < 0) ? 'X' : ('0'+board[i][j])) << " ";
        }
        std::cout << "\n";
    }
}

Minesweeper::~Minesweeper() {}


