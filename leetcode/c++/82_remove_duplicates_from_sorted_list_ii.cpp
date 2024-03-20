// https://leetcode.cn/problems/remove-duplicates-from-sorted-list-ii/

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
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == nullptr) return head;
        
        ListNode* dummy = new ListNode(0, head); 
        ListNode* cur = dummy; 
        while (head) {
            if (head->next && head->val == head->next->val) {
                int x = head->val;
                while (head && head->val == x) { 
                    head = head->next;
                }
                cur->next = head; 
            } else {
                cur = cur->next; 
                head = head->next; 
            }
        }
        
        return dummy->next;
    }
};

// O(n), O(1)
