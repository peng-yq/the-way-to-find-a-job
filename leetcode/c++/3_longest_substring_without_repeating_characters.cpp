// https://leetcode.cn/problems/longest-substring-without-repeating-characters

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> char_map;
        int res = 0;
        for (int i = 0, j = -1; i < s.length(); i++) {
            if (char_map.find(s[i]) != char_map.end()) {
                j = max(j, char_map[s[i]]);
            }
            char_map[s[i]] = i;
            res = max(res, i - j);
        }
        return res;
    }
};

// 时间复杂度为O(n)，空间复杂度为O(1)