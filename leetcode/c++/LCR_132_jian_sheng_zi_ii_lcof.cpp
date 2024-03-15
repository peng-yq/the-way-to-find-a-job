// https://leetcode.cn/problems/jian-sheng-zi-ii-lcof

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    const int mod = 1000000007;
    int myPow(int x, int y) {
        long res = 1;
        long z = x;
        while (y) {
            if ((y & 1) == 1) 
                res = res * z % mod;
            z = z * z % mod;
            y >>= 1;
        }
        return (int)res;
    }
    int cuttingBamboo(int bamboo_len) {
        if (bamboo_len <= 3)
            return bamboo_len - 1;
        int a = bamboo_len / 3, b = bamboo_len % 3;
        long res;
        if (b == 0) 
            res = myPow(3, a);
        else if (b == 2)
            res = myPow(3, a) * 2L % mod; // 避免溢出
        else
            res = myPow(3, a-1) * 4L % mod;
        return (int)res;
    }
};

// 溢出溢出溢出，快速幂，时间复杂度为O(logn)，空间复杂度为O(1)
