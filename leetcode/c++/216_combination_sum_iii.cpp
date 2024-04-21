// https://leetcode.cn/problems/combination-sum-iii

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void dfs(vector<vector<int>>& res, vector<int>& tmp, int k, int n, int start) {
        if (tmp.size() == k && n == 0) {
            res.push_back(tmp);
            return;
        }
        for (int i = start; i <= 9; ++i) {
            if (i <= n) {
                tmp.push_back(i);
                dfs(res, tmp, k, n-i, i+1);
                tmp.pop_back();
            } else {
                break;
            }
        }
    }
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> res;
        vector<int> tmp;
        dfs(res, tmp, k, n, 1);
        return res;
    }
};

// 进步了，刷题真的是不断建立自信又怀疑自己
// 时间复杂度为O(9^k)，也就是从9个中选k个，空间复杂度为O(k)，递归栈