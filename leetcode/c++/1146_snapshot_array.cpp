// https://leetcode.cn/problems/snapshot-array

#include <bits/stdc++.h>
using namespace std;

class SnapshotArray {
private:
    vector<map<int, int>> data;
    int snapId;
public:
    SnapshotArray(int length) : data(length), snapId(0) {
    }
    
    void set(int index, int val) {
        data[index][snapId] = val;
    }
    
    int snap() {
        return snapId++;
    }
    
    int get(int index, int snap_id) {
        auto& map = data[index];
        if (map.count(snap_id)) {
            return map[snap_id];
        }
        auto it = map.upper_bound(snap_id);
        if (it == map.begin()) {
            return 0;
        } else {
            --it;
            return it->second;
        }
    }
};

// 一开始用vector<vector<int>>内存爆了，不过肯定会爆，毕竟我直接把每个里面的vector<int>初始化为了50000大小
// 实际应该使用哈希表来存，注意这里因为快照号是连续的，因此为了方便遍历，使用map，虽然查找时间为O(logn)，比unordered_map的O(1)，慢了不少
// 但是方便查找，unordered_map还要自己实现逻辑
// 前面初始化，set和snap都很常规，最关键的是get
// 如果data[index]这个哈希表有snap_id这个key，那我们就直接返回
// 如果没有表示在这个快照号没有对索引为index的元素进行赋值或更新，因此通过upper_bound查找比当前snap_id大的第一个迭代器，
// 如果迭代器指向begin()，表示两种情况，第一种是map为空，第二种是第一个大于snap_id的快照号是map的第一个，两种情况都直接返回0，
// 否则我们将迭代器-1，再返回，也就是前面一个比snap_id小的的快照