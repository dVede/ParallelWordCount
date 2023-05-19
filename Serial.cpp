#include "Serial.h"

string text_serial;

unordered_map<string, int> serial() {
    unordered_map<string, int> word_freq;
    for (size_t i = 0; i < text_serial.length(); i++) {
        string word;
        while (i < text_serial.length() - 1 && text_serial[i] != ' ') {
            word += text_serial[i];
            i++;
        }
        if (word_freq.find(word) == word_freq.end())
            word_freq[word] = 1;
        else
            word_freq[word]++;
    }
    return word_freq;
}

unordered_map<string, int> serial_count(string text) {
    text_serial = text;
    unordered_map<string, int> word_freq = serial();
    return word_freq;
}