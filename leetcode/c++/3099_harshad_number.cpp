// https://leetcode.cn/problems/harshad-number

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int sumOfTheDigitsOfHarshadNumber(int x) {
        int res = 0, num = x;
        while (x) {
            res += x % 10;
            x /= 10;
        }
        return num % res == 0? res : -1;
    }
};

// O(log10(x)), O(1)