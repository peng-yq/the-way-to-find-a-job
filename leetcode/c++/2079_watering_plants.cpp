// https://leetcode.cn/problems/watering-plants

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int wateringPlants(vector<int>& plants, int capacity) {
        int res = 0, n = plants.size(), tmp = capacity;
        for (int i = 0; i < n; ++i) {
            if (capacity >= plants[i]) {
                res += 1;
                capacity -= plants[i];
            } else {
                res += i;
                capacity = tmp;
                res += i + 1;
                capacity -= plants[i];
            }
        }
        return res;
    }
};

// 模拟就完事了，纯纯简单题，O(n)，O(1)