// https://leetcode.cn/problems/pairs-of-songs-with-total-durations-divisible-by-60

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numPairsDivisibleBy60(vector<int>& time) {
        vector<int> timeMap(60, 0);
        vector<int> timeChoosed(60, 0);
        int res = 0;
        for (int t : time)
            ++timeMap[t % 60];
        for (int i = 0; i < 60; ++i) {
            if (i == 0 || i == 30)
                res += long(timeMap[i]) * long(timeMap[i] - 1) / 2;
            else if (!timeChoosed[i] && !timeChoosed[60 - i]) {
                res += long(timeMap[i]) * long(timeMap[60 - i]);
                timeChoosed[i] = timeChoosed[60 -i] = 1;
            }
        }
        return res;
    }
};

// 思路和今天的周赛一模一样，哈希表
// O(n), O(1)