// https://leetcode.cn/problems/find-minimum-in-rotated-sorted-array-ii/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findMin(vector<int>& nums) {
        int l = 0, r = nums.size() - 1;
        while (l < r) {
            int i = (l + r) / 2;
            if (nums[i] > nums[r]) l = i +1;
            else if (nums[i] < nums[r]) r = i;
            else r--;
        }
        return nums[l];
    }
};

// 时间复杂度为O(logn)，空间复杂度为O(1)