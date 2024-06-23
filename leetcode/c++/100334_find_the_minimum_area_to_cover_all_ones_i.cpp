// https://leetcode.cn/problems/find-the-minimum-area-to-cover-all-ones-i

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumArea(vector<vector<int>>& grid) {
        int left = grid[0].size(), right = 0, top = grid.size(), bottom = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                if (grid[i][j]) {
                    left = min(left, j);
                    right = max(right, j);
                    top = min(top, i);
                    bottom = i;
                }
            }
        }
        return (right - left + 1) * (bottom - top + 1);
    }
};

// 记录上下左右1的值
// O(mn)，O(1)