// https://leetcode.cn/problems/valid-anagram/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isAnagram(string s, string t) {
        unordered_map<char, int> strings;
        unordered_map<char, int> stringt;
        for (char ch : s) 
            strings[ch]++;
        for (char ch : t) 
            stringt[ch]++;
        if (strings.size() != stringt.size())
            return false;
        for (char ch : s) {
            if (strings[ch] != stringt[ch])
                return false;
        }
        return true;
    }
};

// 时间复杂度为O(n+m)，空间复杂度为O(1)