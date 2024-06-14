// https://leetcode.cn/problems/game-of-life

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        int m = board.size(), n = board[0].size();
        auto affect = [&](int x, int y) {
            for (int i = x - 1; i <= x + 1; ++i) {
                for (int j = y - 1; j <= y + 1; ++j) {
                    if (i < 0 || i >= m || j < 0 || j >= n || (i == x && j == y)) 
                        continue;
                    board[i][j] += 10;
                }
            }
        };
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) 
                if (board[i][j] % 10 == 1)
                    affect(i, j);
        }
        auto change = [&](int x, int y) {
            if (board[x][y] / 10 == 3)
                board[x][y] = 1;
            else if (board[x][y] / 10 == 2 && board[x][y] % 10 == 1)
                board[x][y] = 1;
            else 
                board[x][y] = 0;
        };
         for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) 
                change(i, j);
        }
    }
};

// 只有2种情况细胞会保持/变成活细胞：
// 1. 周围8个位置有3个活细胞，不管是死细胞还是活细胞，最终都是活细胞
// 2. 周围8个位置有2个活细胞，并且当前细胞是活细胞，最终是活细胞
// 其他都是死细胞
// 与其对每个细胞都去看周围的8个细胞，转变为让活细胞去影响周围的8个细胞，被影响的值+10，这样10位上的数字表示周围8个位置的活细胞数
// 个位上的数表示当前细胞是活细胞还是死细胞
// 再对每个细胞进行判断最终的细胞状态
// O(mn)，O(1)