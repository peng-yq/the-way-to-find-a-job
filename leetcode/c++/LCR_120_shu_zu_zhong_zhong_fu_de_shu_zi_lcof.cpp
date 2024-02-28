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
