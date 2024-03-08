// https://leetcode.cn/problems/da-yin-cong-1dao-zui-da-de-nwei-shu-lcof

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> countNumbers(int cnt) {
        for (int i = 1; i <= cnt; i++) {
            cur(0, i);
        }
        vector<int> resInt;
        for (auto& s : res)
            resInt.push_back(stoi(s));
        return resInt;
    }
private:
    vector<string> res;
    string str;
    void cur(int x, int len) {
        if (x == len) {
            res.push_back(str);
            return;
        }
        for (int i = x == 0? 1 : 0; i < 10; i++) {
            str += '0' + i;
            cur(x+1, len);
            str.pop_back();
        }
    }
};

// 垃圾lc，本来是考察大数越界的情况，也就是全排列问题，递归
// 时间复杂度和空间复杂度均为O(10^cnt)