// https://leetcode.cn/problems/detect-capital/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool detectCapitalUse(string word) {
        if (all_of(word.begin(), word.end(), ::isupper) || all_of(word.begin(), word.end(), ::islower)) 
            return true;
        else if (word.size() > 1 && isupper(word[0]) && all_of(word.begin() + 1, word.end(), ::islower)) 
            return true;
        return false;
    }
};

