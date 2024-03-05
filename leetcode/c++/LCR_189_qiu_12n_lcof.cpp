// https://leetcode.cn/problems/qiu-12n-lcof/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int mechanicalAccumulator(int target) {
        target > 1 && (target += mechanicalAccumulator(target-1));
        return target;
    }
};

// 蠢得不行的一道题