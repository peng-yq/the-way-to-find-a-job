// https://leetcode.cn/problems/gou-jian-cheng-ji-shu-zu-lcof

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> statisticalResult(vector<int>& arrayA) {
        if (arrayA.size() == 0)
            return {};
        vector<int> left(arrayA.size(), 1);
        int count = 1;
        for (int i = 1; i < arrayA.size(); i++) {
            left[i] = left[i-1] * arrayA[i-1];
        }
        for (int i = arrayA.size()-1; i >= 0; i--) {
            left[i] *= count;
            count *= arrayA[i]; 
        }
        return left;
    }
};

// 直接除会有问题，比如0，所以直接左边的乘积乘以右边的乘积
// O(n), O(1)