// https://leetcode.cn/problems/design-hashmap

#include <bits/stdc++.h>
using namespace std;

class MyHashMap {
private:
    vector<list<pair<int, int>>> set;
    static const int base = 7777;
    static int hash (int key) {
        return key % base;
    }
public: 
    MyHashMap() : set(base) {

    }
    
    void put(int key, int value) {
        int index = hash(key);
        for (auto it = set[index].begin(); it != set[index].end(); it++) {
            if ((*it).first == key) {
                (*it).second = value;
                return;
            }
        }
        set[index].push_back({key, value});
    }
    
    int get(int key) {
        int index = hash(key);
        for (auto it = set[index].begin(); it != set[index].end(); it++) {
            if ((*it).first == key) {
                return (*it).second;
            }
        }
        return -1;
    }
    
    void remove(int key) {
        int index = hash(key);
        for (auto it = set[index].begin(); it != set[index].end(); it++) {
            if ((*it).first == key) {
                set[index].erase(it);
                return;
            }
        }
    }
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */