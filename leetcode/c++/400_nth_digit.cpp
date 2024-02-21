// https://leetcode.cn/problems/nth-digit/description

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findNthDigit(int n) {
        int digit = 1;
        long start = 1, count = 9;
        while (n > count) {
            n -= count;
            start *= 10;
            digit += 1;
            count = digit * start * 9;
        }
        long num = start + (n-1) / digit;
        return to_string(num)[(n-1) % digit] - '0';
    }
};

// 找规律的题真难x，时间复杂度和空间复杂度为O(logn)