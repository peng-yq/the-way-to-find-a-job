// https://leetcode.cn/problems/remove-nth-node-from-end-of-list

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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode(0, head);
        // 边界情况
        ListNode* slow = dummy, *fast = dummy;
        while (n--) 
            fast = fast->next;
        while (fast->next != nullptr) {
            fast = fast->next;
            slow = slow->next;
        }
        slow->next = slow->next->next;
        ListNode* res = dummy->next;
        delete dummy;
        return res;
    }
};

// 快慢指针，快的先走n步，再让慢的和快的一起走，快的走到最后一个节点了，慢的也就处于倒数第n个节点了
// 一次遍历，O(n), O(1)