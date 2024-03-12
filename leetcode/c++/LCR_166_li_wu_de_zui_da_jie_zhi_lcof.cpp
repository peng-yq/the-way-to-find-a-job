// https://leetcode.cn/problems/li-wu-de-zui-da-jie-zhi-lcof

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int jewelleryValue(vector<vector<int>>& frame) {
        int row = frame.size(), col = frame[0].size();
        vector<vector<int>> dp(row, vector<int>(col, 0));
        dp[0][0] = frame[0][0];
        for (int i = 1; i < row; i++) {
            dp[i][0] = dp[i-1][0] + frame[i][0];
        }
        for (int i = 1; i < col; i++) {
            dp[0][i] = dp[0][i-1] + frame[0][i];
        }
        for (int i = 1; i < row; i++) {
            for (int j = 1; j < col; j++) {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]) + frame[i][j];
            }
        }
        return dp[row-1][col-1];
    }
};

// O(mn)