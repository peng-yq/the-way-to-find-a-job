// https://leetcode.cn/problems/word-search/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        row = board.size();
        col = board[0].size();
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (dfs(board, word, i, j, 0))
                    return true;
            }
        }
        return false;
    }
private:
    int row, col;
    bool dfs(vector<vector<char>>& board, string word, int i, int j, int k) {
        if (i < 0 || i >= row || j < 0 || j >= col || board[i][j] != word[k] ) return false;
        if (k == word.size() - 1) return true;
        board[i][j] = '\0';
        bool res = dfs(board, word, i + 1, j, k + 1) || dfs(board, word, i, j + 1, k + 1) || dfs(board, word, i - 1, j, k + 1) || dfs(board, word, i, j - 1, k + 1);
        board[i][j] = word[k];
        return res;
    }
};

// 时间复杂度为O(mn*3^k)，空间复杂度为O(k)，最差K=mn