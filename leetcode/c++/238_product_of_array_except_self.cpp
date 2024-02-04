// https://leetcode.cn/problems/product-of-array-except-self/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> answer(nums.size(), 1);
        int temp = 1;
        for (int i = 1; i < nums.size(); i++) {
            answer[i] = answer[i-1] * nums[i-1];
        }
        for (int i = nums.size() - 2; i >= 0; i--) {
            temp *= nums[i+1];
            answer[i] *= temp; 
        }
        return answer;
    }
};

// 时间复杂度为O(n)，空间复杂度为O(1)