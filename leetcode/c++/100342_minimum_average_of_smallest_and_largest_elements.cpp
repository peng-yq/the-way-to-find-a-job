// https://leetcode.cn/problems/minimum-average-of-smallest-and-largest-elements

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    double minimumAverage(vector<int>& nums) {
        int n = nums.size(), i = 0, j = n - 1;
        double res = 100.0;
        sort(nums.begin(), nums.end());
        while (i < j) {
            res = min(res, (nums[i] + nums[j]) / 2.0);
            ++i;
            --j;
        }
        return res;
    }
};

// 排序+双指针
// O(nlogn)，O(1)