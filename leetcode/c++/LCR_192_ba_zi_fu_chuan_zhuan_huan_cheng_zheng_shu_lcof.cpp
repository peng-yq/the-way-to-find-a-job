// https://leetcode.cn/problems/ba-zi-fu-chuan-zhuan-huan-cheng-zheng-shu-lcof/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int myAtoi(string str) {
        if (str.length() == 0) 
            return 0;
        int res = 0, flag = 1, i = 0;
        while (str[i] == ' ')
            if (i++ == str.length())
                return 0;
        if (str[i] == '-' || str[i] == '+') {
            if (str[i] == '-')
                flag = -1;
            i++;
        }
        for (i; i < str.length(); i++) {
            if (str[i] < '0' || str[i] > '9')
                break;
            if (res > INT_MAX / 10 || res == INT_MAX / 10 && str[i] > '7')
                return flag == 1? INT_MAX : INT_MIN;
            else 
                res = res * 10 + (str[i] - '0');
        }
        return flag * res;
    }
};

// 时间复杂度为O(n)，空间复杂度为O(n)