// https://leetcode.cn/problems/multiply-strings/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string multiply(string num1, string num2) {
        int m = num1.size(), n = num2.size();
        // m长度的数乘以n长度的数得到的数最大长度为m+n
        vector<int> A, B, C(m + n);
        // 逆序保存num1和num2，方便计算
        for (int i = m - 1; i >= 0; --i)
            A.push_back(num1[i] - '0');
        for (int j = n - 1; j >= 0; --j)
            B.push_back(num2[j] - '0');
        // 计算乘积的个位
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                C[i + j] += A[i] * B[j];
            }
        }
        // 处理进位
        int t = 0;
        for (int i = 0; i < m + n; ++i) {
            t += C[i];
            C[i] = t % 10;
            t /= 10;
        }
        // 去除前导0，注意这里不要去除最后一位0
        int k = m + n - 1;
        while (k > 0 && !C[k])
            --k;
        string res;
        // 拼接字符串
        while (k >= 0)
            res += C[k--] + '0';
        return res;
    }
};

// O(mn), O(m+n)