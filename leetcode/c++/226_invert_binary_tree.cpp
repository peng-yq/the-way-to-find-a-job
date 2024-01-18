// https://leetcode.cn/problems/invert-binary-tree/description

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
    TreeNode* invertTree(TreeNode* root) {
        dfs(root);
        return root;
    }
private:
    void dfs(TreeNode* root) {
        if (root == nullptr) 
            return;
        TreeNode* tmp;
        tmp = root->right;
        root->right = root->left;
        root->left = tmp;
        dfs(root->left);
        dfs(root->right);
    }
};

// 时间复杂度为O(n)，空间复杂度最好为O(logn)，最坏为O(n)