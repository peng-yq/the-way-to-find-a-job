// https://leetcode.cn/problems/shu-zi-xu-lie-zhong-mou-yi-wei-de-shu-zi-lcof

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findKthNumber(int k) {
        long sum = 9, bits = 1, begin = 1;
        while (sum < k) {
            bits++;
            begin *= 10;
            sum += bits * begin * 9;
        }
        long index = k - (sum - bits * begin * 9);
        long num = (index-1) / bits + begin, y = (index-1) % bits;
        string x = to_string(num);
        return x[y] - '0';
    }
};

// 1位数共9个 (1-9)，2位数共90个 (10-99)，3位数共900个 (100-999)
// 9*1, 90*2, 900*3
// 时间复杂度、空间复杂度O(logk)