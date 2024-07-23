// https://leetcode.cn/problems/bitwise-and-of-numbers-range

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {
        int res = 0;
        while (left != right) {
            left >>= 1;
            right >>= 1;
            ++res;
        }
        return left << res;
    }
};

// 只要有0，不管有多少个1，相&的结果都是0
// 由于是求[left, right]区间的各数相&的结果，因此转换为求最长公共前缀，后面的部分肯定会出现0
// 不断的右移left和right即可
// O(n), O(1)