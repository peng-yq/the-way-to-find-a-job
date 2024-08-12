// https://leetcode.cn/problems/binary-tree-postorder-traversal/

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
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> stk;
        if (root)
            stk.push(root);
        while (!stk.empty()) {
            TreeNode* tmp = stk.top();
            stk.pop();
            res.push_back(tmp->val);
            if (tmp->left)
                stk.push(tmp->left);
            if (tmp->right)
                stk.push(tmp->right);
        }
        reverse(res.begin(), res.end());
        return res;
    }
};