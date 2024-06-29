// https://leetcode.cn/problems/remove-trailing-zeros-from-a-string

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string removeTrailingZeros(string num) {
        int i = num.size() - 1;
        while (i >= 0 && num[i] == '0')
            --i;
        return num.substr(0, i + 1);
    }
};