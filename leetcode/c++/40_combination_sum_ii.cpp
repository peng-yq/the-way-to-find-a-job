// https://leetcode.cn/problems/combination-sum-ii/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
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
                if (i > start && candidates[i] == candidates[i-1]) 
                    continue;
                state.push_back(candidates[i]);
                dfs(candidates, target-candidates[i], i + 1);
                state.pop_back();
            }
        }
    }
};