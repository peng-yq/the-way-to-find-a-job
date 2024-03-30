// https://leetcode.cn/problems/swap-nodes-in-pairs

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
    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;
        ListNode* dummy = new ListNode(0, head);
        ListNode* current = dummy;
        while (current->next != nullptr && current->next->next != nullptr) {
            ListNode* first = current->next;
            ListNode* second = current->next->next;
            first->next = second->next;
            second->next = first;
            current->next = second;
            current = first;
        }
        ListNode* res = dummy->next;
        delete dummy;
        return res;
    }
};

// 0(n) 0(1)，交换完记得把前面那个指向后面的
