// https://leetcode.cn/problems/shu-ju-liu-zhong-de-zhong-wei-shu-lcof

#include <bits/stdc++.h>
using namespace std;

class MedianFinder {
public:
    /** initialize your data structure here. */
    priority_queue<int, vector<int>, greater<int>> minHeap;
    priority_queue<int, vector<int>, less<int>> maxHeap;
    MedianFinder() {

    }
    
    void addNum(int num) {
        if (minHeap.size() == maxHeap.size()) {
            minHeap.push(num);
            maxHeap.push(minHeap.top());
            minHeap.pop();
        } else {
            maxHeap.push(num);
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        }
    }
    
    double findMedian() {
        if (minHeap.size() == maxHeap.size()) 
            return (minHeap.top() + maxHeap.top()) / 2.0;
        else 
            return maxHeap.top() / 1.0;
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */

// 类的设计很巧妙，利用堆把添加元素的时间压缩到O(logn)，使用sort的话时间则为O(nlogn)，二分查找为O(n)(找到位置为O(logn)，插入元素为O(n))