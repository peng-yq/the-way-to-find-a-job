// https://leetcode.cn/problems/find-first-and-last-position-of-element-in-sorted-array

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findFirst(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target)
                left = mid + 1;
            else 
                right = mid -1;
        }
        return left;
    }
    vector<int> searchRange(vector<int>& nums, int target) {
        int start = findFirst(nums, target);
        if (start == nums.size() || nums[start] != target) 
            return {-1, -1};
        int end = findFirst(nums, target+1) - 1;
        return {start, end};
    }
};

// 十分经典的二分查找，这里边界是选择[0, nums.size()-1]，因此while循环的条件是left <= right
// 换句话说只有当left > right时会结束循环，这里left的范围为[0, nums.size()]
// 然后写里面的left和right变更时，由于是两边闭区间，因此需要写成mid+1和mid-1
// findFirst是查找数组中第一个大于等于target元素的位置，因此如果第一次找到了开始位置，
// 那么闭合位置可以直接通过findFirst(nums, target+1) - 1，如果target+1存在，那么会返回target+1的第一个位置，
// 如果不存在，则会返回大于target+1的第一个位置，这也是target后面的第一个位置，因此都需要-1
// 时间复杂度为O(logn)，空间复杂度为O(1)