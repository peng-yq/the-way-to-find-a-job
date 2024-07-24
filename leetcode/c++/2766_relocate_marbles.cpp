// https://leetcode.cn/problems/relocate-marbles

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> relocateMarbles(vector<int>& nums, vector<int>& moveFrom, vector<int>& moveTo) {
        unordered_map<int, int> stones;
        for (int num : nums)
            ++stones[num];
        for (int i = 0; i < moveFrom.size(); ++i) {
            if (moveFrom[i] != moveTo[i]) {
                stones[moveTo[i]] += stones[moveFrom[i]];
                stones[moveFrom[i]] = 0;
            }
        }
        vector<int> res;
        for (auto [k, v] : stones) {
            if (v > 0)
                res.push_back(k);
        }
        sort(res.begin(), res.end());
        return res;
    }
};