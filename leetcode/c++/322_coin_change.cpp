// https://leetcode.cn/problems/coin-change

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int MAX = amount + 1;
        int n = coins.size();
        vector<vector<int>> dp(n+1, vector<int>(amount+1, MAX));
        for (int i = 0; i < n+1; i++)
            dp[i][0] = 0;
        for (int i = 1; i < n+1; i++) {
            for (int j = 1; j < amount+1; j++) {
                if (coins[i-1] > j) {
                    dp[i][j] = dp[i-1][j];
                }
                else {
                    dp[i][j] = min(dp[i-1][j], dp[i][j-coins[i-1]] + 1);
                }
            }
        }
        return dp[n][amount] == MAX? -1:dp[n][amount];
    }
};

// 完全背包问题，注意初始化一开始全为MAX（除了j=0的情况，也就是金额为0时0个硬币就能凑出来）
// 时间复杂度O(nm)，空间复杂度为O(nm)，可以优化空间复杂度