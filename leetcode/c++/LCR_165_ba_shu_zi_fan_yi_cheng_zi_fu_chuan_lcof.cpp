// https://leetcode.cn/problems/ba-shu-zi-fan-yi-cheng-zi-fu-chuan-lcof

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int crackNumber(int ciphertext) {
        string str = to_string(ciphertext);
        int dp[str.length()+1];
        dp[0] = 1, dp[1] = 1;
        for (int i = 2; i <= str.length(); i++) {
            string tmp = str.substr(i-2, 2);
            if (tmp >= "10" && tmp <= "25")
                dp[i] = dp[i-1] + dp[i-2];
            else 
                dp[i] = dp[i-1];
        }
        return dp[str.length()];
    }
};

// 时间复杂度为O(n)，空间复杂度为O(n)，可以优化为O(1)，改编版的跳楼梯只不过有条件，很巧妙
