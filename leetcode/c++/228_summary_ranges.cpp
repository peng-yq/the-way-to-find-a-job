// https://leetcode.cn/problems/summary-ranges

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        if (nums.empty())
            return {};
        int n = nums.size(), pre = nums[0];
        vector<string> res;
        for (int i = 1; i < n; ++i) {
            if (nums[i] != nums[i - 1] + 1) {
                if (nums[i - 1] == pre)
                    res.push_back(to_string(pre));
                else {
                    res.push_back(to_string(pre) + "->" + to_string(nums[i - 1]));
                }
                pre = nums[i];
            }
        }
        if (nums[n - 1] == pre) {
            res.push_back(to_string(pre));  
        } else {
            res.push_back(to_string(pre) + "->" + to_string(nums[n - 1]));  
        }
        return res;
    }
};

// 没太多好讲的，O(n)，O(1)