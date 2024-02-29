// https://leetcode.cn/problems/er-wei-shu-zu-zhong-de-cha-zhao-lcof/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool findTargetIn2DPlants(vector<vector<int>>& plants, int target) {
        int i = plants.size() - 1, j = 0;
        while (i >= 0 && j < plants[0].size()) {
            if (plants[i][j] < target)
                j++;
            else if (plants[i][j] > target) 
                i--;
            else 
                return true;
        }
        return false;
    }
};

// 一次可以排除一列或者一行，当然也可以从右上角开始，但是需要处理plants为空的情况，而左下角则因为i此时被初始化为-1，则直接返回false
// 时间复杂度为O(m+n)，空间复杂度为O(1)