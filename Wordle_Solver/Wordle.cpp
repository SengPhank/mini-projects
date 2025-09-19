#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>
// Json File Handling
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

bool Load_All_Words(std::unordered_set<std::string>& loadTo) {
    std::ifstream file("Wordle_Words.json");
    if (!file) {
        std::cerr << "Error: could not open file\n";
        return false;
    }
    json j;
    file >> j; // parse JSON
    // Convert JSON array -> vector<string>
    std::vector<std::string> temp = j.get<std::vector<std::string>>();
    // Construct unordered_set from vector
    for (std::string word : temp) {
        loadTo.insert(word);
    }
    return true;
}

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
    std::unordered_set<std::string> allWords;
    if (!Load_All_Words(allWords)) return 0;

    // Get User Information
    int numGuesses;
    std::cout << "How many guesses have you made: ";
    std::cin >> numGuesses;

    // Green = correct letter and placement
    // Yellow = correct letter, incorrect placement
    // Black = incorrect letter
    std::unordered_set<char> allYellows;
    std::unordered_map<int, std::unordered_set<char>> yellow; // {position : all char in pos}
    std::unordered_set<char> black; // if word[i] in black
    std::unordered_map<int, char> green;
    std::unordered_map<char, int> characterAmount; // Word has at least {Int} {Chars}

    // Enter word and correct placement for exclusion of potential words
    std::cout << "Color = {'Y' = yellow, 'B' = black, 'G' = green}" << std::endl;
    for (int i = 0; i < numGuesses; i++) {
        std::string wordInp, placementInp;
        std::cout << "Enter your 5-letter word: ";
        std::cin >> wordInp;
        if (wordInp.size() != 5) {
            std::cout << "Your word was not 5 letters. please try again!" << std::endl;
            i--;
            break;
        }
        std::cout << "Enter your 5-letter placement. For example if its all incorrect, enter 'BBBBB': ";
        std::cin >> placementInp;
        if (placementInp.size() != 5) {
            std::cout << "Your placements were not 5 letters. please try again!" << std::endl;
            i--;
            break;
        }
        
        for (int c = 0; c < 5; c++) {
            switch (placementInp[c])
            {
            case 'Y':
                yellow[c].insert(wordInp[c]);
                break;
            case 'G':
                green[c] = wordInp[c];
                break;
            default:
                black.insert(wordInp[c]);
                break;
            }
        }
    }
    // Clean up input, where we remove from black if in yellow/green (this occurs on duplicate-char words)
    for (auto i = green.begin(); i != green.end(); ++i) {
        black.erase(i->second);
    }
    for (auto i = yellow.begin(); i != yellow.end(); ++i) {
        for (char j : i->second) {
            black.erase(j);
            allYellows.insert(j);
        }
    }

    // Look through potential words in word list
    std::vector<std::string> potentialWords;
    for (std::string s : wordList) {
        bool isValid = true;
        // check green
        for (auto i : green) {
            if (s[i.first] != i.second) {
                isValid = false;
                break;
            }
        }
        if (!isValid) break;

        // Check yellow & black
        std::unordered_set<char>popYellow = allYellows;
        for (int i = 0; i < 5; i++) {
            if (yellow[i].count(s[i]) || black.count(s[i])) {
                isValid = false;
                break;
            }
            popYellow.erase(s[i]);
        }
        if (!popYellow.empty()) {
            isValid = false;
        }
        if (!isValid) break;

        potentialWords.push_back(s);
    } 
    std::cout << "Potential words: " << std::endl;
    for (std::string ans : potentialWords) {
        std::cout << ans << std::endl;
    }

    std::cout << "Amount shown: " << potentialWords.size();
    

}