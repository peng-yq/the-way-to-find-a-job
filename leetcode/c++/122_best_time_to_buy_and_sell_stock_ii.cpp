// https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n < 2)
            return 0;
        int res = 0;
        for (int i = 1; i < n; i++) {
            if (prices[i] > prices[i-1])
                res += prices[i] - prices[i-1];
        }
        return res;
    }
};

// 时间复杂度为O(n)，空间复杂度为O(1)