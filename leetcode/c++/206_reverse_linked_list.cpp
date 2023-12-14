// https://leetcode.cn/problems/reverse-linked-list/description

#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* tmp;
        ListNode* newhead = new ListNode(0);
        while (head != nullptr) {
            tmp = head->next;
            head->next = newhead->next;
            newhead->next = head;
            head = tmp; 
        }
        return newhead->next;
    }
};

// 时间复杂度为O(n)，空间复杂度为O(1)