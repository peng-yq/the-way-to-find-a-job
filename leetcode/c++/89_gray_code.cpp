// https://leetcode.cn/problems/gray-code/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> res;
        res.push_back(0);
        int head = 1;
        for (int i = 0; i <n; i++) {
            for (int j = res.size() - 1; j >=0; j--) 
                res.push_back(head + res[j]);
            head <<= 1;
        }
        return res;
    }
};

// n阶的格雷编码等于n-1阶的格雷编码加上n-1阶的格雷编码的逆序再在每个元素前面加1
// 时间复杂度为O(n^2)，空间复杂度为O(1)