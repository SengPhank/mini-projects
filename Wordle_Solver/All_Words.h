#pragma once
#include <iostream>
#include <unordered_set>
#include <vector>
#include <string>
#include <fstream>

class All_Words
{
private:
    std::unordered_set<std::string> word_set;
public:
    All_Words();
    std::unordered_set<std::string> retrieve_words();
};

