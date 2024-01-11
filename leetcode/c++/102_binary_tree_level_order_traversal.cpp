// https://leetcode.cn/problems/binary-tree-level-order-traversal/description

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

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode *> tree_queue;
        vector<vector<int>> res;
        if (root != nullptr) tree_queue.push(root);
        while (!tree_queue.empty()) {
            vector<int> tmp;
            for (int i = tree_queue.size(); i > 0; i--) {
                TreeNode* tmp_node = tree_queue.front();
                tree_queue.pop();
                tmp.push_back(tmp_node->val);
                if (tmp_node->left != nullptr) tree_queue.push(tmp_node->left);
                if (tmp_node->right != nullptr) tree_queue.push(tmp_node->right);  
            }
            res.push_back(tmp);
        }
        return res;
    }
};