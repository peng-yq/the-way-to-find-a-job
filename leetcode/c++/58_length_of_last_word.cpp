// https://leetcode.cn/problems/length-of-last-word

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int lengthOfLastWord(string s) {
        int n = s.size(), res = 0, i = n - 1;
        while (i >= 0 && s[i] == ' ')
            --i;
        while (i >= 0 && s[i] != ' ') {
            ++res;
            --i;
        }
        return res;
    }
};