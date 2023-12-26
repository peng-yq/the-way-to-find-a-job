// https://leetcode.cn/problems/find-median-from-data-stream/description

#include<bits/stdc++.h>
using namespace std;

class MedianFinder {
public:
    // 创建大小堆使得在添加元素时就使得元素有序，使用sort则会超时
    priority_queue<int, vector<int>, greater<int>> A;
    priority_queue<int, vector<int>, less<int>> B;
    MedianFinder() {

    }
    
    void addNum(int num) {
        if (A.size() == B.size()) {
            B.push(num);
            A.push(B.top());
            B.pop();
        } else {
            A.push(num);
            B.push(A.top());
            A.pop();
        }
    }
    
    double findMedian() {
        if (A.size() == B.size())
            return (A.top() + B.top()) / 2.0;
        else 
            return double(A.top());
    }
};

// 时间复杂度为O(logn)，空间复杂度为O(n)