#include <bits/stdc++.h>
using namespace std;

int knapsackDP(vector<int> &wgt, vector<int> &val, int cap) {
    int n = wgt.size();
    vector<vector<int>>dp (n+1, vector<int>(cap+1, 0));
    for(int i = 1; i < n+1; i++) {
       for(int c = 1; c < n+1; c++) {
            if (wgt[i-1] > c) {
                 dp[i][c] = dp[i-1][c];
            }
            else {
                dp[i][c] = max(dp[i-1][c], dp[i-1][c-wgt[i-1]]+val[i-1]);
            }
            
       }
    }
    return dp[n][cap];
}