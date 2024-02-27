// https://leetcode.cn/problems/hua-dong-chuang-kou-de-zui-da-zhi-lcof/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> maxAltitude(vector<int>& heights, int limit) {
        vector<int> res;
        deque<int> que;
        for (int i = 0, j = 0; j < heights.size(); j++) {
            while (!que.empty() && que.back() < heights[j])
                que.pop_back();
            que.push_back(heights[j]);
            if (j - i + 1 > limit) {
                if (que.front() == heights[i])
                    que.pop_front();
                i++;
            }
            if (j -i + 1 == limit)
                res.push_back(que.front());
        }
        return res;
    }
};

// 时间复杂度为O(n)，空间复杂度为O(limit)
// 利用单调双端队列使得查找窗口内最大值时间复杂度为O(1)