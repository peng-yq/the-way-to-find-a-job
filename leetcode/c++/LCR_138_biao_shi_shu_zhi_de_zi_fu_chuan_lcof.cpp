// https://leetcode.cn/problems/biao-shi-shu-zhi-de-zi-fu-chuan-lcof/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool validNumber(string s) {
        int k = 0;
        while (k < s.length() && s[k] == ' ')
            k++;
        if (!isNum(s, k, 1))
            return false;
        if (k < s.length() && s[k] == 'e' || s[k] == 'E') {
            k++;
            if (!isNum(s, k, 0))
                return false;
        }       
        while (k < s.length() && s[k] == ' ')
            k++;
        return k == s.length();
    }
    bool isNum(string &s, int &k, int spot) {
        int num = 0;
        while (s[k] == '+' || s[k] == '-')
            k++;
        while (s[k] >= '0' && s[k] <= '9' || s[k] == '.') {
            if (s[k] == '.') {
                if (--spot < 0)
                    return false;
            } else 
                num++;
            k++;
        }
        return num > 0;
    }
};

// 时间复杂度为O(n)，空间复杂度为O(1)