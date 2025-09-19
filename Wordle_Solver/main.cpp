#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>

#include "All_Words.h"

// Helper ==========================
void to_lower(std::string& s) {
    for (char& c : s)
        if (c >= 'A' && c <= 'Z') c += 32;

    return;
}

// Update
void updatePossible(std::vector<std::string>& PossibleWordsVector, std::unordered_map<int, std::unordered_set<char>>& notIn, std::unordered_set<char>& nonExist, std::unordered_map<int, char>& greenPosition, std::unordered_set<char>& exists) {
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
// Character is in the __ Position. (Position is 1-indexed)
void isBlack(char c, int position, std::unordered_set<char>& exists, std::unordered_map<int, std::unordered_set<char>>& notIn, std::unordered_set<char>& nonExist) {
    // If not exist, mark as nonExist (until updated)
    if (!exists.count(c)) nonExist.insert(c);
    notIn[position].insert(c);
    return;
}
void isGreen(char c, int position, std::unordered_set<char>& exists, std::unordered_set<char>& nonExist, std::unordered_map<int, char>& greenPosition) {
    greenPosition[position] = c;
    // Mark as seen
    exists.insert(c);
    nonExist.erase(c);
    return;
}
void isYellow(char c, int position, std::unordered_set<char>& exists, std::unordered_map<int, std::unordered_set<char>>& notIn, std::unordered_set<char>& nonExist) {
    // Mark as seen
    exists.insert(c);
    nonExist.erase(c); // remove it from nonExist, since it clearly exists
    notIn[position].insert(c);
    return;
}

// ======================================
// Retrieve user Input for their ith word
void userWord(std::unordered_set<char>& exists, std::unordered_map<int, std::unordered_set<char>>& notIn, std::unordered_set<char>& nonExist, std::unordered_map<int, char>& greenPosition) {
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

int main(void) { 
    std::cout << " ==================== PROJECT BEGINS ====================" << std::endl;
    // Load Payload
    All_Words all_words;
    std::vector<std::string> PossibleWordsVector = all_words.retrieve_words_vector();
    std::cout << PossibleWordsVector.size() << " Possible Words found" << std::endl;

    // Init variables
    std::unordered_set<char> nonExist; // Characters 100% not in the word
    std::unordered_set<char> exists; // At least 1 char of this element exists
    std::unordered_map<int, std::unordered_set<char>> notIn; // {Index 0-4, CHAR NOT IN}
    std::unordered_map<int, char> greenPosition; // {Index : Character exists}
    std::unordered_set<char> blackPosition; // {char doesnt/exists}

    // User Input
    int numWords;
    std::cout << "How many words have you entered thus far; ";
    std::cin >> numWords;

    std::cout << "Enter two characters, 'xc', where X is the character at the ith position, and C is the color (Green, Yellow, Black)" << std::endl;
    for (int i = 0; i < numWords; i++) {
        std::cout << "Word " << i+1 << " out of " << numWords << std::endl;
        userWord(exists, notIn, nonExist, greenPosition);
    }
    updatePossible(PossibleWordsVector, notIn, nonExist, greenPosition, exists);

    // print out all possible words
    std::cout << "\nPOSSIBLE WORDS: " << std::endl;
    for (std::string i : PossibleWordsVector) {
        std::cout << i << std::endl;
    }
    std::cout << PossibleWordsVector.size() << " POSSIBLE WORDS to choose from " << std::endl; 
    std::cout << " ==================== PROJECT ENDS ====================" << std::endl;
    return 0;
}