// https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/description

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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
            if (root == NULL || root == p || root == q) return root;
            TreeNode* left = lowestCommonAncestor(root->left, p, q);
            TreeNode* right = lowestCommonAncestor(root->right, p, q);
            if (left == NULL && right == NULL) return NULL;
            if (left == NULL) return right;
            if (right == NULL) return left;
            return root;
        }
};

// 时间复杂度最差为O(n)，空间复杂度最差为O(n)