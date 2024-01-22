// https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int min_cost = prices[0];
        int max_profit = 0;
        for (int price : prices) {
            min_cost = min(min_cost, price);
            max_profit = max(max_profit, price - min_cost);
        }
        return max_profit;
    }
};

// 时间复杂度为O(n)，空间复杂度为O(1)