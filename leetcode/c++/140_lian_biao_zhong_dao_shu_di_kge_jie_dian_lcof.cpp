// https://leetcode.cn/problems/lian-biao-zhong-dao-shu-di-kge-jie-dian-lcof

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
    ListNode* trainingPlan(ListNode* head, int cnt) {
        ListNode* dummy = new ListNode(0, head), *slow = dummy, *fast = dummy;
        for (int i = 0; i < cnt; ++i) {
            fast = fast->next;
        }
        while (fast) {
            slow = slow->next;
            fast = fast->next;
        }
        return slow;
    }
};
