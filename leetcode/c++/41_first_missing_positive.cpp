// https://leetcode.cn/problems/first-missing-positive

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i])
                swap(nums[i], nums[nums[i] - 1]);
        }
        for (int i = 0; i < n; ++i) {
            if (nums[i] != i + 1)
                return i + 1;
        }
        return n + 1;
    }
};

// 原地哈希，因为是求数组中没有出现的最小整数，因此我们只关注范围为[1-n]的元素，只需要找出这个范围中没有出现的最小正整数即可
// 使用原数组做哈希表，第一次遍历，将数组中处于以上范围的元素放置正确的位置，nums[i] 放到 nums[nums[i-1]-1]处
// 即元素4放到索引3的位置（求最小正整数，并且数组大小为n）
// 再通过一次遍历，找出最小正整数即可