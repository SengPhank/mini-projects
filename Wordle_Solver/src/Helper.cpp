#include "Helper.h"
using json = nlohmann::json;

void to_lower(std::string& s) {
    for (char& c : s)
        if (c >= 'A' && c <= 'Z') c += 32;

    return;
}
bool is_valid_char(char c) {
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}
bool is_valid_string(std::string s) {
    for (char c : s) {
        if (!is_valid_char(c)) return false;
    }
    return true;
}

std::vector<std::string> Get_All_Words() {
    std::ifstream file("data/Wordle_Words.json");
    if (!file) {
        std::cerr << "Error: could not open file\n";
        return {};
    }
    json j;
    file >> j; // parse JSON
    // Convert JSON array -> vector<string>
    return j.get<std::vector<std::string>>();
}