// https://leetcode.cn/problems/two-sum-ii-input-array-is-sorted/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        unordered_map<int, int> num_map;
        for (int i = 0; i < numbers.size(); i++) {
            if (num_map.find(target - numbers[i]) != num_map.end()) 
                return {num_map[target - numbers[i]], i + 1};
            num_map[numbers[i]] = i+1;
        }
        return {};
    }
};

// 虽然题目要求是常数级的空间复杂度，但还是过了....

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int i = 0, j = numbers.size() - 1;
        while (numbers[i] + numbers[j] != target && i < j) {
            if (numbers[i] + numbers[j] < target) 
                i++;
            else 
                j--;
        }
       if (numbers[i] + numbers[j] == target)
            return {i+1, j+1};
        return {};
    }
};

// 时间复杂度O(n)，空间复杂度O(1)