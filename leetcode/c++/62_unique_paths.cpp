// https://leetcode.cn/problems/unique-paths

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n));
        for (int i = 0; i < m; ++i)
            dp[i][0] = 1;
        for (int i = 0; i < n; ++i)
            dp[0][i] = 1;
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
        return dp[m-1][n-1];
    }
};

// 动态规划，时间复杂度为O(mn)，空间复杂度为O(mn)，空间有优化的余地