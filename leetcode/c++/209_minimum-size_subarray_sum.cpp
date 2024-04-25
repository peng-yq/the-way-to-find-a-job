// https://leetcode.cn/problems/minimum-size-subarray-sum

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int res = INT_MAX, n = nums.size(), sum = 0;
        for (int i = 0, j = 0; j < n; ++j) {
            sum += nums[j];
            while (sum >= target) {
                res = min(res, j - i + 1);
                sum -= nums[i++];
            }
        }
        return res == INT_MAX? 0 : res;
    }
};

// 不定长滑动窗口，用while就完事了，只要当前的和大于等于target，就收缩窗口
// O(n)，O(1)