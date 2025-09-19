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
    this->word_vector = j.get<std::vector<std::string>>();
    return;
}

std::vector<std::string> All_Words::retrieve_words_vector() {
    return this->word_vector;
}