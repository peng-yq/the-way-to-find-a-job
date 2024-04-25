// https://leetcode.cn/problems/shu-zu-zhong-zhong-fu-de-shu-zi-lcof/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findRepeatDocument(vector<int>& documents) {
        unordered_map<int, int> map;
        for (int num : documents) {
            if (++map[num] != 1)
                return num;
        }
        return 0;
    }
};

// 哈希表，O(n), O(n)
// 原地哈希，O(n)，O(1)，比较难理解，因为数组元素大小都是0~n的，
// 因此我们直接用原数组做哈希表，索引为i的位置保存元素i，如果在遍历的过程中发现documents[i] == documents[documents[i]]
// 说明这个元素重复
// 怎么遍历呢？如果documents[i] == i，那检查下一个元素，如果不相等，则一致交换直到满足条件。