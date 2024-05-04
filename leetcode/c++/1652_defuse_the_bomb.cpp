// https://leetcode.cn/problems/defuse-the-bomb

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> decrypt(vector<int>& code, int k) {
        int n = code.size(), sum = 0;
        vector<int> res(n, 0);
        if (k == 0)
            return res;
        if (k > 0) {
            for (int i = 1; i <= k; ++i) {
                sum += code[i % n];
            }
            res[0] = sum;
            for (int i = 1; i < n; ++i) {
                sum -= code[i] - code[++k % n];
                res[i] = sum;
            }
        } else {
            for (int i = n + k; i < n; ++i) {
                sum += code[i];
            }
            res[0] = sum;
            int tmp = n + k;
            for (int i = 1; i < n; ++i) {
                sum -= code[tmp++ % n] - code[i-1];
                res[i] = sum;
            }
        }
        return res;
    }
};

// 时间复杂度为O(n)，空间复杂度为O(n)