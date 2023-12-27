// https://leetcode.cn/problems/first-unique-character-in-a-string/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int firstUniqChar(string s) {
        unordered_map<char, int> s_map;
        int res = -1;
        for (char ch : s) 
            s_map[ch]++;
        for (int i = 0; i < s.length(); i++) {
            if (s_map[s[i]] == 1) {
                res = i;
                break;
            }
        }
        return res;
    }
};

// 时间复杂度为O(n)，空间复杂度为O(1)