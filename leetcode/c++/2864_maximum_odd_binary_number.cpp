// https://leetcode.cn/problems/maximum-odd-binary-number

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string maximumOddBinaryNumber(string s) {
        int n = s.length(), count = 0;
        for (auto ch : s) {
            if (ch == '1')
                count++;
        }
        s[n-1] = '1';
        for (int i = 0; i < n-1; i++) {
            s[i] = --count > 0? '1' : '0';
        }
        return s;
    }
};

// O(n), O(1)