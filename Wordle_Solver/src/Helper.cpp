#include "Helper.h"


void to_lower(std::string& s) {
    for (char& c : s)
        if (c >= 'A' && c <= 'Z') c += 32;

    return;
}
bool is_valid_string(std::string s);

std::vector<std::string> Get_All_Words();