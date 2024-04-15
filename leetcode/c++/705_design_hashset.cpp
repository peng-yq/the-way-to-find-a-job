// https://leetcode.cn/problems/design-hashset

#include <bits/stdc++.h>
using namespace std;

class MyHashSet {
private:
    vector<bool> set;
public:
    MyHashSet() : set(1e6+1, false) {

    }
    
    void add(int key) {
        set[key] = true;
    }
    
    void remove(int key) {
        set[key] = false;
    }
    
    bool contains(int key) {
        return set[key];
    }
};

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */

class MyHashSet {
private:
    vector<list<int>> set;
    static const int base = 7988;
    static int hash (int key) {
        return key % base;
    }
public:
    MyHashSet() : set(base) {
        
    }
    
    void add(int key) {
        int index = hash(key);
        for (auto it = set[index].begin(); it != set[index].end(); it++) {
            if ((*it) == key)
                return;
        }
        set[index].push_back(key);
    }
    
    void remove(int key) {
        int index = hash(key);
        for (auto it = set[index].begin(); it != set[index].end(); it++) {
            if ((*it) == key) {
                set[index].erase(it);
                return;
            }
        }
    }
    
    bool contains(int key) {
        int index = hash(key);
        for (auto it = set[index].begin(); it != set[index].end(); it++) {
            if ((*it) == key)
                return true;
        }
        return false;
    }
};

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */

// 链地址法，时间复杂度为O(n/b)，n为总的元素，b为桶的数量
// 空间复杂度为O(n+b)