// https://leetcode.cn/problems/fei-bo-na-qi-shu-lie-lcof

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int fib(int n) {
        if (n < 2)
            return n;
        const int mod = 1000000007;
        int dp[n+1];
        dp[0] =0, dp[1] = 1;
        for (int i = 2; i <= n; i++)
            dp[i] = (dp[i-1]  + dp[i-2]) % mod;
        return dp[n];
    }
};

// 时间复杂度为O(n)，空间复杂度为O(n)，可以优化为O(1)，见go版本