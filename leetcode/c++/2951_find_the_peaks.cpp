// https://leetcode.cn/problems/find-the-peaks

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findPeaks(vector<int>& mountain) {
        vector<int>res;
        int n = mountain.size();
        for (int i = 1; i < n - 1; ++i) {
            if (mountain[i] > mountain[i - 1] && mountain[i] > mountain[i + 1])
                res.push_back(i);
        }
        return res;
    }
};

// 小学生题，O(n)，O(1)