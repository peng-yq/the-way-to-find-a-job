// https://leetcode.cn/problems/watering-plants-ii

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumRefill(vector<int>& plants, int capacityA, int capacityB) {
        int res = 0, n = plants.size(), tmpA = capacityA, tmpB = capacityB;
        int i = 0, j = n - 1;
        while (i < j) {
            if (tmpA >= plants[i]) {
                tmpA -= plants[i];
            } else {
                res += 1;
                tmpA = capacityA;
                tmpA -= plants[i];
            }
            i++;
            if (tmpB >= plants[j]) {
                tmpB -= plants[j];
            } else {
                res += 1;
                tmpB = capacityB;
                tmpB -= plants[j];
            }
            j--;
        }
        if (i == j) {
            if (max(tmpA, tmpB) < plants[i]) {
                res += 1;
            }
        }
        return res;
    }
};

// 双指针模拟就行了，“中等题”，难绷，O(n)，O(1)