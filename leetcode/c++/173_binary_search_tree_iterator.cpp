// https://leetcode.cn/problems/binary-search-tree-iterator

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


class BSTIterator {
private:
    vector<TreeNode*> node; 
public:
    BSTIterator(TreeNode* root) {
        while (root) {
            node.push_back(root);
            root = root->left;
        }
    }
    
    int next() {
        TreeNode* tmp = node.back();
        node.pop_back();
        int res = tmp->val;
        tmp = tmp->right;
        while (tmp) {
            node.push_back(tmp);
            tmp = tmp->left;
        }
        return res;
    }
    
    bool hasNext() {
        return !node.empty();
    }
};