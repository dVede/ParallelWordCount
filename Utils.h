#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>

using namespace std;

struct ThreadInterval{
    int start;
    int end;
};

vector<int> divide_string_length(string text, int segments);

string readFileIntoString(const string& path);