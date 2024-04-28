// https://leetcode.cn/problems/convert-to-base-2

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string baseNeg2(int n) {
        if (n == 0) 
            return "0";
        string res;
        while (n) {
            int x = n / -2;
            int y = n % -2;
            while (y < 0) {
                x += 1;
                y = n - (-2 * x);
            }
            n = x;
            res.push_back(y + '0');
        }
        reverse(res.begin(), res.end());
        return res;
    }
};


// 考察怎么转换-2进制，注意-2进制表示没有正号和负号之分，
// 将1个10进制数转换为-2进制，只需要一直除-2，直到商为0，然后逆序将余数拼接起来
// 这里需要注意调整余数的大小为0或1
/*
假设我们要将十进制的 6 转换为负二进制：
6 ÷ -2 = -3 余 0
-3 ÷ -2 = 2 余 1 （因为 -3 / -2 = 1.5，向下取整为 -3 / -2 = -2 时余数为 1）
2 ÷ -2 = -1 余 0
-1 ÷ -2 = 1 余 1
1 ÷ -2 = 0 余 1
所以，6 的负二进制表示为 11010。
*/
// 时间复杂度为O(logn)，空间复杂度为(logn)，和循环的次数有关

