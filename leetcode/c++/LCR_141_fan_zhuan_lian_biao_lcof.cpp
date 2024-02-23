// https://leetcode.cn/problems/fan-zhuan-lian-biao-lcof/description

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
    ListNode* trainningPlan(ListNode* head) {
        ListNode* tmp = new ListNode();
        ListNode* node = head;
        while (head) {
            node = head->next;
            head->next = tmp->next;
            tmp->next = head;
            head = node;
        }
        return tmp->next;
    }
};

// 时间复杂度为O(n)，空间复杂度为O(1)