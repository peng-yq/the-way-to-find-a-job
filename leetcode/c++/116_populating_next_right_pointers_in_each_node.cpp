// https://leetcode.cn/problems/populating-next-right-pointers-in-each-node

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
        function<void(Node*, Node*)> bfs = [&](Node* leftNode, Node* rightNode) {
            if (leftNode == NULL && rightNode == NULL)
                return;
            leftNode->next = rightNode;
            bfs(leftNode->left, leftNode->right);
            bfs(leftNode->right, rightNode->left);
            bfs(rightNode->left, rightNode->right);
        };
        if (root == NULL)
            return NULL;
        bfs(root->left, root->right);
        return root;
    }
};

// O(n), O(n)