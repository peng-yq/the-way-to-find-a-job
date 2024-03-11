// https://leetcode.cn/problems/zui-xiao-de-kge-shu-lcof

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> inventoryManagement(vector<int>& stock, int cnt) {
        sort(stock.begin(), stock.end());
        vector<int> res;
        for (int i = 0; i < cnt; i++)
            res.push_back(stock[i]);
        return res;
    }
};

// 直接调用库函数，时间复杂度为O(nlogn)，空间复杂度为O(n)

class Solution {
private:
    vector<int> quickSort(vector<int>& stock, int cnt, int l, int r) {
        int i = l, j = r;
        while (i < j) {
            while (i < j && stock[j] >= stock[l]) j--;
            while (i < j && stock[i] <= stock[l]) i++;
            swap(stock[i], stock[j]);
        }
        swap(stock[i], stock[l]);
        if (i < cnt) return quickSort(stock, cnt, i+1, r);
        if (i > cnt) return quickSort(stock, cnt, l, i-1);
        vector<int> res;
        res.assign(stock.begin(), stock.begin()+cnt);
        return res;
    }
public:
    vector<int> inventoryManagement(vector<int>& stock, int cnt) {
        if (cnt == stock.size())
            return stock;
        return quickSort(stock, cnt, 0, stock.size()-1);
    }
};

// 自己写快排，当i=cnt时直接返回，时间复杂度为O(n)，空间复杂度为O(logn)
// 相当于复习快排了，哨兵划分，一轮分为两部分，再逐渐递归