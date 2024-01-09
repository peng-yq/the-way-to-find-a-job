// https://leetcode.cn/problems/find-pivot-index/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        int n = nums.size(), res_left = 0, res_right = 0;
        vector<int>left(n);
        vector<int>right(n);
        for (int i = 0; i < n; i++) {
            left[i] = res_left;
            res_left += nums[i];
        }
        for (int i = n-1; i >= 0; i--) {
            right[i] = res_right;
            res_right += nums[i];
        }
        for (int i = 0; i < n; i++) {
            if (left[i] == right[i]) return i;
        }
        return -1;
    }
};

// 有点笨，时间和空间复杂度都是O(n)，这种解法也是最容易想到的
// 下面是k神的解法，空间复杂度为O(1)，虽然时间复杂度也是O(n)，但只遍历一次

class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        int sumLeft = 0, sumRight = accumulate(nums.begin(), nums.end(), 0);
        for (int i = 0; i < nums.size(); i++) {
            sumRight -= nums[i];
            // 若左侧元素和等于右侧元素和，返回中心下标 i
            if (sumLeft == sumRight)
                return i;
            sumLeft += nums[i];
        }
        return -1;
    }
};