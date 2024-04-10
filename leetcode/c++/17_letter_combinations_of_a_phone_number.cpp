// https://leetcode.cn/problems/letter-combinations-of-a-phone-number

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    const vector<string> numChars = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> res;
    string tmp;
    void dfs(string digits, int start) {
        if (tmp.length() == digits.length()) {
            res.push_back(tmp);
            return;
        }
        for (int i = start; i < digits.length(); i++) {
            for (int j = 0; j < numChars[digits[i] - '0' - 2].length(); j++) {
                tmp += numChars[digits[i] - '0' - 2][j];
                dfs(digits, i+1);
                tmp.pop_back();
            }
        }
    }
public:
    vector<string> letterCombinations(string digits) {
        if (digits == "")
            return {};
        dfs(digits, 0);
        return res;
    }
}; 

// 时间复杂度为O(n*4^n)，空间复杂度为O(n)