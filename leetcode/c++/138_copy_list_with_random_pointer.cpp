// https://leetcode.cn/problems/copy-list-with-random-pointer/description

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        unordered_map<Node*, Node*> hashArray;
        Node* newHead1 = head;
        Node* newHead2 = head;
        while (newHead1 != NULL) {
            hashArray[newHead1] = new Node(newHead1->val);
            newHead1 = newHead1->next;
        }
        while (newHead2 != NULL) {
            hashArray[newHead2]->next = hashArray[newHead2->next];
            hashArray[newHead2]->random = hashArray[newHead2->random];
            newHead2 = newHead2->next;
        }
        return hashArray[head];
    }
};

// 时间复杂度和空间复杂度均为O(n)