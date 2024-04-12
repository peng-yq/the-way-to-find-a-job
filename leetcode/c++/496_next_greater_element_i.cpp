// https://leetcode.cn/problems/next-greater-element-i/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size(), n2 = nums2.size();
        vector<int> res(n1, -1);
        unordered_map<int, int> index;
        stack<int> stk;
        for (int i = n2-1; i >= 0; --i) {
            index[nums2[i]] = i;
            while (!stk.empty() && nums2[i] >= stk.top())
                stk.pop();
            if (!stk.empty())
                index[nums2[i]] = stk.top();
            else 
                index[nums2[i]] = -1;
            stk.push(nums2[i]);
        }
        for (int i = 0; i < n1; ++i) {
            res[i] = index[nums1[i]];
        }
        return res;
    }
};

// O(n), O(n)