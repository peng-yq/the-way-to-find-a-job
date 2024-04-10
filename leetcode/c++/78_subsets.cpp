// https://leetcode.cn/problems/subsets

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void dfs(vector<vector<int>>& res, vector<int>& nums, vector<int>& tmp, int start, int num) {
        if (tmp.size() == num) {
            res.push_back(tmp);
            return;
        }
        for (int i = start; i < nums.size(); i++) {
            tmp.push_back(nums[i]);
            dfs(res, nums, tmp, i+1, num);
            tmp.pop_back();
        }
    }
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> tmp;
        for (int i = 0; i <= nums.size(); i++) {
            dfs(res, nums, tmp, 0, i);
        }
        return res;
    }
};

// 如果是求全排列就用visited，如果要求不重复就使用start
// 时间复杂度为O(n * 2 ^n)， 共有2^n个子集，构造每个子集需要O(n)的时间，空间复杂度为O(n)，递归的最大深度为O(n)