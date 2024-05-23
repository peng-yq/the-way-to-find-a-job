// https://leetcode.cn/problems/find-the-longest-equal-subarray

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestEqualSubarray(vector<int>& nums, int k) {
        int n = nums.size(), res = 0;
        vector<vector<int>> numMap(n + 1);
        for (int i = 0; i < n; ++i) {
            numMap[nums[i]].push_back(i);
        }
        for (auto num : numMap) {
            for (int i = 0, j = 0; j < num.size(); ++j) {
                while(num[j] - num[i] + 1 - (j - i + 1) > k) 
                    ++i;
                res = max(res, j - i + 1);
            }
        }
        return res;
    }
};

// 分组+滑动窗口，统计相同元素的下标，并滑动窗口求取最大值
// num[j] - num[i] + 1 - (j - i + 1)表示相同元素中其他元素的个数
// 时间复杂度和空间复杂度均为O(n)