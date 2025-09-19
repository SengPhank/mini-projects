#include <include/nlohmann/json.hpp>
#include "All_Words.h"
using json = nlohmann::json;

All_Words::All_Words() {
    std::ifstream file("Wordle_Words.json");
    if (!file) {
        std::cerr << "Error: could not open file\n";
        return;
    }
    json j;
    file >> j; // parse JSON
    // Convert JSON array -> vector<string>
    std::vector<std::string> temp = j.get<std::vector<std::string>>();
    // Construct unordered_set from vector
    for (std::string word : temp) {
        this->word_set.insert(word);
    }
}

std::unordered_set<std::string> All_Words::retrieve_words() {
    return this->word_set;
}