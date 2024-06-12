// https://leetcode.cn/problems/account-balance-after-rounded-purchase

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int accountBalanceAfterPurchase(int purchaseAmount) {
        const int sum = 100;
        if (purchaseAmount % 10 < 5) {
            return sum - (purchaseAmount / 10) * 10;
        } else {
            return sum - (purchaseAmount / 10 + 1) * 10;
        }
    }
};