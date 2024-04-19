// https://leetcode.cn/problems/single-number-ii/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int one = 0, two = 0;
        for (int num : nums) {
            one = one ^ num & ~ two;
            two = two ^ num & ~ one;
        }
        return one;
    }
};

// 时间复杂度为O(n)，空间复杂度为O(1)
// 还是没理解，还是用下面那种万能法吧O(n), O(1)

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        vector<int> res(32, 0);
        int real_res = 0;
        for (int num : nums) {
            for (int i = 0; i < 32; ++i) {
                res[i] += (num & 1);
                num >>= 1;
            }
        }
        for (int i = 0; i < 32; ++i) {
            real_res += (res[i] % 3) << i;
        }
        return real_res;
    }
};