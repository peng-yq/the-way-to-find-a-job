// https://leetcode.cn/problems/er-cha-shu-de-jing-xiang-lcof/description

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    void reverse(TreeNode* root) {
        if (root == NULL)
            return;
        TreeNode* node = root->left;
        root->left = root->right;
        root->right = node;
        reverse(root->left);
        reverse(root->right);
    }
    TreeNode* mirrorTree(TreeNode* root) {
        reverse(root);
        return root;
    }
};

// 时间复杂度O(n)，空间复杂度O(n)