// https://leetcode.cn/problems/total-distance-traveled

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int distanceTraveled(int mainTank, int additionalTank) {
        int res = 0, flag = 0;
        while (mainTank) {
            res += 10;
            flag++;
            mainTank--;
            if (flag % 5 == 0 && additionalTank) {
                mainTank++;
                additionalTank--;
            }
        }
        return res;
    }
};

// 模拟，时间复杂度为O(n)