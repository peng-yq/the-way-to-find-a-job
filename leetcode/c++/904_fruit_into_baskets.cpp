// https://leetcode.cn/problems/fruit-into-baskets/description/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        unordered_map<int, int> fruit;
        int res = 0;
        for (int l = 0, r = 0; r < fruits.size(); r++) {
            fruit[fruits[r]]++;
            if (fruit.size() > 2) {
                if (--fruit[fruits[l]] == 0) {
                    fruit.erase(fruits[l]);
                }
                l++;
            }
            res = max(res, r - l + 1);
        }
        return res;
    }
};

// 时间复杂度和空间复杂度均为O(n)