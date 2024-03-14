// https://leetcode.cn/problems/yuan-quan-zhong-zui-hou-sheng-xia-de-shu-zi-lcof

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int iceBreakingGame(int num, int target) {
        int res = 0;
        for (int i = 2; i <= num; i++)
            res = (res + target) % i;
        return res;
    }
};

// 解决约瑟夫环问题的关键在于，n个人的结果可以从n-1个人推到而来，因此从1个人开始，推到n个人
// O(n)，O(1)