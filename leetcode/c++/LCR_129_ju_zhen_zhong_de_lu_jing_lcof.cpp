// https://leetcode.cn/problems/ju-zhen-zhong-de-lu-jing-lcof/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool wordPuzzle(vector<vector<char>>& grid, string target) {
        int row = grid.size();
        int col = grid[0].size();
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (dfs(grid, target, i, j, 0)) return true;
            }
        }
        return false;
    }
private:
    bool dfs(vector<vector<char>>& grid, string &target, int i, int j, int k) {
        int row = grid.size();
        int col = grid[0].size();
        if (i >= row || i < 0 || j >= col || j < 0 || grid[i][j] != target[k]) return false;
        if (k == target.size() -1) return true;
        grid[i][j] = ' ';
        bool res = dfs(grid, target, i+1, j, k+1) || dfs(grid, target, i-1, j, k+1) || dfs(grid, target, i, j+1, k+1) || dfs(grid, target, i, j-1, k+1);
        grid[i][j] = target[k];
        return res;
    }
};

// 这里用引用的方式传入target可以显著降低时间和内存，
// 通过值传递一个对象（如字符串）时，每次函数调用都会创建对象的一个副本。
// 如果对象较大（例如一个长字符串），这会导致显著的内存开销。
// 相比之下，引用传递仅传递对象的引用（或地址），而不是整个对象，因此内存使用显著减少。

// 时间复杂度为O(mn*4^k)，空间复杂度为O(k)