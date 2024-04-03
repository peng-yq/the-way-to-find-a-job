// https://leetcode.cn/problems/find-minimum-in-rotated-sorted-array

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] > nums[right])
                left = mid + 1;
            else 
                right = mid; 
        }
        return nums[left];
    }
};

// 这里所有数是唯一，因此不讨论nums[mid] == nums[right]的情况了（right--）
// 时间复杂度为O(logn)，空间复杂度为O(1)