// https://leetcode.cn/problems/chou-shu-lcof

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int nthUglyNumber(int n) {
        int dp[n], a = 0, b = 0, c = 0;
        dp[0] = 1;
        for (int i = 1; i < n; i++) {
            int resa = dp[a] * 2, resb = dp[b] * 3, resc = dp[c] * 5;
            int d = min(min(resa, resb), resc);
            dp[i] = d;
            if (resa == d) a++;
            if (resb == d) b++;
            if (resc == d) c++;
        }
        return dp[n-1];
    }
};

// 时间复杂度为O(n)，空间复杂度为O(n)
// 解题关键在于每个丑数（除了1）都可以由比它小的丑数乘以2或3或5得到
// 为了确保不漏掉每个丑数，我们需要让每个丑数都乘以2或3或5，也就是三个有序队列
// 但是这样会导致重复，我们需要合并这三个有序队列，也就是维护三个指针，每次选取最小的那个，再移动相应的指针