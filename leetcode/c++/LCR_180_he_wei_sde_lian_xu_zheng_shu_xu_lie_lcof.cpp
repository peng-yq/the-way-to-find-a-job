// https://leetcode.cn/problems/he-wei-sde-lian-xu-zheng-shu-xu-lie-lcof

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> fileCombination(int target) {
        vector<vector<int>> res;
        vector<int> tmp;
        int sum = 0;
        for (int i = 1, j = 1; j <= target / 2 + 1; j++) {
            sum += j;
            tmp.push_back(j);
            while (sum > target) {
                sum -= i++;
            }
            if (sum == target) {
                vector<int> v(tmp.begin()+i-1, tmp.begin()+j);
                res.push_back(v);
            }              
        }
        return res;
    }
};

// 想不到数学办法，直接滑动窗口，O(n),O(1)