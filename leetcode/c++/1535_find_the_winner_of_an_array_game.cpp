// https://leetcode.cn/problems/find-the-winner-of-an-array-game

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int getWinner(vector<int>& arr, int k) {
        int count = 0, pre = arr[0];
        for (int i = 1; i < arr.size(); ++i) {
            if (count == k)
                return pre;
            if (max(arr[i], pre) == pre)
                ++count;
            else {
                pre = arr[i];
                count = 1;
            }
        }
        return pre;
    }
};

// 透过现象看本质，压根不用去管每回合比较中小的那个移动到最后一个位置，大的移动到第一个位置
// 每次比较都是上一轮最大的数（第一轮比较可以看作上一轮最大的数就是第一个元素）和当前元素进行比较
// 如果本次获胜的还是上一轮最大的数，那么获胜次数加一，否则获胜次数变为1，更新上一轮获胜的最大的数
// 如果胜利次数等于k，则返回；如果一次遍历后，获胜次数仍然小于k，因为此时获胜的元素已经是数组中最大的元素了
// 不管比较多少次都是它获胜，因此也返回该元素即可。