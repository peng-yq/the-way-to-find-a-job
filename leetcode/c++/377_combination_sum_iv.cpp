// https://leetcode.cn/problems/combination-sum-iv

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    unordered_map<int, int> cache;
    void dfs(vector<int>& nums, int target, int& res) {
        if (target == 0) {
            res++;
            return;
        }
        if (cache.count(target)) {
            res += cache[target];
            return;
        }
        int tmp = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] <= target)
                dfs(nums, target-nums[i], tmp);
            else
                break;
        }
        cache[target] = tmp;
        res += tmp;
    }
    int combinationSum4(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int res = 0;
        dfs(nums, target, res);
        return res;
    }
};

// 回溯，记忆化搜索避免超时，时间复杂度为O(target*nums.size())，空间复杂度为O(target)
// 动态规划，爬楼梯的进阶版，有个测试样例很恶心，加了unsigned int就能过了，奇怪的是long long过不了，怪了，时间复杂度和空间复杂度一致

class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        vector<unsigned int> dp(target + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= target; ++i) {
            for (int num : nums) {
                if (num <= i) 
                    dp[i] += dp[i-num];
            }
        }
        return dp[target];
    }
};