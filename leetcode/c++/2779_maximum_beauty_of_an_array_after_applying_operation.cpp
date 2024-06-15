// https://leetcode.cn/problems/maximum-beauty-of-an-array-after-applying-operation

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumBeauty(vector<int>& nums, int k) {
        int res = 0;
        sort(nums.begin(), nums.end());
        for (int i = 0, j = 0; j < nums.size(); ++j) {
            while (nums[j] - nums[i] > 2 * k) {
                ++i;
            }
            res = max(res, j - i + 1);
        }
        return res;
    }
};

// 阅读理解题目，翻译过来是每个元素x，可以变换成[x-k, x+k]范围内的任一元素，并且只能变换一次
// 美丽值是相等元素组成的最长子序列的长度，我们不需要去考虑美丽值是什么，也为最后可能有多个符合条件的美丽值
// 对于元素x和元素y，他们分别可变为[x-k, x+k]和[y-k, y+k]范围内的任意值，当x和y变为相等值时，其下标y-i就是美丽值
// 为了满足相等，就说明两个元素的取值范围需要有交集，也就是x + k >= y - k -> y - x >= 2 * k
// 由于是子序列，因此我们可以将元素进行排序，从而更方便并使用滑动窗口进行求解
// 时间复杂度为O(nlogn)，空间复杂度为O(1)