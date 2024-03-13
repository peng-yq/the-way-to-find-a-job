// https://leetcode.cn/problems/er-jin-zhi-zhong-1de-ge-shu-lcof

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int hammingWeight(uint32_t n) {
        int res = 0;
        while (n) {
            if (n & 1 == 1)
                res++;
            n >>= 1;
        }
        return res;
    }
};

// O(n), O(1)