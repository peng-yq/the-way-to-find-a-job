// https://leetcode.cn/problems/reverse-linked-list/description

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
    ListNode* reverseList(ListNode* head) {
        ListNode* tmp;
        ListNode* newhead = new ListNode(0);
        while (head != nullptr) {
            tmp = head->next;
            head->next = newhead->next;
            newhead->next = head;
            head = tmp; 
        }
        return newhead->next;
    }
};

// 头插法，用了一个哑节点，时间复杂度为O(n)，空间复杂度为O(1)
// 下面的双指针一致，但更好一些

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* cur = head, *pre = nullptr;
        while (cur != nullptr) {
            ListNode* nxt = cur->next;
            cur->next = pre;
            pre = cur;
            cur = nxt;
        }
        return pre;
    }
};

// 递归写法，递归的思路是根据上述双指针改的，时间复杂度为O(n)，空间复杂度为O(n) 
class Solution {
private:
    ListNode* recur(ListNode* cur, ListNode* pre) {
        if (cur == nullptr) return pre;
        ListNode* res = recur(cur->next, cur);
        cur->next = pre;
        return res;
    }
public:
    ListNode* reverseList(ListNode* head) {
        return recur(head, nullptr);
    }
};

