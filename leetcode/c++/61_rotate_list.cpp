// https://leetcode.cn/problems/rotate-list

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
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == nullptr || k == 0) 
            return head;
        int n = 1;
        ListNode* oldTail = head, *newHead = head;
        while(oldTail->next) {
            ++n;
            oldTail = oldTail->next;
        }
        k %= n;
        if (k == 0)
            return head;
        for (int i = 0; i < n - k - 1; ++i)
            newHead = newHead->next;
        ListNode* tmp = newHead->next;
        newHead->next = nullptr;
        newHead = tmp;
        oldTail->next = head;
        return newHead;
    }
};

// O(n), O(1)