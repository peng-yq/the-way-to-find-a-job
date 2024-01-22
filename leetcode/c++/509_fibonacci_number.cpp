// https://leetcode.cn/problems/fibonacci-number/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int fib(int n) {
        if (n <= 1)
            return n;
        vector<int>dp(n+1);
        dp[0] = 0;
        dp[1] = 1;
        for (int i = 2; i <= n; i++) {
            dp[i] = dp[i-1] + dp[i-2];
        }
        return dp[n];
    }
};

// 时间复杂度和空间复杂度都为O(n)