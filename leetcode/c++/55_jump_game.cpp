// https://leetcode.cn/problems/jump-game

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int maxlength = 0, n = nums.size();
        for (int i = 0; i < n; i++) {
            if (i > maxlength)
                return false;
            maxlength = max(maxlength, i + nums[i]);
            if (maxlength >= n - 1)
                return true;
        }
        return maxlength >= (n-1);
    }
};

// 时间复杂度为O(n)，空间复杂度为O(1)