// https://leetcode.cn/problems/number-of-islands

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void dfs(vector<vector<char>>& grid, int i, int j) {
        int row = grid.size(), col = grid[0].size();
        if (i < 0 || i >= row || j < 0 || j >= col || grid[i][j] != '1')
            return;
        grid[i][j] = '0';
        dfs(grid, i+1, j);
        dfs(grid, i-1, j);
        dfs(grid, i, j+1);
        dfs(grid, i, j-1);
    }
    int numIslands(vector<vector<char>>& grid) {
        int row = grid.size(), col = grid[0].size(), res = 0;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (grid[i][j] == '1') {
                    dfs(grid, i, j);
                    res++;
                }
            }
        }
        return res;
    }
};

// 把相邻的大陆污染就好了，时间和空间复杂度为O(mn)