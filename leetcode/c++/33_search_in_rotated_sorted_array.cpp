// https://leetcode.cn/problems/search-in-rotated-sorted-array

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right-left) / 2;
            if (nums[mid] == target)
                return mid;
            if (nums[mid] < nums[right]) {
                if (nums[mid] < target && target <= nums[right])
                    left = mid + 1;
                else 
                    right = mid - 1;
            } else {
                if (nums[left] <= target && target < nums[mid])
                    right = mid - 1;
                else
                    left = mid + 1;
            }
        }
        return -1;
    }
};

// 一次二分，通过nums[mid] < nums[right] （也可以和nums[left]判断）判断(mid, right]和[left, mid]这两个区间哪个是有序的（另外一个则是部分有序的），
// 然后根据target再这个区间的关系，来更新left或者right的值，再进行二分，时间复杂度为O(logn)，空间复杂度为O(1)