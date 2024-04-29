// https://leetcode.cn/problems/sort-the-matrix-diagonally

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> diagonalSort(vector<vector<int>>& mat) {
        int row = mat.size(), col = mat[0].size();
        vector<vector<int>> nums(row + col -1);
        vector<int> index(row + col - 1, 0);
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                nums[i-j+col-1].push_back(mat[i][j]);
            }
        }
        for (auto& num : nums) {
            sort(num.begin(), num.end());
        }
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                int k = i - j + col - 1;
                mat[i][j] = nums[k][index[k]];
                index[k]++;
            }
        }
        return mat;
    }
};

// 硬模拟，O(mn)，O(mn)