// https://leetcode.cn/problems/liang-ge-lian-biao-de-di-yi-ge-gong-gong-jie-dian-lcof

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
        ListNode* tmp1 = headA, *tmp2 = headB;
        while (tmp1 != tmp2) {
            if (tmp1 != NULL)
                tmp1 = tmp1->next;
            else 
                tmp1 = headB;
            if (tmp2 != NULL) 
                tmp2 = tmp2->next;
            else 
                tmp2 = headA;
        }
        return tmp1;
    }
};

// 时间复杂度为O(n+m)，空间复杂度为O(1)

// a+(b-c) = b+(a-c)，a, b分别为两个链表的长度，c为相交的点到结尾的长度（如果不相交则为0）