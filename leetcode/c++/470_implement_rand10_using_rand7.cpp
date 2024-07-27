// https://leetcode.cn/problems/implement-rand10-using-rand7

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int rand10() {
        while (true) {
            int x = (rand7() - 1) * 7 + (rand7() - 1);
            if (x >= 0 && x <= 39)
                return x % 10 + 1;
        }
    }
};