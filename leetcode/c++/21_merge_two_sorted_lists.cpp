// https://leetcode.cn/problems/merge-two-sorted-lists/description

#include<bits/stdc++.h>
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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* head = new ListNode(0);
        ListNode* tmp = head;
        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val <= list2->val) {
                tmp->next = list1;
                list1 = list1->next;
            } else {
                tmp->next = list2;
                list2 = list2->next;
            }
            tmp = tmp->next;
        }
        tmp->next = list1 != nullptr ? list1 : list2;
        return head->next;
    }
};

// 时间复杂度为O(n+m)， 空间复杂度为O(1)