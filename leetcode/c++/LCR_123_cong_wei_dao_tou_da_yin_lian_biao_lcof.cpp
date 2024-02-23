// https://leetcode.cn/problems/cong-wei-dao-tou-da-yin-lian-biao-lcof/description

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
    vector<int> reverseBookList(ListNode* head) {
        ListNode* tmp = new ListNode();
        vector<int> res;
        while (head) {
            ListNode* node = head->next;
            head->next = tmp->next;
            tmp->next = head;
            head = node;
        }
        tmp = tmp->next;
        while (tmp) {
            res.push_back(tmp->val);
            tmp = tmp->next;
        }
        return res;
    }
};

// 时间复杂度为O(n)，空间复杂度为O(n)
// 也可以用stack