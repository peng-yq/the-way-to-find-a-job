// https://leetcode.cn/problems/spiral-matrix-ii/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        int l = 0, r = n - 1, t = 0, b = n - 1, num = 1;
        vector<vector<int>>res(n, vector<int>(n));
        while (true) {
            for (int i = l; i <= r; i++) res[t][i] = num++;
            if (++t > b) break;
            for (int i = t; i <= b; i++) res[i][r] = num++;
            if (--r < l) break;
            for (int i = r; i >= l; i--) res[b][i] = num++;
            if (--b < t) break;
            for (int i = b; i >= t; i--) res[i][l] = num++;
            if (++l > r) break;
        }
        return res;
    }
};

// 时间和空间复杂度为O(n^2)