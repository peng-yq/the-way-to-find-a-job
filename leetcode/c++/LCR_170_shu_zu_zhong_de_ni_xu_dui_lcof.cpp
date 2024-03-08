// https://leetcode.cn/problems/shu-zu-zhong-de-ni-xu-dui-lcof

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int mergeSort(vector<int>& record, vector<int>& tmp, int l, int r) {
        if (l >= r)
            return 0;
        int m = l + (r-l) / 2;
        int res = mergeSort(record, tmp, l, m) + mergeSort(record, tmp, m+1, r);
        for (int k = l; k <= r; k++) 
            tmp[k] = record[k];
        int left_start = l, right_start = m+1;
        for (int k = l; k <= r; k++) {
            if (left_start == m+1)
                record[k] = tmp[right_start++];
            else if (right_start == r+1 || tmp[left_start] <= tmp[right_start])
                record[k] = tmp[left_start++]; // 稳定排序
            else {
                record[k] = tmp[right_start++];
                res += m-left_start+1;
            }
        } 
        return res;
    }
    int reversePairs(vector<int>& record) {
       vector<int> tmp(record.size(), 0);
       return mergeSort(record, tmp, 0, record.size() - 1);
    }
};

// 用归并排序来避免超时，在合并的时候统计逆序对，res += m-left_start+1这个很关键，因为左边都是排序好了的
// 只要比左边起始位置小，那么说明比左边所有剩余数都小
// 时间复杂度为O(nlogn)，空间复杂度为O(n)