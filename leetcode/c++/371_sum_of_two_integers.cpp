// https://leetcode.cn/problems/sum-of-two-integers

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int getSum(int a, int b) {
        while (b != 0) {
            int c = (unsigned int) (a & b) << 1;
            a ^= b;
            b = c;
        }
        return a;
    }
};