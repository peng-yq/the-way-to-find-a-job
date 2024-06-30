// https://leetcode.cn/problems/maximum-height-of-a-triangle

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxHeightOfTriangle(int red, int blue) {
        auto tmp = [](int red, int blue)->int {
            vector<int> left = {red, blue};
            int res = 0;
            while (left[res % 2] >= res + 1) {
                left[res % 2] -= (res + 1);
                ++res;
            }
            return res;
        };
        return max(tmp(red, blue), tmp(blue, red));
    }
};

// 优雅，O(max(sqrt(red), sqrt(blue))), O(1)