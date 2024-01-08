// https://leetcode.cn/problems/string-to-integer-atoi/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int myAtoi(string s) {
        if (s.length() == 0) return 0;
        int i = 0, flag = 1, res = 0;
        while (s[i] == ' ') {
            if (++i == s.length()) return 0;
        }
        if (s[i] == '-') flag = -1;
        if (s[i] == '-' || s[i] == '+') i++;
        for (i; i < s.length(); i++) {
            if (s[i] < '0' || s[i] > '9') break;
            if (res > INT_MAX / 10 || res == INT_MAX / 10 && s[i] > '7')
                return flag == 1? INT_MAX : INT_MIN;
            res = res * 10 + (s[i] - '0');
        }
        return res * flag;
    }
};

// 时间复杂度为O(n)，空间复杂度为O(1)