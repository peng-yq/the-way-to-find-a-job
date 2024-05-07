// https://leetcode.cn/problems/cherry-pickup-ii

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int row = grid.size(), col = grid[0].size();
        vector<vector<vector<int>>> cache(row, vector<vector<int>>(col, vector<int>(col, -1)));
        function<int(int, int, int)> dfs = [&](int i, int j, int k) -> int {
            if (i == row || j < 0 || j >= col || k < 0 || k >= col)
                return 0;
            int& res = cache[i][j][k];
            if (res != -1)
                return res;
            for (int m = j - 1; m <= j + 1; ++m) {
                for (int n = k - 1; n <= k + 1; ++n) {
                    res = max(res, dfs(i + 1, m, n));
                }
            }
            res += grid[i][j] + (j == k ? 0 : grid[i][k]);
            return res;
        };
        return dfs(0, 0, col - 1);
    }
};

// 动态规划，这里只看懂了递归+记忆化搜索的解法
// 定义动态规划状态为dfs(i, j, k)表示A，B两个机器人分别从[i,j]和[i,k]的位置出发到最底行所能摘得的最大樱桃数
// 并使用一个三维数组cache来记录递归过程中的结果，从而避免重复无用递归
// 记忆化的基本套路是比如dfs(i, j, k)有3个参数，我们就使用3维数组，注意初始化的值不能与后面记忆化的值相同，初始化为一个不可能出现的值；
// 在递归的过程中首先检查记忆化数组中是否已经有保存值，否则进行递归，并更新记忆化数组中的值，也就是需要使用引用或指针
// A，B2个机器人可能有3*3共9种结果，纵坐标大家都往下一格，主要变化在横坐标上，范围分别为[j-1, j+1]和[k-1, k+1]，使用2层循环即可
// 注意边界条件，i == row时需要停止递归，我们直接返回0即可，
// 由于我们初始值定义的是-1，在最后一行的求解中，res = max(res, dfs(i + 1, m, n))的结果会为0
// 此外，当j和k相同时，也就是A，B两个机器人都走到同一个格子，只加一次
// 时间复杂度为O(m*n^2)，空间复杂度为O(m*n^2)