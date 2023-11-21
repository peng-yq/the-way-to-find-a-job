#include <bits/stdc++.h>
using namespace std;

int unboundedKnapsackDP(vector<int> &wgt, vector<int> &val, int cap) {
    int n = wgt.size();
    vector<vector<int>>dp (n+1, vector<int> (cap+1, 0));
    for (int i = 1; i < n + 1; i++) {
        for (int c = 1; c < cap + 1; c++) {
            if (wgt[i-1] > c) {
                dp[i][c] = dp[i-1][c];
            } else {
                dp[i][c] = max(dp[i-1][c], dp[i][c-wgt[i-1]] + val[i-1]);
            }
        }
    }
    return dp[n][cap];
}

int unboundedKnapsackDPComp(vector<int> &wgt, vector<int> &val, int cap) {
    int n = wgt.size();
    vector<int> dp(cap + 1, 0);
    for (int i = 1; i <= n; i++) {
        for (int c = 1; c <= cap; c++) {
            if (wgt[i - 1] <= c) {
                dp[c] = max(dp[c], dp[c - wgt[i - 1]] + val[i - 1]);
            }
        }
    }
    return dp[cap];
}

int coinChangeDP(vector<int> &coins, int amt) {
    int n = coins.size();
    vector<vector<int>>dp(n+1, vector<int> (amt+1,0));
    // dp[0][0] = 0
    for(int i = 1; i < amt+1; i++) {
        dp[0][i] = amt + 1;
    }
    for(int i = 1; i < n+1; i++) {
        for(int a = 1; a < amt+1; a++) {
            if(coins[i-1] > a) {
                dp[i][a] = dp[i-1][a];
            } else {
                dp[i][a] = min(dp[i-1][a], dp[i][a-coins[i-1]]+1);
            }
        }
    }
    return dp[n][amt] == amt + 1? -1:dp[n][amt];
}

int coinChangeDPComp(vector<int> &coins, int amt) {
    int n = coins.size();
    int MAX = amt + 1;
    vector<int> dp(amt + 1, MAX);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int a = 1; a <= amt; a++) {
            if (coins[i - 1] > a) {
                dp[a] = dp[a];
            } else {
                dp[a] = min(dp[a], dp[a - coins[i - 1]] + 1);
            }
        }
    }
    return dp[amt] != MAX ? dp[amt] : -1;
}

int coinChangeIIDP(vector<int> &coins, int amt) {
     int n = coins.size();
    vector<vector<int>>dp(n+1, vector<int> (amt+1,0));
    // dp[0][0] = 0
    for(int i = 0; i < amt+1; i++) {
        dp[i][0] = 1;
    }
    for(int i = 1; i < n+1; i++) {
        for(int a = 1; a < amt+1; a++) {
            if(coins[i-1] > a) {
                dp[i][a] = dp[i-1][a];
            } else {
                dp[i][a] = dp[i-1][a] + dp[i][a-coins[i-1]];
            }
        }
    }
    return dp[n][amt];
}

int coinChangeIIDPComp(vector<int> &coins, int amt) {
    int n = coins.size();
    vector<int> dp(amt + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int a = 1; a <= amt; a++) {
            if (coins[i - 1] > a) {
                dp[a] = dp[a];
            } else {
                dp[a] = dp[a] + dp[a - coins[i - 1]];
            }
        }
    }
    return dp[amt];
}