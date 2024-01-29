// https://leetcode.cn/problems/candy/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int candy(vector<int>& ratings) {
        vector<int>candies(ratings.size(), 1);
        for (int i = 1; i < ratings.size(); i++) {
            if (ratings[i] > ratings[i-1] && candies[i] <= candies[i-1])
                candies[i] = candies[i-1] + 1;
        }
        for (int i = ratings.size() - 1; i > 0; i --) {
             if (ratings[i] < ratings[i-1] && candies[i] >= candies[i-1])
                candies[i-1] = candies[i] + 1;
        }
        return accumulate(candies.begin(), candies.end(), 0);
    }
};

// 时间复杂度为O(n)，空间复杂度为O(n)