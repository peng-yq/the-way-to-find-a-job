// https://leetcode.cn/problems/lian-biao-zhong-dao-shu-di-kge-jie-dian-lcof/description

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
        if (head == nullptr)
            return nullptr;
        ListNode* fast = head, *slow = head;
        while (cnt--) 
            fast = fast->next;
        while (fast != nullptr) {
            fast = fast->next;
            slow = slow->next;
        }
        return slow;
    }
};

// 快慢指针，先让快的走n步，再让快慢一起出发，快的到了末尾即(len-n)，快的也就从头部走了(len-n)步，也就是倒数第n个节点
// 时间复杂度为O(n)，空间复杂度为O(1)