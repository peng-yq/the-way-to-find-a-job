// https://leetcode.cn/problems/reverse-linked-list-ii

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
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode* dummy = new ListNode(0, head);
        ListNode* p0 = dummy;
        for (int i = 0; i < left - 1; ++i) 
            p0 = p0->next;
        ListNode* cur = p0->next;
        ListNode* pre = nullptr;
        for (int i = left; i <= right; ++i) {
            ListNode* tmp = cur->next;
            cur->next = pre;
            pre = cur; 
            cur = tmp;
        }
        p0->next->next = cur;
        p0->next = pre;
        return dummy->next;
    }
};

// O(n), O(1),
// pre表示需要反转的最后一个节点，cur表示需要反转的最后一个节点的下一个节点