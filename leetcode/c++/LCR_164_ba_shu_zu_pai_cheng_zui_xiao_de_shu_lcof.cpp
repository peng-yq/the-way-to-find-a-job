// https://leetcode.cn/problems/ba-shu-zu-pai-cheng-zui-xiao-de-shu-lcof

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    static bool compare(const string& a, const string& b) {
        return a + b < b + a;
    }
public:
    string crackPassword(vector<int>& password) {
        vector<string> strs;
        string res;
        for (auto num : password)
            strs.push_back(to_string(num));
        sort(strs.begin(), strs.end(), compare);
        for (auto str : strs)
            res += str;
        return res;
    }
};

// 时间复杂度为O(nlogn)，排序算法的平均时间复杂度，空间复杂度为O(n)
// 属于做过就是简单题那种题