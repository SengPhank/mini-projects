#pragma once
#include "Helper.h"
#include <unordered_set>
#include <unordered_map>
#include <vector>
class Possible_Words {
private:
    std::vector<std::string> PossibleWordsVector;
    std::unordered_set<char> nonExist; // Characters 100% not in the word
    std::unordered_set<char> exists; // At least 1 char of this element exists
    std::unordered_map<int, std::unordered_set<char>> notIn; // {Index 0-4, CHAR NOT IN}
    std::unordered_map<int, char> greenPosition; // {Index : Character exists}
    std::unordered_set<char> blackPosition; // {char doesnt/exists}

    void isBlack(char c, int position);
    void isGreen(char c, int position);
    void isYellow(char c, int position);
    void updatePossible();

public:
    Possible_Words();
    void InputWord(std::string word); // Character, followed by the color
    std::vector<std::string> get_Possible_Words();

};

