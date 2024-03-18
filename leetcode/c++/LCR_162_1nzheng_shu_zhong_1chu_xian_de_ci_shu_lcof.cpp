// https://leetcode.cn/problems/1nzheng-shu-zhong-1chu-xian-de-ci-shu-lcof

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int digitOneInNumber(int num) {
        int count = 0;
        int digit = 1;
        int tmp = num;
        while(tmp) {
            int cur = num / digit % 10;
            int low = num % digit;
            int high = num / digit / 10;
            tmp /= 10;
            if (cur > 1)
                count += (high+1) * digit;
            else if (cur == 1)
                count += high * digit + low + 1;
            else 
                count += high * digit;
            digit *= 10;
        }
        return count;
    }
};

// 解法就是求每一位出现1的概率，把数分为当前位，高位和低位，根据当前位和1的关系去计算当前位1的出现次数
// 用5321为例去带入就好理解了
// 时间复杂度为O(logn)，空间复杂度为O(1)