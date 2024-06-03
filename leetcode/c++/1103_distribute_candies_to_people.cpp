// https://leetcode.cn/problems/distribute-candies-to-people

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> distributeCandies(int candies, int num_people) {
        vector<int> res(num_people, 0);
        int pre = 0;
        for (int i = 0; candies > 0; ++i) {
            res[i % num_people] += min(pre + 1, candies); 
            candies -= min(pre + 1, candies); 
            ++pre;
        }
        return res;
    }
};

// O(n)，O(1)