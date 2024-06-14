// https://leetcode.cn/problems/word-pattern

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool wordPattern(string pattern, string s) {
        vector<string> str;
        int i = 0, j = 0;
        while (i < s.size() && j < s.size()) {
            j = i;
            while (s[j] != ' ' && j < s.size())
                ++j;
            str.push_back(s.substr(i, j - i));
            ++j;
            i = j;
        }
        if (pattern.size() != str.size())
            return false;
        unordered_map<char, string> pMap;
        unordered_map<string, char> sMap;
        for (int i = 0; i < pattern.size(); ++i) {
            if ((pMap.count(pattern[i]) && pMap[pattern[i]] != str[i]) || (sMap.count(str[i]) && sMap[str[i]] != pattern[i]))
                return false;
            pMap[pattern[i]] = str[i];
            sMap[str[i]] = pattern[i];
        }
        return true;
    }
};

// O(m+n) O(m+n)