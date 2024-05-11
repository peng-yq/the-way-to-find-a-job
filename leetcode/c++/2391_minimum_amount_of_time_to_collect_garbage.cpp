//https://leetcode.cn/problems/minimum-amount-of-time-to-collect-garbage

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    int metal_ = 0;
    int paper_ = 0;
    int glass_ = 0;
    void count(const string& str, int i, vector<int>& house) {
        for (auto ch : str) {
            if (ch == 'M') {
                metal_++;
                house[0] = max(house[0], i);
            }
            if (ch == 'P') {
                paper_++;
                house[1] = max(house[1], i);
            }
            if (ch == 'G') {
                glass_++;
                house[2] = max(house[2], i);
            }
        }
    }
public:
    int garbageCollection(vector<string>& garbage, vector<int>& travel) {
        int res = 0;
        vector<int> house(3, 0);
        for (int i = 0; i < garbage.size(); ++i) 
            count(garbage[i], i, house);
        res += metal_ + paper_ + glass_;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < house[i]; ++j) 
                res += travel[j];
        }
        return res;
    }
};

// 纯纯简单题，记录最后一个垃圾出现的位置就行，模拟就完事了时间复杂度为O(nk+n)，空间复杂度为O(1)