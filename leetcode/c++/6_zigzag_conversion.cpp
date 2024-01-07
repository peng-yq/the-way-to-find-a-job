// https://leetcode.cn/problems/zigzag-conversion/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows < 2)
            return s;
        vector<string> res(numRows);
        int i = 0, flag = -1;
        for (char ch : s) {
           res[i].push_back(ch);
           if (i == 0 || i == numRows - 1)
            flag = - flag;
            i += flag;
        }
        string res_string;
        for (i = 0; i < numRows; i++) 
            res_string += res[i];
        return res_string;
    }
};

// 时间复杂度为和空间复杂度为O(n)