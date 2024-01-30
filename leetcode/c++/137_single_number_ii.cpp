// https://leetcode.cn/problems/single-number-ii/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int one = 0, two = 0;
        for (int num : nums) {
            one = one ^ num & ~ two;
            two = two ^ num & ~ one;
        }
        return one;
    }
};

// 时间复杂度为O(n)，空间复杂度为O(1)