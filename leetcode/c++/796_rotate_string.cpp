// https://leetcode.cn/problems/rotate-string/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool rotateString(string s, string goal) {
        if (s.length() != goal.length()) 
            return false;
        string temp;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == goal[0]) {
                string sum_str = s.substr(i) + temp;
                if (sum_str == goal)
                    return true;
            }
            temp.push_back(s[i]);
        }
        return false;
    }
};

// 时间复杂度为O(n^2)，空间复杂度为O(n)

// O(n)的解法

class Solution {
public:
    bool rotateString(string s, string goal) {
        return s.length() == goal.length() && (goal + goal).find(s) != -1;
    }
};