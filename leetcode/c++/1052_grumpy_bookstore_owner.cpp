// https://leetcode.cn/problems/grumpy-bookstore-owner

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
        int res = 0, sum = 0, tmp = 0, n = customers.size();
        for (int left = 0, right = 0; right < n; ++right) {
            if (grumpy[right]) 
                tmp += customers[right];
            else 
                res += customers[right];
            if (right - left + 1 > minutes) {
                if (grumpy[left])
                    tmp -= customers[left];
                left++;
            }
            if (right - left + 1 == minutes)
                sum = max(sum, tmp);
        }
        return res + sum;
    }
};

// 看到连续，想到定长滑动窗口，本来不生气的分钟即使施展魔法也还是不生气，
// 改变的是生气的分钟，因此只需找出连续minutes中生气的最大人数
// 时间复杂度为O(n)，空间复杂度为O(1)