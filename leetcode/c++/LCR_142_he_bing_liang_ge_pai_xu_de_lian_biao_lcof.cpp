// https://leetcode.cn/problems/he-bing-liang-ge-pai-xu-de-lian-biao-lcof/description

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
    ListNode* trainningPlan(ListNode* l1, ListNode* l2) {
        ListNode* head = new ListNode(0);
        ListNode* tmp = head;
        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val <= l2->val) {
                tmp->next = l1;
                l1 = l1->next;
            } else {
                tmp->next = l2;
                l2 = l2->next;
            }
            tmp = tmp->next;
        }
        tmp->next = l1 != nullptr ? l1 : l2;
        return head->next;
    }
};

// O(n+m)， O(1)
// 复习x