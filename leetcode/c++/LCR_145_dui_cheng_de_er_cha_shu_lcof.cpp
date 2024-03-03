// https://leetcode.cn/problems/dui-cheng-de-er-cha-shu-lcof/description

#include <bits/stdc++.h>
using  namespace std;

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
    bool check(TreeNode* a, TreeNode* b) {
        if (a == nullptr && b == nullptr)
            return true;
        if (a == nullptr || b == nullptr || a->val != b->val)
            return false;
        return check(a->left, b->right) && check(a->right, b->left);
    }
    bool checkSymmetricTree(TreeNode* root) {
        if (root == nullptr)
            return true;
        return check(root->left, root->right);
    }
};

// 时间复杂度为O(n)，空间复杂度为O(n)