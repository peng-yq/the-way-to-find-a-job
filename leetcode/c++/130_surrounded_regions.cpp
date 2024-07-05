// https://leetcode.cn/problems/surrounded-regions

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void solve(vector<vector<char>>& board) {
        int row = board.size(), col = board[0].size();
        function<void(int, int)> dfs = [&](int i, int j){
            if(i < 0 || i >= row || j < 0 || j >= col || board[i][j] != 'O') 
                return;
            board[i][j] = 'T';
            dfs(i-1, j);
            dfs(i, j - 1);
            dfs(i + 1, j);
            dfs(i, j + 1); 
        };
        for (int i = 0; i < row; ++i) {
            if (board[i][0] == 'O') dfs(i, 0);
            if (board[i][col - 1] == 'O') dfs(i, col - 1);
        }
        for (int i = 0; i < col; ++i) {
            if (board[0][i] == 'O') dfs(0, i);
            if (board[row - 1][i] == 'O') dfs(row - 1, i);
        }
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (board[i][j] == 'O')
                    board[i][j] = 'X';
                if (board[i][j] == 'T')
                    board[i][j] = 'O';
            }   
        }
    }
};

// 与边界上的'O'相邻的'O'肯定是不被围绕的，因此，我们先将边界的'O'及其连接的'O'变成'T'，剩余的'O'则表示可以被围绕的，再把'T'变成'O'
// O(m*n), O(m*n)