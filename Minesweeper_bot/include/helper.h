#ifndef HELPER
#define HELPER

#include <utility>
#include <cstdlib>
#include <vector>
#include <iostream>

class HelperFunction
{
private:
    /* data */
public:
    HelperFunction(/* args */);
    // Converts 1D to {r, c}, or vice versa
    std::pair<int, int> convert1DTo2D(int numCol, int x);
    int convert2DTo1D(int numCol, int r, int c);

    // Shuffles all elements inside v
    void vectorShuffle(std::vector<int>& v);

    // --- DEBUG ---
    void board1DPrint(std::vector<int>& v, int numRow, int numCol);
};

#endif