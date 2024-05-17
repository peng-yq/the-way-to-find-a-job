// https://leetcode.cn/problems/most-profit-assigning-work

#include <bits/stdc++.h>
using namespace std;

struct work {
    int difficulty_;
    int profit_;
};

class Solution {
public:
    int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
        int n = difficulty.size(), res = 0, m = worker.size();
        vector<work> works(n);
        for (int i =0; i < n; ++i) {
            works[i] = {difficulty[i], profit[i]};
        }
        sort(works.begin(), works.end(), [](const work& a, const work& b) {return a.difficulty_ < b.difficulty_;});
        sort(worker.begin(), worker.end());
        int j = 0, maxProfit = 0;
        for (int i = 0; i < m; ++i) {
            while (j < n && works[j].difficulty_ <= worker[i]) {
                maxProfit = max(maxProfit, works[j].profit_);
                ++j;
            }
            res += maxProfit;
        }
        return res;
    }
};

// 比较简单吧，时间复杂度就是两个排序的时间，空间复杂度O(n)