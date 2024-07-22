// https://leetcode.cn/problems/factorial-trailing-zeroes

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int trailingZeroes(int n) {
        int res = 0;
        while (n) {
            res += n / 5;
            n /= 5;
        }
        return res;
    }
};

// 判断0的个数也就是判断式子中2和5的个数中的最小值，由于2的个数肯定是比5多的，因此直接判断5的个数即可
// 基于以下规律：1-n中，每个5个数出现1个5，每个25个数多出现1个5，每个125个数再多出现1个5
// 因此不断的去除以5和更新n即可
// O(log5n) O(1)