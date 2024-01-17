// https://leetcode.cn/problems/ti-huan-kong-ge-lcof/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string pathEncryption(string path) {
        for (char& ch : path) {
            if (ch == '.') 
                ch = ' ';
        }
        return path;
    }
};

// 时间复杂度为O(n)，空间复杂度为O(1)