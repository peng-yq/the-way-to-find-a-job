// https://leetcode.cn/problems/majority-element/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int res = nums[0], sum = 0;
        for (int num : nums) {
            if (sum == 0) 
                res = num;
            if (num == res) 
                sum += 1;
            else if (num != res)
                sum += -1;
        }
        return res;
    }
};

// 采用摩尔投票，时间复杂度为O(n)，空间复杂度为O(1)