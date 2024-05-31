// https://leetcode.cn/problems/find-missing-and-repeated-values

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findMissingAndRepeatedValues(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size(), a, b;
        vector<int> count(n * n, 0);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (++count[grid[i][j] - 1] == 2)
                    a = grid[i][j];
            }
        }
        for (int i = 0; i < n * n; ++i) {
            if (count[i] == 0) {
                b = i + 1;
                break;
            }
        }
        return {a, b};
    }
};

// O(mn)，O(n^2)