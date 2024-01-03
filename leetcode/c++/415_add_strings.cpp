// https://leetcode.cn/problems/add-strings/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string addStrings(string num1, string num2) {
        int i = num1.length() - 1, j = num2.length() - 1, temp = 0;
        string res;
        while(i >= 0 || j >= 0 || temp > 0) {
            int num_i = (i >= 0)? num1[i] - '0' : 0; 
            int num_j = (j >= 0)? num2[j] - '0' : 0;
            int sum = temp + num_i + num_j;
            temp = sum / 10;
            sum = sum % 10;
            res.push_back('0' + sum);
            i--;
            j--;
        }
        reverse(res.begin(), res.end());
        return res;
    }
};

// 时间复杂度为O(max(num1.length(), num2.length())), 空间复杂度为O(1)