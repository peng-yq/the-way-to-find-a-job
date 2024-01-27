// https://leetcode.cn/problems/container-with-most-water/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int i = 0, j = height.size() - 1;
        int res = 0;
        while (i < j) {
            res = max(res, (j - i) * min(height[i], height[j]));
            if (height[i] < height[j])
                i++;
            else 
                j--;
        }
        return res;
    }
};

// 时间复杂度为O(n)，空间复杂度为O(1)