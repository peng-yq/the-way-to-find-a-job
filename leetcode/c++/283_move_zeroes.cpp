// https://leetcode.cn/problems/move-zeroes

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        for (int l = 0, r = 0; r < nums.size(); r++) {
            if (nums[r] != 0) 
                swap(nums[l++], nums[r]);
        }
    }
};

// 双指针，l左边的全为非0的数，l到r全为0，时间复杂度为O(n)，空间复杂度为O(1);