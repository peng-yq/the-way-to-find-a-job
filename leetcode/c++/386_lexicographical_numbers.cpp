// https://leetcode.cn/problems/lexicographical-numbers

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> lexicalOrder(int n) {
        vector<int> res(n);
        // 最小的字典序是1
        int number = 1;
        for (int i = 0; i < n; ++i) {
            res[i] = number;
            if (number * 10 <= n) {
                number *= 10;
            } else {
                while (number % 10 == 9 || number + 1 > n) {
                    number /= 10;
                }
                ++number;
            }
        }
        return res;
    }
};