// https://leetcode.cn/problems/longest-subarray-of-1s-after-deleting-one-element/submissions/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int res = 0;
        for (int l = 0, r = 0, tmp = 0; r < nums.size(); r++) {
            tmp += nums[r];
            if (tmp < r - l)
                tmp -= nums[l++];
            res = max(res, r - l);
        }
        return res;
    }
};