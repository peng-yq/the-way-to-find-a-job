// https://leetcode.cn/problems/reorder-list

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
private:
    ListNode* midList(ListNode* head) {
        ListNode* slow = head, *fast = head;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    ListNode* reverseList(ListNode* head) {
        ListNode* node = new ListNode(0);
        ListNode* tmp;
        while(head != nullptr) {
            tmp = head->next;
            head->next = node->next;
            node->next = head;
            head = tmp;
        }
        ListNode* newHead = node->next;
        delete node;
        return newHead;
    }
public:
    void reorderList(ListNode* head) {
        ListNode* mid = midList(head);
        ListNode* right = reverseList(mid);
        ListNode* tmp = head;
        // 注意下面的判断 
        while (right->next != nullptr) {
            ListNode* tmpLeft = tmp->next;
            ListNode* tmpRight = right->next;
            right->next = tmp->next;
            tmp->next = right;
            tmp = tmpLeft;
            right = tmpRight;
        }
    }
};

// 链表大杂烩，找到中间节点，反转后半部分链表，然后合并链表
// 时间复杂度为O(n)，空间复杂度为O(1)