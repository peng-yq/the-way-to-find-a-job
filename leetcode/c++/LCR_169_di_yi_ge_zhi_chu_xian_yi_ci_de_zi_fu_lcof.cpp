// https://leetcode.cn/problems/di-yi-ge-zhi-chu-xian-yi-ci-de-zi-fu-lcof/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    char dismantlingAction(string arr) {
        unordered_map<char, int>map;
        for (char ch : arr)
            map[ch]++;
        for (char ch : arr) {
            if (map[ch] == 1)
                return ch;
        }
        return ' ';
    }
};

// 还可以用有序哈希表来减小第二次遍历的时间复杂度，即重复字符只检测一次
// 时间复杂度和空间复杂度均为O(n)