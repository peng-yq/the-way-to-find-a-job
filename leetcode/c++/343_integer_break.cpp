// https://leetcode.cn/problems/integer-break/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int integerBreak(int n) {
        if (n <= 3)
            return n-1;
        int a = n / 3, b = n % 3;
        if (b == 0)
            return pow(3, a);
        if (b == 2)
            return pow(3, a) * 2;
        return pow(3, a-1) * 4;
    }
};

// 数论的解法，时间复杂度为O(1)，空间复杂度为O(1)，但pow算法有点耗时间，最后的提交时间和动态规划差不多

class Solution {
public:
    int integerBreak(int n) {
       vector<int>dp(n + 1, 0);
       dp[2] = 1;
       for (int i = 3; i <= n; i++) {
           for (int j = 1; j < i-1; j++) {
               dp[i] = max(dp[i], max(j * (i-j), j * dp[i-j]));
           }
       }
       return dp[n];
    }
};

// 动态规划的解法，时间复杂度为O(n^2)，空间复杂度为O(n)