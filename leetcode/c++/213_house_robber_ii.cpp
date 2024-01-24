// https://leetcode.cn/problems/house-robber-ii/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) {
            return nums[0];
        } else if (n == 2) {
            return max(nums[0], nums[1]);
        }
        vector<int>dp(n);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        for (int i = 2; i < n-1; i++) {
            dp[i] = max(dp[i-1], dp[i-2] + nums[i]);
        }
        int max1 = dp[n-2];
        dp[1] = nums[1];
        dp[2] = max(nums[1], nums[2]);
         for (int i = 3; i < n; i++) {
            dp[i] = max(dp[i-1], dp[i-2] + nums[i]);
        }
        int max2 = dp[n - 1];
        return max(max1, max2);
    }
};