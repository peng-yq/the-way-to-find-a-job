// https://leetcode.cn/problems/find-missing-observations

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> missingRolls(vector<int>& rolls, int mean, int n) {
        int m = rolls.size();
        int sum = (m + n) * mean - accumulate(rolls.begin(), rolls.end(), 0);
        if (sum > 6 * n || sum < n) return {};
        vector<int> res(n, 0);
        for (int i = 0; i < sum; ++i) 
            ++res[i % n];
        return res;
    }
};

// 从n个1-6中选出sum，凑就完事了，相当于填桶
// 时间复杂度为O(n)，空间复杂度为O(1)