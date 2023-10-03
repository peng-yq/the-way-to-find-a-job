// https://leetcode.cn/problems/add-two-numbers/

#include <bits/stdc++.h>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 主要考察了链表的插入构造，注意最后一位进位
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *head = nullptr, *tail = nullptr;
        int pre = 0;
        while(l1 || l2){
            int left = l1 ? l1->val : 0;
            int right = l2 ? l2->val : 0;
            int sum = left + right + pre;
            if(!head){
                head = tail = new ListNode(sum % 10);
            }else{
                tail->next = new ListNode(sum % 10);
                tail = tail->next;
            }
            pre = sum / 10;
            if(l1)
                l1 = l1-> next;
            if(l2)
                l2 = l2->next;
        }
        if(pre > 0){
            tail->next = new ListNode(pre);
        }
        return head;
    }
};