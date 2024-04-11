// https://leetcode.cn/problems/n-queens

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        vector<string> tmp(n, string(n, '.'));
        vector<bool> cols(n, false);
        vector<bool> diags1(2*n-1, false);
        vector<bool> diags2(2*n-1, false);
        function<void(int)> dfs = [&](int row) {
            if (row == n) {
                res.push_back(tmp);
                return;
            }
            for (int col = 0; col < n; col++) {
                if (cols[col] || diags1[row-col+n-1] || diags2[row+col])
                    continue;
                cols[col] = diags1[row-col+n-1] = diags2[row+col] = true;
                tmp[row][col] = 'Q';
                dfs(row+1);
                tmp[row][col] = '.';
                cols[col] = diags1[row-col+n-1] = diags2[row+col] = false;
            }
        };
        dfs(0);
        return res;
    }
};

// 关键在于需要保证每一行就一个皇后，并且每一列和两个斜线都只有一个
// 时间复杂度为O(n!)，空间复杂度为O(n^2)