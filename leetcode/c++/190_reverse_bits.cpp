// https://leetcode.cn/problems/reverse-bits

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t res = 0;
        int i = 32;
        while (i--) {
            res <<= 1;
            res += n & 1;
            n >>= 1;
        }
        return res;
    }
};

// 二进制左移右移