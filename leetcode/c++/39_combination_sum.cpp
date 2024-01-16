// https://leetcode.cn/problems/combination-sum/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        dfs(candidates, target, 0);
        return res;
    }
private:
    vector<vector<int>> res;
    vector<int> state;
    void dfs(vector<int>& candidates, int target, int start) {
        if (target == 0) {
            res.push_back(state);
            return;
        }
        for (int i = start; i < candidates.size(); i++) {
            if (target >= candidates[i]) {
                state.push_back(candidates[i]);
                dfs(candidates, target - candidates[i], i);
                state.pop_back();
            }
        }
    }
};

// 时间复杂度和空间复杂度挺复杂的，估计也不会问