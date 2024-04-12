// https://leetcode.cn/problems/find-champion-i

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findChampion(vector<vector<int>>& grid) {
        int n = grid.size(), res = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    if (res != i) {
                        res = grid[i][res] == 1? i : res;
                    }
                }
            }
        }
        return res;
    }
};