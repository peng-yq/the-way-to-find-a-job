// https://leetcode.cn/problems/er-cha-sou-suo-shu-yu-shuang-xiang-lian-biao-lcof/description

#include <bits/stdc++.h>
using  namespace std;

class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};

class Solution {
private:
    vector<Node*> data;
    void dfs(Node* root) {
        if (root == NULL)
            return;
        dfs(root->left);
        data.push_back(root);
        dfs(root->right);
    }
public:
    Node* treeToDoublyList(Node* root) {
        if (root == NULL)
            return NULL;
        dfs(root);
        for (int i = 0; i < data.size(); i++) {
            data[i]->right = data[(i+1) % data.size()];
            data[i]->left = data[(i-1+data.size()) % data.size()];
        }
        return data[0];
    }
};

// 非原地排序版本

// 下面是原地排序版本

class Solution {
private:
    Node* head, *pre;
    void dfs(Node* root) {
        if (root == NULL)
            return;
        dfs(root->left);
        if (pre == NULL) head = root;
        else pre->right = root;
        root->left = pre;
        pre = root;
        dfs(root->right);
    }
public:
    Node* treeToDoublyList(Node* root) {
        if (root == NULL)
            return NULL;
        dfs(root);
        pre->right = head;
        head->left = pre;
        return head; 
    }
};

// 时间复杂度和空间复杂度均为O(n)