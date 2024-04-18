// https://leetcode.cn/problems/perfect-squares

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n+1, INT_MAX);
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j * j <= i; ++j)
                dp[i] = min(dp[i], dp[i-j*j] + 1);
        }
        return dp[n];
    }
};

// 时间复杂度为O(o^3/2)，空间复杂度为O(n)
// 完全背包问题，即每个完全平方数可以多次选，并且要求和均为完全平方数组成，那么就是dp[i-j*j]+1