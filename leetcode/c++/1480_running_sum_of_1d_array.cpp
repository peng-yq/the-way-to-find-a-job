// https://leetcode.cn/problems/running-sum-of-1d-array/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        if (nums.size() < 2)    
            return nums;
        vector<int>dp(nums.size());
        dp[0] = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            dp[i] = dp[i-1] + nums[i];
        }
        return dp;
    }
};

// 时间复杂度和空间复杂度为O(n)