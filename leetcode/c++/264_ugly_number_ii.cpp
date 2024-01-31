// https://leetcode.cn/problems/ugly-number-ii/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int nthUglyNumber(int n) {
        int dp[n];
        dp[0] = 1;
        int a = 0, b = 0, c = 0;
        for (int i = 1; i < n; i++) {
            int res_a = dp[a] * 2, res_b = dp[b] * 3, res_c = dp[c] * 5;
            dp[i] = min(min(res_a, res_b), res_c);
            if (dp[i] == res_a) a++;
            if (dp[i] == res_b) b++;
            if (dp[i] == res_c) c++;
        }
        return dp[n-1];
    }
};

// 时间复杂度为O(n)，空间复杂度为O(n)