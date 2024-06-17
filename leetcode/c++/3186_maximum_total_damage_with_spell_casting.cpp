// https://leetcode.cn/problems/maximum-total-damage-with-spell-casting

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maximumTotalDamage(vector<int>& power) {
        unordered_map<int, int> powerMap;
        for (int x : power) {
            ++powerMap[x];
        }
        vector<pair<int, int>> powerArray(powerMap.begin(), powerMap.end());
        sort(powerArray.begin(), powerArray.end());
        int n = powerArray.size();
        vector<long long> dp(n + 1, 0);
        for (int i = 0, j = 0; i < n; ++i) {
            auto& [k, v] = powerArray[i];
            while (powerArray[j].first < k - 2) {
                ++j;
            }
            dp[i + 1] = max(dp[i], dp[j] + (long long)k * v);
        }
        return dp[n];
    }
};

// 值域打家劫舍
// 时间复杂度为O(nlogn)，空间复杂度为O(n)