// 

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
    ListNode* middleNode(ListNode* head) {
        ListNode* tmp = head;
        int length = 0;
        while (tmp != nullptr) {
            tmp = tmp->next;
            length++;
        }
        ListNode* tmp1 = head;
        if (length % 2 == 0) {
            int mid = length / 2;
            while (mid--) 
                tmp1 = tmp1->next;
        } else {
            int mid = (length - 1) / 2;
            while (mid--)
                tmp1 = tmp1->next; 
        }
        return tmp1;
    }
};

// 时间复杂度为O(n)，空间复杂度为O(1)，但其实是笨办法

class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode* slow = head, * fast = head;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
};

// 事实证明fast 比 fast != nullptr更慢