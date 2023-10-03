// https://leetcode.cn/problems/two-sum/description/
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
        最简单的暴力枚举，时间复杂度为O(n^2)，空间复杂度为O(1)
    */
    vector<int> twoSum(vector<int>& nums, int target) {
        for (int i = 0; i < nums.size(); i++){
            for (int j = i + 1; j < nums.size(); j++){
                if (nums[i] + nums[j] == target){
                    return {i, j};
                }
            }
        }
        return {};
    }

    /*
        采用哈希表的方式，将寻找target - x的时间复杂度降为O(1)
        时间复杂度为O(n)，空间复杂度为O(n)
    */
    vector<int> twoSumHash(vector<int>& nums, int target) {
        unordered_map<int, int> hashtable;
        for (int i = 0; i < nums.size(); i++){
            auto it = hashtable.find(target - nums[i]);
            if (it != hashtable.end()) {
                return {it->second, i};
            }
            hashtable[nums[i]] = i;
        }
        return {};
    }
};



