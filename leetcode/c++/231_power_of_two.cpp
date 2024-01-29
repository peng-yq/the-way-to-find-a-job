// https://leetcode.cn/problems/power-of-two/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isPowerOfTwo(int n) {
       return n > 0 && (n&(n-1)) == 0;
    }
};

// O(1)