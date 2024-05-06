// https://leetcode.cn/problems/max-chunks-to-make-sorted-ii

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        int n = arr.size();
        stack<int> stk;
        for (int i = 0; i < n; ++i) {
            if (!stk.empty() && stk.top() > arr[i]) {
                int tmp = 0;
                while (!stk.empty() && stk.top() > arr[i]) {
                    tmp = max(tmp, stk.top());
                    stk.pop();
                }
                stk.push(tmp);
            } else {
                stk.push(arr[i]);
            }
        }
        return stk.size();
    }
};

// 要完成这道题，首先需要明白怎么去划分排序块：题目要求将数组划分为若干个块（1个或多个元素），并且需要满足将划分后的块排序后从左到右拼接起来与原数组排序后一致
// 此外，为了使得划分的块数最大，尽可能的将一个元素划分为1个块；如何判断一个元素num是否能单独划分为一个排序块呢？
// 我们需要保证前面所有块的最大值要小于等于当前元素num，否则需要将当前num加入到前面的块中
// 此外，我们不能将元素进行移动，什么意思呢？比如前面的块是3|5|6，当前元素是4，我们只能将其划分为3|5 6 4|，注意这个过程中，我们一直往前搜索已划分的块中的最大值
// 直到出现某个块的最大值小于等于当前元素num，或找不到目标块；此时我们再更新排序块
// 上述过程可以使用单调栈模拟，用单调栈保存每个块的最大值，最后返回单调栈的大小即为划分的最大块数
// 时间复杂度为O(n)，空间复杂度为O(n)