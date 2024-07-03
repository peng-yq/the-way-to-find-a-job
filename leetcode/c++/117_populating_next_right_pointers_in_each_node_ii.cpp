// https://leetcode.cn/problems/populating-next-right-pointers-in-each-node-ii

#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution {
public:
    Node* connect(Node* root) {
        if (root == NULL)
            return NULL;
        vector<Node*> q = {root};
        while (!q.empty()) {
            vector<Node*> nxt;
            for (int i = 0; i < q.size(); ++i) {
                 Node* tmp = q[i];
                if (i)
                    q[i-1]->next = tmp;
                if (tmp->left)
                    nxt.push_back(tmp->left);
                if (tmp->right)
                    nxt.push_back(tmp->right);
            }
            q = move(nxt);   
        }
        return root;
    }
};

// O(n), O(n)