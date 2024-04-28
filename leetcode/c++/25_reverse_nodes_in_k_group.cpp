// https://leetcode.cn/problems/reverse-nodes-in-k-group

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
    ListNode* reverseKGroup(ListNode* head, int k) {
        int n = 0;
        ListNode* dummy = new ListNode(0, head);
        ListNode* cur = head, *pre = nullptr, *preHead = dummy;
        for (ListNode* tmp = head; tmp != nullptr; tmp = tmp->next)
            ++n;
        for (; n >= k; n -= k) {
            for (int i = 0; i < k; ++i) {
                ListNode* nxt = cur->next;
                cur->next = pre;
                pre = cur;
                cur = nxt;
            }
            ListNode* tail = preHead->next;
            tail->next = cur;
            preHead->next = pre;
            preHead = tail;
        }
        ListNode* res = dummy->next;
        delete dummy;
        return res;
    }
};

// 迭代解法，时间复杂度为O(n)，空间复杂度为O(1)
// 首先先计算链表的长度，这样我们才能知道迭代的次数也就是n/k
// 因为是k个一组反转，因此我们需要一个哑节点dummy，最后直接返回dummy->next即可
// 进行n/k次迭代，每次迭代对里面的k个链表进行反转，这里用双指针进行，反转链表的常规解法
// 每组反转后，此时pre是这组的第一个节点，cur变成了下一组的第一个节点
// 首先我们需要让当前组的最后一个节点指向下一组的第一个节点也就是cur
// 此外，由于头节点变化了，因此我们需要让上一组的最后一个节点指向当前组的头节点也就是pre
// 根据上述分析，我们需要preHead保存每轮迭代上一组的最后一个节点，并将其指向当前组的第一个节点
// 这样在每轮反转后，preHead->next变成了当前组的最后一个节点

// 递归版本，更加清晰

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* tmp = head;
        for (int i = 0; i < k; ++i) {
            if (tmp == nullptr) return head;
            tmp = tmp->next;
        }
        ListNode* cur = head, *pre = nullptr;
        for (int i = 0; i < k; ++i) {
            ListNode* nxt = cur->next;
            cur->next = pre;
            pre = cur;
            cur = nxt;
        }
        head->next = reverseKGroup(cur, k);
        return pre;
    }
};