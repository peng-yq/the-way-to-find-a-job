// https://leetcode.cn/problems/average-salary-excluding-the-minimum-and-maximum-salary

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    double average(vector<int>& salary) {
        int n = salary.size();
        sort(salary.begin(), salary.end());
        double res = 0;
        for (int i = 1; i < n-1; ++i) {
            res += salary[i];
        }
        return res / (n-2);
    }
};

// 最简单的一集，时间复杂度为O(nlogn)，空间复杂度为O(1)
// 下面使用c++20的特性可以使时间复杂度达到O(n)

double average(vector<int>& salary) {
    int sum = reduce(salary.begin(), salary.end());
    auto [m, M] = ranges::minmax(salary);
    return (double) (sum - m - M) / (salary.size() - 2);
}