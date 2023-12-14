// https://leetcode.cn/problems/partition-list/description

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
    ListNode* partition(ListNode* head, int x) {
        ListNode* list1 = new ListNode();
        ListNode* list2 = new ListNode();
        ListNode* end1 = list1;
        ListNode* end2 = list2;
        while (head != nullptr) {
            if (head->val < x) {              
                end1->next = head;
                end1 = end1->next;              
            } else {
                end2->next = head;
                end2 = end2->next;
            }
            head = head->next;
        }
        end2->next = nullptr;
        end1->next = list2->next;
        ListNode* res = list1->next;
        delete list1;
        delete list2;
        return res;
    }
};

// 时间复杂度为O(n)，空间复杂度为O(1)