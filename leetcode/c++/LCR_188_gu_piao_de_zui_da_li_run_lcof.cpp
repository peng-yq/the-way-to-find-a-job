// https://leetcode.cn/problems/gu-piao-de-zui-da-li-run-lcof

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int bestTiming(vector<int>& prices) {
        if (prices.size() < 2)
            return 0;
        int a = 0, b = 0;
        int buy_price = prices[0];
        for (int i = 1; i < prices.size(); i++) {
            if (prices[i] < buy_price)
                buy_price = prices[i];
            b = max(prices[i] - buy_price, a);
            a = b;
        }
        return b;
    }
};

// 时间复杂度为O(n)，空间复杂度为O(1)