#include <bits/stdc++.h>
using namespace std;

// template: state choices condition(use to prune) res

void backtrack(vector<int> &state, const vector<int> &choices, vector<bool> &selected, vector<vector<int>> &res) {
    if (state.size() == choices.size()) {
        res.push_back(state);
        return;
    }

    for(int i = 0; i < choices.size(); i++) {
        if(!selected[i]) {
            state.push_back(choices[i]);
            selected[i] = true;
            backtrack(state, choices, selected, res);
            selected[i] = false;
            state.pop_back();
        }
    }
}

vector<vector<int>> permutationsI(vector<int> nums) {
    vector<int> state;
    vector<bool> selected (nums.size(), false);
    vector<vector<int>> res;
    backtrack(state, nums, selected, res);
    return res;
}

void backtrack(vector<int> &state, const vector<int> &choices, vector<bool> &selected, vector<vector<int>> &res) {
    if(state.size() == choices.size()) {
        res.push_back(state);
        return;
    }

    unordered_set<int> duplicated;

    for(int i = 0; i < choices.size(); i++) {
        if(!selected[i] && duplicated.find(choices[i]) == duplicated.end()) {
            duplicated.emplace(choices[i]);
            selected[i] = true;
            state.push_back(choices[i]);
            backtrack(state, choices, selected, res);
            selected[i] = false;
            state.pop_back();
        }
    }
}

vector<vector<int>> permutationsII(vector<int> nums) {
    vector<int> state;
    vector<bool> selected(nums.size(), false);
    vector<vector<int>> res;
    backtrack(state, nums, selected, res);
    return res;
}