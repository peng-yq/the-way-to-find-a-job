// https://leetcode.cn/problems/sort-list

#include <bits/stdc++.h>
using namespace std;

// 递归版本，时间复杂度为O(nlogn)，空间复杂度为O(logn)

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:   
    ListNode* sortList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;
        ListNode* slow = head, *fast = head;
        while (fast->next != nullptr && fast->next->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode* tmp = slow->next;
        slow->next = nullptr;
        ListNode* left = sortList(head);
        ListNode* right = sortList(tmp);
        ListNode* dummy = new ListNode(0);
        ListNode* res = dummy;
        while (left != nullptr && right != nullptr) {
            if (left->val <= right->val) {
                dummy->next = left;
                dummy = left;
                left = left->next;
            } else {
                dummy->next = right;
                dummy = right;
                right = right->next;
            }
        }
        dummy->next = left == nullptr? right : left;
        return res->next;
    }
};

// 迭代版本，时间复杂度没变，空间复杂度变为了O(1)，挺难写的

class Solution {
public:
    ListNode* cutList(ListNode* head, int n) {
        while (--n && head != nullptr)
            head = head->next;
        if (head == nullptr)
            return nullptr;
        ListNode* res = head->next;
        head->next = nullptr;
        return res;
    }
    ListNode* mergeList(ListNode* left, ListNode* right) {
        ListNode* dummy = new ListNode(0);
        ListNode* res = dummy;
        while (left != nullptr && right != nullptr) {
            if (left->val <= right->val) {
                dummy->next = left;
                dummy = left;
                left = left->next;
            } else {
                dummy->next = right;
                dummy = right;
                right = right->next;
            }
        }
        dummy->next = left == nullptr? right : left;
        ListNode* head = res->next;
        delete res;
        return head;
    }
    ListNode* sortList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;
        ListNode* dummy = new ListNode(0, head);
        ListNode* tmp = head;
        int length = 0;
        while (tmp != nullptr) {
            tmp = tmp->next;
            length++;
        }
        for (int i = 1; i < length; i <<= 1) {
            ListNode* cur = dummy->next;
            ListNode* tail = dummy;
            while (cur != nullptr) {
                ListNode* left = cur;
                ListNode* right = cutList(left, i);
                cur = cutList(right, i);
                tail->next = mergeList(left, right);
                while (tail->next)
                    tail = tail->next;
            }
        }
        ListNode* res = dummy->next;
        delete dummy;
        return res; 
    }
};