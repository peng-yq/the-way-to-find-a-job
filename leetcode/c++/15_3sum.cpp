// https://leetcode.cn/problems/3sum/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>>res;
        for (int k = 0; k < nums.size() - 2; k++) {
            if (nums[k] > 0) break;
            if (k > 0 && nums[k] == nums[k-1]) continue;
            int i = k + 1, j = nums.size() - 1;
            while (i < j) {
                int sum = nums[k] + nums[i] + nums[j];
                if (sum < 0) i++;
                if (sum > 0) j--;
                if (sum == 0) {
                    res.push_back(vector<int>{nums[k], nums[i], nums[j]});
                    while (i < j && nums[i] == nums[++i]) continue;
                    while (i < j && nums[j] == nums[--j]) continue;
                }
            }
        }
        return res;
    }
};

// 时间复杂度为O(n^2)，空间复杂度为O(1)