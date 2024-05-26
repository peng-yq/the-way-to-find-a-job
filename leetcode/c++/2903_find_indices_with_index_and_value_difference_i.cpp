// https://leetcode.cn/problems/find-indices-with-index-and-value-difference-i

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findIndices(vector<int>& nums, int indexDifference, int valueDifference) {
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            for (int j = i + indexDifference; j < n; ++j) {
                if (abs(nums[i] - nums[j]) >= valueDifference)
                    return {i, j};
            }
        }
        return {-1, -1};
    }
};

// 简单题，1100分，数据量这么小，我直接暴力啊，O(n^2),O(1)