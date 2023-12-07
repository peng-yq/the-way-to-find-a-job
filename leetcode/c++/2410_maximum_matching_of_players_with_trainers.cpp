// https://leetcode.cn/problems/maximum-matching-of-players-with-trainers/description/

#include <bits/stdc++.h>
using namespace std;

// 时间复杂度O(nlogn)，sort的时间复杂度，空间复杂度O(1)
class Solution {
public:
    int matchPlayersAndTrainers(vector<int>& players, vector<int>& trainers) {
        sort(players.begin(), players.end());
        sort(trainers.begin(), trainers.end());
        int i = 0, j = 0, res = 0;
        while(i < players.size() && j < trainers.size()) {
            if (players[i] <= trainers[j]) {
                i++;
                res++;
            }
            j++;
        }
        return res;
    }
};