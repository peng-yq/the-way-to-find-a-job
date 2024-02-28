// https://leetcode.cn/problems/shun-shi-zhen-da-yin-ju-zhen-lcof/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> spiralArray(vector<vector<int>>& array) {
        if (array.empty())
            return {};
        int top = 0, bottom = array.size() - 1, left = 0, right = array[0].size() - 1;
        vector<int> res;
        while (true) {
            for (int i = left; i <= right; i++) res.push_back(array[top][i]);
            if (++top > bottom) break;
            for (int i = top; i <= bottom; i++) res.push_back(array[i][right]);
            if (--right < left) break;
            for (int i = right; i >= left; i--) res.push_back(array[bottom][i]);
            if (--bottom < top) break;
            for (int i = bottom; i >= top; i--) res.push_back(array[i][left]);
            if (++left > right) break;
        }
        return res;
    }
};

// 模拟，O(m * n)，O(1)