// https://leetcode.cn/problems/compare-version-numbers

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int compareVersion(string version1, string version2) {
        auto foo = [&](string& str) {
            for (auto& c : str) {
                if (c == '.')
                    c = ' ';
            }
        };
        foo(version1);
        foo(version2);
        istringstream is1(version1), is2(version2);;
        vector<int> v1, v2;
        int num;
        while (is1 >> num)
            v1.push_back(num);
        while (is2 >> num)
            v2.push_back(num);
        auto check = [&]()->int {
            for (int i = 0, j = 0; i < v1.size() || j < v2.size(); ++i, ++j) {
                int a = i < v1.size() ? v1[i] : 0;
                int b = j < v2.size() ? v2[j] : 0;
                if (a < b)
                    return -1;
                else if (a > b)
                    return 1;
            }
            return 0;
        };
        return check();
    }
};