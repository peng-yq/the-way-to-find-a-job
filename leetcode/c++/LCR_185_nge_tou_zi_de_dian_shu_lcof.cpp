// https://leetcode.cn/problems/nge-tou-zi-de-dian-shu-lcof

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<double> statisticsProbability(int num) {
        vector<double>dp(6, 1.0/6.0);
        for (int i = 2; i <= num; i++) {
            vector<double>tmp(5*i+1, 0);
            for (int j = 0; j < dp.size(); j++) {
                for (int k = 0; k < 6; k++) {
                    tmp[j+k] += dp[j] / 6.0;
                }
            }
            dp = tmp;
        }
        return dp;
    }
};

// O(n^2), O(n)
// f(n, x)表示n个骰子点数和为x的概率，可以由f(n-1, k+i)得到，k+i=x，i的范围为[1-6]
// 逆推不好写代码可能出现溢出，因此正向推导