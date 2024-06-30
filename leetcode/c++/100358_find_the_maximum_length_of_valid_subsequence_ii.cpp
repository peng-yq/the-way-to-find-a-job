// https://leetcode.cn/problems/find-the-maximum-length-of-valid-subsequence-ii

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumLength(vector<int>& nums, int k) {
        int res = 0;
        vector<vector<int>>dp(k, vector<int>(k, 0));
        for (auto num : nums) {
            int x = num % k;
            for (int y = 0; y < k; ++y) {
                dp[y][x] = dp[x][y] + 1;
                res = max(res, dp[y][x]);
            }
        }
        return res;
    }
};

// 单调序列 x y x y，再枚举
// 时间复杂度O(nk)