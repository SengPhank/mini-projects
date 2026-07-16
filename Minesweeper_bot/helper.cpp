#include "helper.h"

HelperFunction::HelperFunction(/* args */) {}

int HelperFunction::convert2DTo1D(int numCol, int r, int c) {
    return numCol*r + c;
}

std::pair<int, int> HelperFunction::convert1DTo2D(int numCol, int x) {
    // (x - c) / n = r, and find c using x%n 
    int c = x % numCol;
    int r = (x-c) / numCol;
    return {r, c};
}

// randomly shuffles the given vector (Durstenfeld's algorithm)
void HelperFunction::vectorShuffle(std::vector<int>& v) {
    for (int i = v.size()-1; i >= 0; i--) {
        int randNum = rand() % (i+1);
        std::swap(v[i], v[randNum]);
    }   
}

void HelperFunction::board1DPrint(std::vector<int>& v, int numRow, int numCol){
        for (int i = 0; i < numRow; i++) {
            for (int j = 0; j < numCol; j++) {
                int val = v[convert2DTo1D(numCol, i, j)];
                std::cout << (char) ((val < 0) ? 'X' : ('0'+val)) << " ";
            }
            std::cout << "\n";
        }
    }