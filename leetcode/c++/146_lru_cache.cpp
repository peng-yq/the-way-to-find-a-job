// https://leetcode.cn/problems/lru-cache

#include <bits/stdc++.h>
using namespace std;

class LRUCache {
private:
    int _capacity;
    list<pair<int, int>> cache;
    unordered_map<int, decltype(cache.begin())> cache_map;
public: 
    LRUCache(int capacity) : _capacity(capacity){}
    
    int get(int key) {
        if (cache_map.contains(key)) {
            cache.splice(cache.begin(), cache, cache_map[key]);
            return cache.front().second;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if (!cache_map.contains(key)) {
            if (cache.size() == _capacity) {
                cache_map.erase(cache.back().first);
                cache.pop_back();
            }
            cache_map[key] = cache.emplace(cache.begin(), key, value);
        } else {
            cache.splice(cache.begin(), cache, cache_map[key]);
            cache.front().second = value;
        }
    }
};

// 终于刷到LRU了，关键在于如何维护一个O(1)时间的LRU缓存表，使得插入和删除一个缓存都是O(1)
// 数组肯定不行，只能链表，为什么要双链表呢，是因为能在O(1)时间获得尾指针，并且双向指针使得删除一个节点很快（如果是单链表肯定得遍历）
// 再结合哈希表保存迭代器能实现put和get时间复杂度为O(1)