// https://leetcode.cn/problems/maximum-subarray/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        vector<int>dp(nums.size());
        dp[0] = nums[0];
        int max_sum = dp[0];
        for (int i = 1; i < nums.size(); i++) {
            if (dp[i-1] >= 0)
                dp[i] = dp[i-1] + nums[i];
            else 
                dp[i] = nums[i];
            max_sum = max(max_sum, dp[i]);
        }
        return max_sum;
    }
};

// 时间复杂度为O(n)，空间复杂度为O(n)