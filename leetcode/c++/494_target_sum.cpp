// https://leetcode.cn/problems/target-sum

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = 0, n = nums.size();
        for (int num : nums)
            sum += num;
        sum += target;
        if (sum < 0 || (sum & 1) == 1)
            return 0;
        sum /= 2;
        vector<vector<int>>dp(n+1, vector<int>(sum+1, 0));
        dp[0][0] = 1;
        for (int i = 1; i < n+1; i++) {
            for (int j = 0; j < sum+1; j++) {
                if (nums[i-1] > j)
                    dp[i][j] = dp[i-1][j];
                else 
                    dp[i][j] = dp[i-1][j] + dp[i-1][j-nums[i-1]];
            }
        }
        return dp[n][sum];
    }
};

// x为正的数之和，y为负的数之和
// x-y=target, x+y=sum
// x = (sum+target)/2
// 0 <= nums[i] <= 1000，并且为整数->(sum+target) >= 0并且为偶数 
// 转换为0，1背包问题
// 注意dp数组的初始化，时间复杂度为O(mn)，空间复杂度为O(MN)