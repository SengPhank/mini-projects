#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class All_Words
{
private:
    std::vector<std::string> word_vector;
public:
    All_Words();
    std::vector<std::string> retrieve_words_vector();
};

