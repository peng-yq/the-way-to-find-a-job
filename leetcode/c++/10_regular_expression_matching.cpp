// https://leetcode.cn/problems/regular-expression-matching/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.length() + 1, n = p.length() + 1;
        vector<vector<bool>> dp (m, vector<bool>(n, false));
        dp[0][0] = true;
        for (int i = 2; i < n; i += 2) {
            dp[0][i] = dp[0][i - 2] && p[i-1] == '*';
        }
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (p[j-1] != '*') {
                    if (dp[i-1][j-1] && s[i-1] == p[j-1]) 
                        dp[i][j] = true;
                    else if (dp[i-1][j-1] && p[j-1] == '.')
                        dp[i][j] = true;
                } else {
                    if (dp[i][j-2])
                        dp[i][j] = true;
                    else if (dp[i-1][j] && s[i-1] == p[j-2])
                        dp[i][j] = true;
                    else if (dp[i-1][j] && p[j-2] == '.')
                        dp[i][j] = true;
                }
            }
        }
        return dp[m-1][n-1];
    }
};

// 时间复杂度为O(mn)，空间复杂度为O(mn)