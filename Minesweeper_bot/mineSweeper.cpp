#include "mineSweeper.h"

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
    
    helpy.vectorShuffle(mineSeeds);
    for (int i = 0; i < numMines; i++) {
        auto [r, c] = helpy.convert1DTo2D(numCol, mineSeeds[i]);
        board[mineSeeds[i]] = CONSTANTS::MINE_VALUE;
        
        increaseNeighbours(card, r, c);
        increaseNeighbours(diag, r, c);
    }
}

void Minesweeper::revealMines() {
    for (int i = 0; i < numMines; i++) {
        explored[mineSeeds[i]] = CONSTANTS::MINE_VALUE;
    }
}

void Minesweeper::clickedMine() {
    gameOver = true;
    revealMines();
}

void Minesweeper::wonGame() {
    gameOver = true;
    gameWon = true;
    revealMines();
}
// PUBLIC =======================================================================================
Minesweeper::Minesweeper(int rows, int cols, int mineAmounts) : numRow(rows), numCol(cols) {
    // init default variables
    numMines = std::min(mineAmounts, numRow*numCol);
    exploredMine = false;
    safeGridsLeft = numRow*numCol - numMines;

    // init vvector values
    board.resize(numRow * numCol); 
    flagged.resize(numRow * numCol, false);
    explored.resize(numRow * numCol, CONSTANTS::UNDISCOVERED);

    mineSeeds.resize(numRow*numCol);
    std::iota(mineSeeds.begin(), mineSeeds.end(), 0);
    
    // populate board
    randomMineAlgorithm();
    helpy.board1DPrint(board, numRow, numCol);
}

void Minesweeper::restartGame() {
    randomMineAlgorithm();
    flagged.assign(numRow * numCol, false);
    explored.assign(numRow*numCol, CONSTANTS::UNDISCOVERED);
    exploredMine = false;
    safeGridsLeft = numRow*numCol - numMines;
}

void Minesweeper::discoverGrid(int r, int c) {
    if (gameOver) return;
    int x = helpy.convert2DTo1D(numCol, r, c);
    if (flagged[x]) return;
    if (explored[x] != -1) return;
    if (board[x] < 0) { // CLICKED ON A MINE!
        clickedMine();
        return;
    }

    std::queue<int> bfs;
    explored[x] = board[x];
    bfs.push(x);

    int card[5] = {1, 0, -1, 0, 1};
    int diag[5] = {1, 1, -1, -1, 1};
    auto exploreNeighbours = [&](int dir[5], int r, int c) {
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
    };

    while (!bfs.empty()) {
        int curX = bfs.front(); bfs.pop();
        safeGridsLeft--;
        auto [r, c] = helpy.convert1DTo2D(numCol, curX); 
        if (explored[curX] != 0) continue;
        exploreNeighbours(card, r, c);
        exploreNeighbours(diag, r, c);
    }
    if (safeGridsLeft <= 0) {
        wonGame();
    }
}

void Minesweeper::flagGrid(int r, int c) {
    if (gameOver) return;
    int x = helpy.convert2DTo1D(numCol, r, c);
    flagged[x] = !flagged[x];
}

// ENCAPSULATION --------------------------------------------------------------------------------
std::vector<int>& Minesweeper::getExplored() {
    return this->explored;
}

std::vector<bool>& Minesweeper::getFlagged() {
    return this->flagged;
}

bool Minesweeper::getGameWon() {
    return this->gameWon;
}
Minesweeper::~Minesweeper() {}


