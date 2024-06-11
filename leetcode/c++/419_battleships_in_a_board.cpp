// https://leetcode.cn/problems/battleships-in-a-board

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countBattleships(vector<vector<char>>& board) {
        int row = board.size(), col = board[0].size(), res = 0;
        function<void(int, int)> dfs = [&](int i, int j) {
            if (i < 0 || i >= row || j < 0 || j >= col || board[i][j] != 'X')
                return;
            board[i][j] = '.';
            dfs(i + 1, j);
            dfs(i - 1, j);
            dfs(i, j + 1);
            dfs(i, j - 1);
        };
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (board[i][j] == 'X') {
                    ++res;
                    dfs(i, j);
                }
            }
        }
        return res;
    }
};

// 和岛屿数量一样的题，时间和空间复杂度都是O(r*c)