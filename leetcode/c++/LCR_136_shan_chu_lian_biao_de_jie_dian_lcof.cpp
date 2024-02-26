// https://leetcode.cn/problems/shan-chu-lian-biao-de-jie-dian-lcof/description

#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* deleteNode(ListNode* head, int val) {
        if (head->val == val)
            return head->next;
        ListNode* pre = head;
        ListNode* node = head->next;
        while (node->val != val && node) {
            pre = pre->next;
            node = node->next;
        }
        if (node->val == val) 
            pre->next = node->next;
        return head;
    }
};

// 时间复杂度为O(n)，空间复杂度为O(1)

// 比较简单，之前还有一道告诉要删除链表节点地址的题，那个需要用O(1)的时间复杂度去解决，即把后面一个节点的值赋值给要删除的节点，再删除后面一个节点