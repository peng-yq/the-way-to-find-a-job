// https://leetcode.cn/problems/distribute-candies

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int distributeCandies(vector<int>& candyType) {
        int res = 0, n = candyType.size(), top = n / 2;
        unordered_set<int> types;
        for (int i = 0; i < n && top > 0; ++i) {
            if (!types.count(candyType[i])) {
                ++res;
                --top;
                types.insert(candyType[i]);
            }
        }
        return res;
    }
};

// O(n)，O(n)