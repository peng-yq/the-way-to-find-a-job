// https://leetcode.cn/problems/find-the-width-of-columns-of-a-grid

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int len(int num) {
        if (num == 0)
            return 1;
        int res = num > 0 ? 0 : 1;
        while (num) {
            num /= 10;
            res++;
        }
        return res;
    }
    vector<int> findColumnWidth(vector<vector<int>>& grid) {
        vector<int> res;
        int row = grid.size(), col = grid[0].size();
        for (int i = 0; i < col; ++i) {
            int tmp = 0;
            for (int j = 0; j < row; ++j) {
                tmp = max(tmp, len(grid[j][i]));
            }
            res.push_back(tmp);
        }
        return res;
    }
};

// 最简单的一集，时间复杂度O(mn*log(maxnum))，空间复杂度O(1)
// 求位数还可以(int)to_string().size()