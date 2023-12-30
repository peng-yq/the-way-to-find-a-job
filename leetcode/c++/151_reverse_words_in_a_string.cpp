// https://leetcode.cn/problems/reverse-words-in-a-string

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string reverseWords(string s) {
        string res;
        int m = s.length() - 1;
        while (s[m] == ' '&& m >= 0) m--;
        int n = m;
        while (m >= 0) {
            while (m >= 0 && s[m] != ' ') m--;
            res += s.substr(m + 1, n-m) + " ";
            while (m >=0 && s[m] == ' ') m--;
            n = m;
        }
        return res.substr(0, res.length() - 1);
    }
};

// 时间复杂度和空间复杂度都为O(n)，虽然题目要求尝试O(1)
// while (m >= 0 && s[m] != ' ') m--;
// 比下面的更节约时间
// while (m >= 0 && s[m] != ' ') 
//    m--;