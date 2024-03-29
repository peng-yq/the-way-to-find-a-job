// https://leetcode.cn/problems/palindrome-linked-list

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
    ListNode* midList(ListNode* head) {
        ListNode* slow = head, *fast = head;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        } 
        return slow;
    }
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        while (head != nullptr) {
            ListNode* temp = head->next;
            head->next = prev;
            prev = head;
            head = temp;
        }
        return prev; 
    }
    bool cmpList(ListNode* head1, ListNode* head2) {
        ListNode* tmp1 = head1, *tmp2 = head2;
        while (tmp1 != nullptr && tmp2 != nullptr) {
            if (tmp1->val == tmp2->val) {
                tmp1 = tmp1->next;
                tmp2 = tmp2->next;
            } else {
                return false;
            }
        }
        return true;
    }
    bool isPalindrome(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return true;
        ListNode* mid = midList(head);
        ListNode* last = reverseList(mid);     
        bool res = cmpList(head, last);
        mid = reverseList(last); 
        return res;
    }
};

// 又是一道大杂烩题，当然如果不要求空间复杂度为O(1)的话，直接用栈保存链表中所有节点的值，再出栈对比即可
// 这里反转链表没有用哑节点而是原地反转
// 最后恢复了原链表