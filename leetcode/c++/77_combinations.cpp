// https://leetcode.cn/problems/combinations

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;
        vector<int> tmp;
        function<void(int)> dfs = [&](int start) {
            if (tmp.size() == k) {
                res.push_back(tmp);
                return;
            }
            for (int i = start; i <= n; ++i) {
                tmp.push_back(i);
                dfs(i + 1);
                tmp.pop_back();
            }
        };
        dfs(1);
        return res;
    }
};

// 时间复杂度为O(nk),空间复杂度为O()