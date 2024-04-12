// https://leetcode.cn/problems/largest-rectangle-in-histogram

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        vector<int> left(n, -1); // 注意这里是-1，你就想只有一个元素的时候，左边小于它的就是-1
        deque<int> stk;
        for (int i = 0; i < n; i++) {
            while (!stk.empty() && heights[i] <= heights[stk.back()])
                stk.pop_back();
            if (!stk.empty()) 
                left[i] = stk.back();
            stk.push_back(i);
        }
        vector<int> right(n, n); // 同样的道理，只有一个元素，右边小于它的就是n
        stk = deque<int>();
        for (int i = n - 1; i >= 0; i--) {
            while (!stk.empty() && heights[i] <= heights[stk.back()]) {
                stk.pop_back();
            }
            if (!stk.empty()) 
                right[i] = stk.back();
            stk.push_back(i);
        }
        int res = 0;
        for (int i = 0; i < n; i++) {
            res = max(res, heights[i] * (right[i] - left[i] -1));
        }
        return res;
    }
};

// 单调栈，时间复杂度为O(n)，空间复杂度为O(n)
// 求最大矩形也就是需要找到左右两边小于当前高度的最近元素的下标，最大矩形为h * (right - left -1)
// 一轮循环也可以解决，但我理解不了x