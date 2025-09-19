#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>

#include "All_Words.h"

/* Run with:
cd 
mkdir build
cd build
cmake ..
cmake --build .
./WordleSolver

*/

// Character is in the __ Position. (Position is 1-indexed)
void isBlack(int position) {

}
void isGreen(int position) {

}
void isYellow(int position) {

}

// ======================================
void userWord() {

}

int main(void) {
    // Load Payload
    All_Words all_words;
    std::unordered_set<std::string> wordsList = all_words.retrieve_words();
    std::cout << wordsList.size() << std::endl;
    

}