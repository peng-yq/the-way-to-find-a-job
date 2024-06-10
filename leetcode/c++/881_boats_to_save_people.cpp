// https://leetcode.cn/problems/boats-to-save-people

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        int n = people.size(), res = 0, i = 0, j = n - 1;
        sort(people.begin(), people.end());
        while (i <= j) {
            if (i == j) {
                ++res;
                break;
            }
            if (people[i] + people[j] <= limit) {
                ++i;
            }
            --j;
            ++res;
        }
        return res;
    }
};

// 时间复杂度O(nlogn)，空间复杂度O(1)
// 排序+双指针，让大体重的先上，能带上一个轻的就带一个轻的