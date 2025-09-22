#include "Possible_Words.h"
#define WORD_LENGTH 5
// Constructor, set default word list from JSON
Possible_Words::Possible_Words() {
    this->PossibleWordsVector = Get_All_Words();
}
void Possible_Words::isBlack(char c, int position) {
    // If not exist, mark as nonExist (until updated)
    if (!exists.count(c)) nonExist.insert(c);
    notIn[position].insert(c);
}
void Possible_Words::isGreen(char c, int position) {
    greenPosition[position] = c;
    // Mark as seen
    exists.insert(c);
    nonExist.erase(c);
}
void Possible_Words::isYellow(char c, int position) {
    // Mark as seen
    exists.insert(c);
    nonExist.erase(c); // remove it from nonExist, since it clearly exists
    notIn[position].insert(c);
}

void Possible_Words::updatePossible() {
    std::vector<std::string> filtered;
    for (const auto& word : PossibleWordsVector) {
        bool bad = false;
        int amountDiffered = 0; // how many characters differ. if it is more than what has been found, bad!
        // Check individual char for any collusion
        for (int i = 0; i < WORD_LENGTH; i++) {
            if (!exists.count(word[i])) amountDiffered++;
            if (amountDiffered > WORD_LENGTH-exists.size()) bad = true;
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

        if (!bad) filtered.push_back(word);
    }
    PossibleWordsVector.swap(filtered);
    return;
}

void Possible_Words::InputWord(std::string word) { // Character followed by their Color
    if (word.size() != WORD_LENGTH*2) return; // Invalid input
    if (!is_valid_string(word)) return;
    to_lower(word);
    for (int i = 0; i < 10; i += 2) {
        char Character = word[i];
        char Color = word[i+1];
        int pos = i / 2; // map 0,2,4,6,8 → 0,1,2,3,4
        switch (Color) {
            case 'g': isGreen(Character, pos); break;
            case 'y': isYellow(Character, pos); break;
            default:  isBlack(Character, pos); break;
        }
    }
    updatePossible();
}

std::vector<std::string> Possible_Words::get_Possible_Words() {
    return this->PossibleWordsVector;
}