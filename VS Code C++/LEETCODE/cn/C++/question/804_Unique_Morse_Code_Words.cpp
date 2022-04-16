// @algorithm @lc id=822 lang=cpp
// @title unique-morse-code-words

#include <iostream>
#include <vector>
#include <string>
#include "algm.h"
using namespace std;
// @test(["gin","zen","gig","msg"])=2
// @test(["a"])=1

const static string MORSE[] = {
    ".-",   "-...", "-.-.", "-..",  ".",   "..-.", "--.",  "....", "..",
    ".---", "-.-",  ".-..", "--",   "-.",  "---",  ".--.", "--.-", ".-.",
    "...",  "-",    "..-",  "...-", ".--", "-..-", "-.--", "--.."};

class Solution {
  public:
    int uniqueMorseRepresentations(vector<string> &words) {
        unordered_map<string> seen;
        for (auto &word : words) {
            string code;
            for (auto &c : word){
                code.append(MORSE[c - 'a']);
            }
            seen.emplace(code);
        }
        return seen.size();
    }
};