// https://leetcode.cn/problems/search-a-2d-matrix

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int row = matrix.size(), col = matrix[0].size();
        int i = 0, j = col - 1;
        while (0 <= i && i < row && 0 <= j && j < col) {
            if (matrix[i][j] == target)
                return true;
            else if (matrix[i][j] > target)
                j--;
            else 
                i++;
        }
        return false;
    }
};

// 老题了，时间复杂度为O(m+n)，空间复杂度为O(1)