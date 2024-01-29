// https://leetcode.cn/problems/number-of-1-bits/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int hammingWeight(uint32_t n) {
        int res = 0;
        while (n != 0) {
            res += n & 1;
            n >>= 1;
        }
        return res;
    }
};

// 时间和空间复杂度均为O(1)