// https://leetcode.cn/problems/find-the-most-competitive-subsequence

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> mostCompetitive(vector<int>& nums, int k) {
        vector<int> res;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            while (!res.empty() && res.back() > nums[i] && res.size() + n - i - 1 >= k)
                res.pop_back();
            if (res.size() < k)
                res.push_back(nums[i]);
        }
        return res;
    }
};

// 单调栈，直接用数组模拟单调递增栈，左边的小的元素拥有更高的优先级
// 在更新单调栈的过程中需要保证剩余的数+栈中已有的数+1 >= k
// 并且只有在栈中大小小于k时，才添加元素
// 时间复杂度为O(n)，空间复杂度为O(n) 