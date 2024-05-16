// https://leetcode.cn/problems/maximum-number-of-weeks-for-which-you-can-work

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long numberOfWeeks(vector<int>& milestones) {
        long long maxNum = 0, index = 0, n = milestones.size(), sum = 0;
        for (int i = 0; i < n; ++i) {
            if (milestones[i] > maxNum) {
                index = i;
                maxNum = milestones[i];
            }
            sum += milestones[i];
        }
        if (maxNum > sum - maxNum + 1) 
            return 2 * (sum - maxNum) + 1;
        return sum;
    }
};

// 时间复杂度为O(n)，空间复杂度为O(1)
// 构造题或者说数学题，只需要考虑其中最大的元素，我们先将最大的元素的下标排列在偶数下标，其他元素依次排列到奇数下标位
// 这样可以保证两两之间不是同一个项目，但是要是最大的元素很大呢？那这个边界是多少呢？
// 其他元素的总和为所有的和s-最大元素的值m，m最大可以为s-m+1，序列长度为2*（s-m）+1，m超过s-m+1，那么后面的工作则不能完成
// 如果m<=s-m+1，则一定可以完成所有工作，结果为s，局部最优保证全局最优