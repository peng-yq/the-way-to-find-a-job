// https://leetcode.cn/problems/intersection-of-two-linked-lists/description

#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *tmpA = headA, *tmpB = headB;
        while (tmpA != tmpB) {
            if (tmpA != NULL)
                tmpA = tmpA->next;
            else 
                tmpA = headB;
            if (tmpB != NULL)
                tmpB = tmpB->next;
            else 
                tmpB = headA;
        }
        return tmpA;
    }
};

// 时间复杂度为O(n+m)，空间复杂度为O(1)
// 还得是k神