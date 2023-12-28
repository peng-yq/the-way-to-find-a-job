// https://leetcode.cn/problems/isomorphic-strings

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if (s.length() != t.length())
            return false;
        unordered_map<char, char>s_t;
        unordered_map<char, char>t_s;
        for (int i = 0; i < s.length(); i++) {
            if (s_t.find(s[i]) != s_t.end() && s_t[s[i]] != t[i] ||
                t_s.find(t[i]) != t_s.end() && t_s[t[i]] != s[i]) {
                return false;
            }
            s_t[s[i]] = t[i];
            t_s[t[i]] = s[i];
        }
        return true;
    }
};

// 时间复杂度为O(n)，空间复杂度为O(1)