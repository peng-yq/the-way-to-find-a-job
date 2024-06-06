// https://leetcode.cn/problems/separate-black-and-white-balls

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long minimumSteps(string s) {
        long long res = 0;
        int i = 0, j = s.size() - 1;
        while (i < j) {
            while (s[i] == '0' && i < j)
                ++i;
            while (s[j] == '1' && i < j)
                --j;
            res += j - i;
            swap(s[i], s[j]);
        }
        return res;
    }
};

// 双指针，没太多好说的，O(n)，O(1)