// https://leetcode.cn/problems/he-wei-sde-liang-ge-shu-zi-lcof/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& price, int target) {
        int i = 0, j = price.size() - 1;
        while (i < j) {
            if (price[i] + price[j] < target)
                i++;
            else if (price[i] + price[j] > target)
                j--;
            else
                return {price[i], price[j]};
        }
        return {};
    }
};

// O(n), O(1)