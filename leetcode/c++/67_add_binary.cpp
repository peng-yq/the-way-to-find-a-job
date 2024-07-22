// https://leetcode.cn/problems/add-binary

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string addBinary(string a, string b) {
        string res;
        int i = a.size() - 1, j = b.size() - 1, pre = 0;
        while (i >= 0 || j >= 0 || pre) {
            int sum = pre;
            if (i >= 0) {
                sum += a[i] - '0';
                --i;
            }
            if (j >= 0) {
                sum += b[j] - '0';
                --j;
            }
            res = to_string(sum % 2) + res;
            pre = sum / 2;
        }
        return res;
    }
};

// 双指针