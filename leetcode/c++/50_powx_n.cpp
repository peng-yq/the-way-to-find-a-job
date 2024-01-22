// https://leetcode.cn/problems/powx-n/description

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    double myPow(double x, int n) {
        double res = 1;
        if (n < 0)
            x = 1 / x;
        double tmp = x;
        for (int i = abs(n); i > 0; i /= 2) {
            if (i % 2 == 1)  // 二进制位该位权重为1，因此要乘当前已有的幂
                res *= tmp;
            tmp *= tmp; //无论二进制位当前权重是否为1，都要计算幂
        }
        return res;
    }
};

// 时间复杂度为O(logn)，使用快速幂解法