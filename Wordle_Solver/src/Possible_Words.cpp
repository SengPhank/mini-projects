#include "Possible_Words.h"

// Constructor, set default word list from JSON
Possible_Words::Possible_Words() {
    this->PossibleWordsVector = Get_All_Words();
}
void Possible_Words::isBlack(char c, int position, std::unordered_set<char>& exists, std::unordered_map<int, std::unordered_set<char>>& notIn, std::unordered_set<char>& nonExist) {
    // If not exist, mark as nonExist (until updated)
    if (!exists.count(c)) nonExist.insert(c);
    notIn[position].insert(c);
    return;
}
void Possible_Words::isGreen(char c, int position, std::unordered_set<char>& exists, std::unordered_set<char>& nonExist, std::unordered_map<int, char>& greenPosition) {
    greenPosition[position] = c;
    // Mark as seen
    exists.insert(c);
    nonExist.erase(c);
    return;
}
void Possible_Words::isYellow(char c, int position, std::unordered_set<char>& exists, std::unordered_map<int, std::unordered_set<char>>& notIn, std::unordered_set<char>& nonExist) {
    // Mark as seen
    exists.insert(c);
    nonExist.erase(c); // remove it from nonExist, since it clearly exists
    notIn[position].insert(c);
    return;
}

void Possible_Words::updatePossible(std::vector<std::string>& PossibleWordsVector, std::unordered_map<int, std::unordered_set<char>>& notIn, std::unordered_set<char>& nonExist, std::unordered_map<int, char>& greenPosition, std::unordered_set<char>& exists) {
    std::unordered_set<std::string> PossibleWordsSet(PossibleWordsVector.begin(), PossibleWordsVector.end());
    for (std::string word : PossibleWordsVector) {
        bool bad = false;
        int amountDiffered = 0; // how many characters differ. if it is more than what has been found, bad!
        // Check individual char for any collusion
        for (int i = 0; i < 5; i++) {
            if (!exists.count(word[i])) amountDiffered++;
            if (amountDiffered > 5-exists.size()) bad = true;
            if (bad) break;

            // Check for Green:
            if (greenPosition.count(i) && greenPosition[i] != word[i]) bad = true;
            if (bad) break;
            
            // Check for existance
            if (nonExist.count(word[i])) bad = true;
            if (bad) break;

            // Check for NOT in
            if (notIn[i].count(word[i])) bad = true;
        }

        if (bad) PossibleWordsSet.erase(word);
    }
    std::vector<std::string> tmp(PossibleWordsSet.begin(), PossibleWordsSet.end());
    PossibleWordsVector = tmp;
    return;
}

void userWord(std::string word) { // Character followed by their Color
    if (word.size() != 10) return; // Invalid input
    for (int i = 0; i < 5; i++) {
        std::cout << ". Character " << i+1 << ": ";
        std::string userInput;
        std::cin >> userInput;
        to_lower(userInput);
        switch (userInput[1])
        {
        case 'g':
            isGreen(userInput[0], i, exists, nonExist, greenPosition);
            break;
        case 'y': 
            isYellow(userInput[0], i, exists, notIn, nonExist);
            break;
        default:
            isBlack(userInput[0], i, exists, notIn, nonExist);
            break;
        } 
    }

    return;
}
std::vector<std::string> Possible_Words::get_Possible_Words() {
    return this->PossibleWordsVector;
}