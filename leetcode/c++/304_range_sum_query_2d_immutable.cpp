// https://leetcode.cn/problems/range-sum-query-2d-immutable/description/

#include <bits/stdc++.h>
using namespace std;

class NumMatrix {
public:
    vector<vector<int>> res;
    NumMatrix(vector<vector<int>>& matrix) {
        res.resize(matrix.size() + 1, vector<int>(matrix[0].size() + 1, 0));
        for (int i = 1; i < matrix.size() + 1; i++) {
            for (int j = 1; j < matrix[0].size() + 1; j++) {
                res[i][j] = res[i][j-1] + res[i-1][j] - res[i-1][j-1] + matrix[i-1][j-1];
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        return res[row2+1][col2+1] - res[row2+1][col1] - res[row1][col2+1] + res[row1][col1];
    }
};

// 二维前缀和，注意下标是从0开始的，需要+1