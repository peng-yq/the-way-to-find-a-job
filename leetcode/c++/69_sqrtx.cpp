// https://leetcode.cn/problems/sqrtx

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int mySqrt(int x) {
        if (x == 0) return 0;        
        int i = 1, j = x / 2 + 1;
        while (i <= j) {
            int m = i + (j - i) / 2;
            if (m == x / m) {
                return m;
            } else if (m < x / m) {
                i = m + 1;
            } else {
                j = m - 1;
            }
        }
        
        return j;
    }
};

// 任何一个正整数x的平方根都不会大于x/2+1
// 题目实际是要求平方根不大于x的最大整数，所以最后返回的是j
// O(logn), O(1)