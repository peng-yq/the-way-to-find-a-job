// https://leetcode.cn/problems/trapping-rain-water

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        int res = 0, left = 0, right = height.size() - 1, left_max = 0, right_max = 0;
        while (left < right) {
            left_max = max(left_max, height[left]);
            right_max = max(right_max, height[right]);
            if (left_max < right_max) {
                res += left_max - height[left];
                left++;
            }
            else {
                res += right_max - height[right];
                right--;
            }
        }
        return res;
    }
};

// 大名鼎鼎的“接雨水”，有很多种做法：
// 1. 前缀和保存左右隔板最大高度，或者双指针来减少空间复杂度，这两都是竖着求容量，和盛最多水的容器很像，关键在于两边隔板的高度最小的那个
// 2. 可以通过单调栈，这样是横着求，空间复杂度为O(n)
// 时间复杂度为O(n)，空间复杂度为O(1)