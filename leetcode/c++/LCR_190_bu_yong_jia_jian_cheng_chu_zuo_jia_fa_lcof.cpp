// https://leetcode.cn/problems/bu-yong-jia-jian-cheng-chu-zuo-jia-fa-lcof

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int encryptionCalculate(int dataA, int dataB) {
        while (dataB != 0) {
            int c = (unsigned int) (dataA & dataB) << 1; // 计算进位
            dataA ^= dataB; // 计算无进位和
            dataB = c; 
        }
        return dataA;
    }
};

// O(1), O(1)
// 在进行位运算时，C++ 默认对整数使用有符号的算术运算。
// 由于a & b可能会导致它变成负数（高位符号位为1），而负数再进行左移操作可能会产生不符合预期的结果。
// 为了避免负数的左移问题，对a & b进行了强制转换为无符号整数类型（static_cast< unsigned int >）。
// 这样，static_cast< unsigned int >(a & b)左移一位后，高位不再是符号位，而是补零。
// 这样就确保了计算的正确性和避免了负数的问题。