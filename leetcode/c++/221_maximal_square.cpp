// https://leetcode.cn/problems/maximal-square

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> dp(m, vector<int>(n));
        int maxLen = 0;
        for (int i = 0; i < m; ++i) {
            dp[i][0] = matrix[i][0] - '0';
            maxLen = max(maxLen, dp[i][0]);
        }
        for (int j = 0; j < n; ++j) {
            dp[0][j] = matrix[0][j] - '0';
            maxLen = max(maxLen, dp[0][j]);
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (matrix[i][j] == '0')
                    continue;
                dp[i][j] = min(min(dp[i - 1][j - 1], dp[i - 1][j]), dp[i][j - 1]) + 1;
                maxLen = max(maxLen, dp[i][j]);
            }
        }
        return maxLen * maxLen;
    }
};


// dp[i][j]表示以[i][j]为右下角（matrix[i][j]为1）的最大正方形边长
// 需要看垂直向上1的个数，左边的1的个数，和左上角1的个数，选取最小值+1