// https://leetcode.cn/problems/zuo-xuan-zhuan-zi-fu-chuan-lcof/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string dynamicPassword(string password, int target) {
        string res = "";
        for (int i = target; i < password.length(); i++) {
            res.push_back(password[i]);
        }
        for (int i = 0; i < target; i++) {
            res.push_back(password[i]);
        }
        return res;
    }
};

// 时间复杂度为O(n)，空间复杂度为O(n)