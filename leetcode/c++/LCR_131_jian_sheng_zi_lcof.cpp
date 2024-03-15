// https://leetcode.cn/problems/jian-sheng-zi-lcof

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int cuttingBamboo(int bamboo_len) {
        if (bamboo_len <= 3)
            return bamboo_len - 1;
        int a = bamboo_len / 3, b = bamboo_len % 3;
        if (b == 0)
            return pow(3, a);
        if (b == 2)
            return pow(3, a) * 2;
        return pow(3, a-1) * 4;
    }
};

// 数论，每个数字都能分为2和3（奇偶），3越多越大，比如3*3 > 2*2*2
// 当余数为1时，需要把前一个3和这个1变为2和2，2*2 > 1*3
// O(1)，O(1)
// 也可以用动态规划