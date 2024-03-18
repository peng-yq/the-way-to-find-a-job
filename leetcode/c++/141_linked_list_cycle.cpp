// https://leetcode.cn/problems/linked-list-cycle

#include <bits/stdc++.h>
using namespace std;

struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode* node1 = head, *node2 = head;
        while (node2 && node2->next) {
            node2 = node2->next->next;
            node1 = node1->next;
            if (node1 == node2)
                return true;
        }
        return false;
    }
};

// O(n), O(1)