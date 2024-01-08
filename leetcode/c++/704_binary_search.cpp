// https://leetcode.cn/problems/binary-search/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0, r = nums.size() - 1, i;
        while (l <= r) {
            i = (l + r) / 2;
            if (nums[i] < target) l = i + 1;
            else if (nums[i] > target) r = i - 1;
            else return i;
        }
        return -1;
    }
};

// 时间复杂度为O(logN)，空间复杂度为O(1)