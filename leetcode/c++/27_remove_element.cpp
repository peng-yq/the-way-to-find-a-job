// https://leetcode.cn/problems/remove-element

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int n = nums.size(), i = 0, j = n - 1, res = 0;
        while (i < j) {
            while (nums[i] != val && i < j) {
                ++i;
                ++res;
            }
            while (nums[j] == val && i < j)
                --j;            
            if (i < j) {
                swap(nums[i], nums[j]);
            }
        }
        if (i == j) {
            res += nums[i] != val;
        }
        return res;
    }
};

// 双指针，O(n), O(1)

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int k = 0, res = 0;
        for (auto num : nums) {
            if (num != val) {
                ++res;
                nums[k++] = num;
            }
        }
        return res;
    }
};

// 简单的做，O(n)，O(1)