// https://leetcode.cn/problems/next-greater-element-ii

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n, -1);
        stack<int> stk;
        for (int i = 2*n-1; i >= 0; --i) {
            while (!stk.empty() && nums[i%n] >= stk.top()) 
                stk.pop();
            if (!stk.empty())
                res[i%n] = stk.top();
            stk.push(nums[i%n]);
        }
        return res;
    }
};

// O(n), O(n)
// 主要是循环数组的处理