// https://leetcode.cn/problems/shu-zhi-de-zheng-shu-ci-fang-lcof

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    double myPow(double x, int n) {
        long i = n;
        if (n < 0) {
            x = 1 / x;
            i = -i;
        }
        double res = 1;
        while (i > 0) {
            if (i & 1)
                res *= x;
            x *= x;
            i >>= 1;
        }
        return res;
    }
};


// 快速幂，时间复杂度O(logn)，空间复杂度为O(1)