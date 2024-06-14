// https://leetcode.cn/problems/valid-sudoku

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        vector<vector<int>> row(9, vector<int>(10, 0));
        vector<vector<int>> col(9, vector<int>(10, 0));
        vector<vector<int>> box(9, vector<int>(10, 0));
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] == '.') continue;
                int tmp = board[i][j] - '0';
                if (row[i][tmp]) return false;
                if (col[j][tmp]) return false;
                if (box[(i / 3) * 3 + j / 3][tmp]) return false;
                row[i][tmp] = 1;
                col[j][tmp] = 1;
                box[(i / 3) * 3 + j / 3][tmp] = 1;
            }
        }
        return true;
    }
};

// 用三个哈希表记录，行、列和九宫格
// 时间复杂度O(1)，空间复杂度O(1)