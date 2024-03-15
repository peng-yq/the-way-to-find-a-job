// https://leetcode.cn/problems/shu-zu-zhong-shu-zi-chu-xian-de-ci-shu-lcof

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> sockCollocation(vector<int>& sockets) {
        int res = 0;
        for (int socket : sockets)
            res ^= socket;
        int m = 1;
        while ((m & res) == 0)
            m <<= 1;
        int x = 0, y = 0;
        for (int socket : sockets) {
            if ((socket & m) == 0)
                x ^= socket;
            else 
                y ^= socket;
        }
        return {x, y};
    }
};

// 时间复杂度为O(n)，空间复杂度为O(1)
// 第一次异或所有元素得到的结果为x^y，这两肯定至少有一位不同，即某一位为1
// 使用m去得到最低位的1，目的是为了将x和y分为两个子数组
// 遍历数组，分为两个子数组，此时x和y肯定分布在两个不同的数组，并且每个数组里面相等的元素均为两个，此时进行异或即可求得目标值