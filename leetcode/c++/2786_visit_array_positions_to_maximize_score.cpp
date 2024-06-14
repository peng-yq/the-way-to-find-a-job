// https://leetcode.cn/problems/visit-array-positions-to-maximize-score

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maxScore(vector<int>& nums, int x) {
        long long even = 0, odd = 0;
        if (nums[0] & 1)
            even = INT_MIN;
        else 
            odd = INT_MIN;
        for (auto num : nums) {
            if (num & 1)
                odd = max(odd, max(odd + num, even + num - x));
            else
                even = max(even, max(even + num, odd + num - x));
        }
        return max(odd, even);
    }
};

// 动态规划，只记录当前最大的奇数元素的值和偶数元素的值
// O(n),O(1)