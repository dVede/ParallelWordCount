#include "Utils.h"

using namespace std;

vector<int> divide_string_length(string text, int segments) {
    vector<int> result(segments + 1);
    int len = text.length();
    int partLen = len / segments;
    int endIndex = partLen;
    result[0] = -1;
    result[segments] = len - 1;
    for (int i = 1; i < segments; i++) {
    	while (text[endIndex] != ' ' && endIndex < len) {
	    endIndex++;
	}
	result[i] = endIndex;
	endIndex = partLen * (i + 1);
    }
    return result;
}

string readFileIntoString(const string& path) {
    ifstream input_file(path);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    return string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
}