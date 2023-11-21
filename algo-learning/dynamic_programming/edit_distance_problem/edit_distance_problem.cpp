#include <bits/stdc++.h>
using namespace std;

int editDistanceDP(string s, string t) {
    int n = s.size(), m = t.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    for (int j = 1; j < m+1; j++)
        dp[0][j] = j;
    for (int i = 1; i < n+1; i++)
        dp[i][0] = i;
    for (int i = 1; i < n+1; i++) {
        for (int j = 1; j < m+1; j++) {
            if (s[i-1] == t[j-1])
                dp[i][j] = dp[i-1][j-1];
            else
                dp[i][j] = min(dp[i-1][j-1], dp[i][j-1], dp[i-1][j]) + 1;
        }
    }
    return dp[n][m];
}

int editDistanceDPComp(string s, string t) {
    int n = s.size(), m = t.size();
    vector<int> dp (m+1, 0);
    for (int i = 1; i < m+1; i++) {
        dp[i] = i;
    }
    for (int i = 1; i < n+1; i++) {
        int left = dp[0];
        dp[0] = i;
        for (int j = 1; j < m+1; j++) {
            int temp = dp[j];
            if (s[i-1] == t[j-1]) {
                dp[j] = left;
            } else {
                dp[j] = min (dp[j-1], left, dp[j]) + 1;
            }
            left = temp;
        }
    }
    return dp[m];
}