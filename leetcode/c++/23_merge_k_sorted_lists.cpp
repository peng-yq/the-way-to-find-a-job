// https://leetcode.cn/problems/merge-k-sorted-lists

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
private:
    ListNode* merge(ListNode* headA, ListNode* headB) {
        ListNode* dummy = new ListNode(0);
        ListNode* tmp = dummy;
        while (headA != nullptr && headB != nullptr) {
            if (headA->val < headB->val) {
                tmp->next = headA;
                headA = headA->next;
            } else {
                tmp->next = headB;
                headB = headB->next;
            }
            tmp = tmp->next;
        }
        tmp->next = headA != nullptr? headA : headB;
        ListNode* res = dummy->next;
        delete dummy;
        return res;
    }
    ListNode* mergeLists(vector<ListNode*>& lists, int i, int j ) {
        if (i > j)
            return nullptr;
        if (i == j)
            return lists[i];
        int mid = i + (j - i) / 2;
        ListNode* left = mergeLists(lists, i, mid);
        ListNode* right = mergeLists(lists, mid + 1, j);
        return merge(left, right);
    }
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;
        return mergeLists(lists, 0, lists.size()-1);
    }
};

// 这道题单纯对于通过而言还是很简单的，只要你会合并2个链表，但是时间复杂度比较高，n为单个链表的平均长度，时间复杂度为O(lognk^2)，空间复杂度为O(1)
// 时间复杂度是第一次合并是n个节点，第二次是2n，一直到kn，(n+kn)*k/2
// 优化可以考虑使用归并的思想来两两合并，这样时间复杂度会变成O(nklogk)，空间复杂度为O(logk)，主要是递归的消耗
// 归并再优化的话就是用多线程，这里只为left的递归开了个线程去执行，而不是left和right同时开，同时开还得考虑同步和互斥的问题
// 另外线程的创建也是需要一定资源的，同时操作系统对同时允许的线程数量也是有限制的，即使只为left开线程最后一个测试用例就已经报系统资源不足了
// 解决办法是通过线程池，设置异常处理函数使得资源不足时使用单线程执行，或者只有在列表数量超过某个阈值时才使用多线程
// 下面的解决办法是第3种

class Solution {
private:
    ListNode* merge(ListNode* headA, ListNode* headB) {
        ListNode* dummy = new ListNode(0);
        ListNode* tmp = dummy;
        while (headA != nullptr && headB != nullptr) {
            if (headA->val < headB->val) {
                tmp->next = headA;
                headA = headA->next;
            } else {
                tmp->next = headB;
                headB = headB->next;
            }
            tmp = tmp->next;
        }
        tmp->next = headA != nullptr? headA : headB;
        ListNode* res = dummy->next;
        delete dummy;
        return res;
    }
     ListNode* mergeLists(vector<ListNode*>& lists, int i, int j, bool use_threads) {
        if (i > j)
            return nullptr;
        if (i == j)
            return lists[i];        
        int mid = i + (j - i) / 2;
        ListNode* left = nullptr;
        ListNode* right = nullptr;
        if (use_threads && (j - i + 1) > 4) {  
            thread left_thread([&]() { left = mergeLists(lists, i, mid, false); });
            right = mergeLists(lists, mid + 1, j, false);
            left_thread.join();
        } else {
            left = mergeLists(lists, i, mid, false);
            right = mergeLists(lists, mid + 1, j, false);
        }
        return merge(left, right);
    }

public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;
        cout << lists.size();
        return mergeLists(lists, 0, lists.size()-1, true);
    }
};

// 还有一种解决办法是使用最小堆，先遍历数组，把所有链表的头节点推入堆中，再依次出堆，如果出堆的节点还有后续节点，再将其推入堆中
// 时间复杂度为O(nklogk)，操作堆的时间复杂度为O(logk)，空间复杂度为O(k)

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        auto cmp = [](ListNode* a, ListNode* b) {
            return a->val > b->val;
        };
        priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq;
        for (auto list : lists) {
            if (list)
                pq.push(list);
        }
        ListNode* dummy = new ListNode();
        ListNode* tmp = dummy;
        while (!pq.empty()) {
            ListNode* node = pq.top();
            pq.pop();
            if (node->next)
                pq.push(node->next);
            tmp->next = node;
            tmp = tmp->next;
        }
        return dummy->next;
    }
};