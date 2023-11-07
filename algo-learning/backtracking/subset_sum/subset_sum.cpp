#include <bits/stdc++.h>
using namespace std;

void backtrack(vector<int> &state, vector<int> &choices, int target, int start, vector<vector<int>> &res) {
    if (target == 0) {
        res.push_back(state);
        return;
    }
    for (int i = start; i < choices.size(); i++) {
        
        state.push_back(choices[i]);
        backtrack(state, choices, target - choices[i], i, res);
        state.pop_back();
    }
}

void backtrack(vector<int> &state, vector<int> &choices, int target, int start, vector<vector<int>> &res) {
    if (target == 0) {
        res.push_back(state);
        return;
    }
    for (int i = start; i < choices.size(); i++) {
        if (target - choices[i] < 0)
            break;
        // i > start makes sure i-1 >= 0
        if(i > start && choices[i] == choices[i-1])
            continue;
        state.push_back(choices[i]);
        backtrack(state, choices, target - choices[i], i+1, res);
        state.pop_back();
    }
}

vector<vector<int>> subsetSumI(vector<int> &nums, int target) {
    vector<int> state;
    sort(nums.begin(), nums.end());
    vector<vector<int>> res;
    backtrack(state, nums, target, 0, res);
    return res;
}