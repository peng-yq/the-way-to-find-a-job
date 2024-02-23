// https://leetcode.cn/problems/fu-za-lian-biao-de-fu-zhi-lcof/description

#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class Solution {
public:
    Node* copyRandomList(Node* head) {
        unordered_map<Node*, Node*> map;
        Node* tmp = head;
        while (tmp) {
            map[tmp] = new Node(tmp->val);
            tmp = tmp->next;
        }
        tmp = head;
        while (tmp) {
            map[tmp]->next = map[tmp->next];
            map[tmp]->random = map[tmp->random];
            tmp = tmp->next;
        }
        return map[head];
    }
};

// 时间复杂度O(n)，空间复杂度O(n)