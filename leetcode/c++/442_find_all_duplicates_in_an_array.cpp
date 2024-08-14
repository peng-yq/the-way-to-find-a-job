// https://leetcode.cn/problems/find-all-duplicates-in-an-array/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> res;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            int num = nums[i];
            int index = abs(num) - 1;
            if (nums[index] > 0) {
                nums[index] = -nums[index];
            } else {
                res.push_back(index + 1);
            }
        }
        return res;
    }
};


// 原地哈希，用负数来标记为之前访问过