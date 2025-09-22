#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>

void to_lower(std::string& s);
bool is_valid_char(char c);
bool is_valid_string(std::string s);
std::vector<std::string> Get_All_Words();