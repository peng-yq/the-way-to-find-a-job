// https://leetcode.cn/problems/max-chunks-to-make-sorted

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        int res = 0, tmp = 0;
        for (int i = 0; i < arr.size(); ++i) {
            tmp = max(tmp, arr[i]);
            if (tmp == i)
                ++res;
        }
        return res;
    }
};

// 这道题有个关键条件，元素范围在[0-n)，并且元素各不相同
// 使用单调栈肯定是可以解决的，但空间复杂度为O(n)，并且没有充分利用上述条件
// 同样的思路，只有当前面所有块的最大值都小于当前元素num，才能将其划分为一个单独块
// 由于元素各不相同，并且数据范围为[0-n)，因此排序后索引为i的元素应该为i，我们需要保证左边最大值等于元素num的索引才能将其划分为一个排序块
// 这样每个排序块内部排序后拼接起来，才能保证索引为i的位置的元素为i
// 时间复杂度为O(n)，空间复杂度为O(1)