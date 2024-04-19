// https://leetcode.cn/problems/partition-equal-subset-sum

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for (int num : nums)
            sum += num;
        if (sum & 1)
            return false;
        sum /= 2;
        vector<vector<bool>> dp(nums.size() + 1, vector<bool>(sum + 1, false));
        for (int i = 0; i <= nums.size(); ++i)
            dp[i][0] = true;
        for (int i = 1; i <= nums.size(); ++i) {
            for (int j = 1; j <= sum; ++j) {
                if (nums[i-1] > j)
                    dp[i][j] = dp[i-1][j];
                else 
                    dp[i][j] = dp[i-1][j] || dp[i-1][j-nums[i-1]]; 
            }
        }
        return dp[nums.size()][sum];
    }
};

// 0-1背包问题，分割等和子集，也就是找是否能凑出sum/2，如果能凑出那么另外的元素肯定也能组成sum/2
// 时空复杂度比较爆炸，O(mn)

// 一维dp优化

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for (int num : nums)
            sum += num;
        if (sum % 2 != 0)  
            return false;
        sum /= 2;
        vector<bool> dp(sum + 1, false);
        dp[0] = true;  
        for (int num : nums) {
            for (int j = sum; j >= num; --j) {
                dp[j] = dp[j] || dp[j - num];
            }
        }
        return dp[sum];
    }
};
