// https://leetcode.cn/problems/minimum-path-sum/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int row = grid.size();
        if (row == 0)
            return 0;
        int col = grid[0].size();
        if (col == 0)
            return 0;
        vector<vector<int>>dp(row, vector<int>(col));
        dp[0][0] = grid[0][0];
        for (int i = 1; i < row; i++) 
            dp[i][0] = dp[i-1][0] + grid[i][0];
        for (int i = 1; i < col; i++) 
            dp[0][i] = dp[0][i-1] + grid[0][i];
        for (int i = 1; i < row; i++) {
            for (int j = 1; j < col; j++) {
                dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j];
            }
        }
        return dp[row-1][col-1];
    }
};

// 时间复杂度为O(m*n)，空间复杂度为O(m*n)