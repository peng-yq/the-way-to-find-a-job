// https://leetcode.cn/problems/qing-wa-tiao-tai-jie-wen-ti-lcof

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int trainWays(int num) {
        if (num < 2)
            return 1;
        const int mod = 1000000007;
        int a = 1, b = 1, sum = 0;
        for (int i = 2; i <= num; i++) {
            sum = (a + b) % mod;
            a = b;
            b = sum;
        }
        return sum;
    }
};

// O(n), O(1)