// https://leetcode.cn/problems/bu-ke-pai-zhong-de-shun-zi-lcof

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool checkDynasty(vector<int>& places) {
        int res = 0, count = 0;
        sort(places.begin(), places.end());
        for (int i = 0; i < places.size() - 1; i++) {
            if (places[i] == 0)
                count++;
            else if (places[i+1] == places[i])
                return false;
            else 
                res += places[i+1] - places[i];
        }
        return count >= abs(res - 4);
    }
};

