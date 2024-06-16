// https://leetcode.cn/problems/count-pairs-that-form-a-complete-day-ii

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long countCompleteDayPairs(vector<int>& hours) {
        unordered_map<int, int> hourMap;
        unordered_set<int> s;
        long long res = 0;
        for (auto hour : hours)
            ++hourMap[hour % 24];
        for (int i = 0; i < 24; ++i) {
            if (i == 0 || i == 12)
                res += (long(hourMap[i]) * long(hourMap[i] - 1) / 2);
            else {
                if (!s.count(i) && !s.count(24 -i)){
                    res += (long(hourMap[i]) * long(hourMap[24 - i]));
                    s.insert(i);
                    s.insert(24 - i);
                }
            }
        }
        return res;
    }
};

// 用哈希表存储对24求余数为0-23的元素的数量
// O(n), O(1)