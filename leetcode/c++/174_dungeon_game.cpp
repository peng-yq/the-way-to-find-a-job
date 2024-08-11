// https://leetcode.cn/problems/dungeon-game/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int m = dungeon.size(), n = dungeon[0].size();
        vector<vector<int>> dp(m, vector<int>(n, INT_MAX));
        dp[m - 1][n - 1] = max(1, 1 - dungeon[m - 1][n - 1]);
        for (int i = m - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                if (i < m - 1)
                    dp[i][j] = min(dp[i][j], max(1, dp[i + 1][j] - dungeon[i][j]));
                if (j < n - 1)
                    dp[i][j] = min(dp[i][j], max(1, dp[i][j + 1] - dungeon[i][j]));
            }
        }
        return dp[0][0];
    }
};

/*
定义状态：dp[i][j] 表示骑士从位置 (i, j) 到达终点 (m-1, n-1) 所需的最小初始生命值。

初始化终点：骑士到达终点时，所需的最小初始生命值取决于终点的值。如果终点的值为负，骑士需要至少 1 - dungeon[m-1][n-1] 的生命值才能存活；

如果为正，骑士至少需要 1 点生命值。因此 dp[m-1][n-1] = max(1, 1 - dungeon[m-1][n-1])。

状态转移：从终点 (m-1, n-1) 开始，向左和向上更新 dp 数组。
对于位置 (i, j)，骑士可以向右走到 (i, j+1) 或向下走到 (i+1, j)。
无论哪种情况，骑士在 (i, j) 需要的最小初始生命值为：
dp[i][j] = min(max(1, dp[i+1][j] - dungeon[i][j]), max(1, dp[i][j+1] - dungeon[i][j]))
这里的 max(1, ...) 确保生命值始终为正数，即骑士至少需要 1 点生命值。

返回结果：最后，dp[0][0] 就是骑士从起点 (0, 0) 出发所需的最小初始生命值。
*/