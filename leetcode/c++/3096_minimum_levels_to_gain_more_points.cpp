// https://leetcode.cn/problems/minimum-levels-to-gain-more-points

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumLevels(vector<int>& possible) {
        int sum = 0, tmp = 0;
        for (auto num : possible)
            sum += num == 1? 1 : -1;
        for (int i = 0; i < possible.size() - 1; ++i) {
            tmp += possible[i] == 1? 1 : -1;
            if (tmp > sum - tmp)
                return i + 1;
        }
        return -1;
    }
};

// O(n), O(1)