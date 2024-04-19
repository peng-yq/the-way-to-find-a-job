// https://leetcode.cn/problems/maximum-product-subarray

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int tmp = 1, res = nums[0];
        for (int num : nums) {
            tmp *= num;
            if (tmp > res)
                res = tmp;
            if (num == 0)
                tmp = 1;
        }
        tmp = 1;
        for (int i = nums.size() - 1; i >= 0; --i) {
            tmp *= nums[i];
            if (tmp > res)
                res = tmp;
            if (nums[i] == 0)
                tmp = 1;
        }
        return res;
    }
};

// 极其巧妙的方法，时间复杂度为O(n)，空间复杂度为O(1)
// 假如数组中没有0时，偶数个负数最大值为全部元素的乘积，
// 奇数个元素需要比较从左到右乘到最后一个负数的最大值和从右到左乘到最后一个负数的最大值（因为要求连续子数组）
// 如果有0，则0把数组分成左右两个部分，也是按上述办法进行计算即可，到编程也就是重设置为1.

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size(), res = INT_MIN;
        vector<int> min_dp(n+1), max_dp(n+1);
        min_dp[0] = 1, max_dp[0] = 1;
        for (int i = 1; i <= n; ++i) {
            min_dp[i] = min(min_dp[i-1] * nums[i-1], min(nums[i-1], max_dp[i-1] * nums[i-1]));
            max_dp[i] = max(min_dp[i-1] * nums[i-1], max(nums[i-1], max_dp[i-1] * nums[i-1]));
            res = max(res, max_dp[i]);
        }
        return res;
    }
};

// 动态规划，时间复杂度为O(n)，空间复杂度为O(n)
// 需要保存前一个子数组的最大值和最小值，因为最大值可能变为最小值，最小值可能变为最大值，当然也可以从这个数开始