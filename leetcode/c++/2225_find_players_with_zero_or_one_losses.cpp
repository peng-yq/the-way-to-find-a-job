// https://leetcode.cn/problems/find-players-with-zero-or-one-losses

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> findWinners(vector<vector<int>>& matches) {
        unordered_map<int, int> loss_count;
        for (auto& m : matches) {
            if (!loss_count.contains(m[0])) {
                loss_count[m[0]] = 0;
            }
            loss_count[m[1]]++;
        }

        vector<vector<int>> res(2);
        for (auto& [player, cnt] : loss_count) {
            if (cnt < 2) {
                res[cnt].push_back(player);
            }
        }
        sort(res[0].begin(), res[0].end());
        sort(res[1].begin(), res[1].end());
        return res;
    }
};

// 考察map吧，简单题，O(nlogn)，O(n)