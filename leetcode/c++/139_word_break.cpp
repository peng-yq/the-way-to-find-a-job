// https://leetcode.cn/problems/word-break

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.length();
        vector<bool> dp(n+1, false);
        dp[0] = true;
        for (int i = 1; i <= n; ++i) {
            for (auto word : wordDict) {
                int j = word.size();
                if (i - j >= 0 && dp[i - j] && s.substr(i - j, j) == word)
                    dp[i] = true;
            }
        }
        return dp[n];
    }
};

// 完全背包问题，O(mn)，O(n)
// dp[i]表示0-i-1的子串是否能匹配，状态转移方程是 if (i - j >= 0 && dp[i - j] && s.substr(i - j, j) == word) dp[i] = true;