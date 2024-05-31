// https://leetcode.cn/problems/distribute-candies-among-children-i

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int distributeCandies(int n, int limit) {
        int res = 0;
        for (int i = 0; i <= limit; ++i) {
            for (int j = 0; j <= limit; ++j) {
                if (n - i - j <= limit && n - i - j >= 0)
                    ++res;
            }
        }
        return res;
    }
};

// O(limit^2)，O(1)
// 没绷住，哥们儿一开始还用回溯，还尼玛是错的