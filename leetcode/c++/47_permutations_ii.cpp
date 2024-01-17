// https://leetcode.cn/problems/permutations-ii/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<bool>selected(nums.size(), false);
        dfs(nums, selected);
        return res;
    }
private:
    vector<vector<int>> res;
    vector<int> state;
    void dfs(vector<int>& nums, vector<bool>& selected) {
        if (state.size() == nums.size()) {
            res.push_back(state);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (i > 0 && nums[i]==nums[i-1] && !selected[i-1])
                    continue;
            if (!selected[i]) {             
                state.push_back(nums[i]);
                selected[i] = true;
                dfs(nums, selected);
                state.pop_back();
                selected[i] = false;
            }
        }
    }
};

// 时间复杂度为O(n*n!)，空间复杂度也是