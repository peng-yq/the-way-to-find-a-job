// https://leetcode.cn/problems/ping-heng-er-cha-shu-lcof/description

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
private:
    bool res = true;
    int depth(TreeNode* root) {
        if (root == nullptr)
            return 0;
        int l = depth(root->left), r = depth(root->right);
        if (abs(l - r) > 1) {
            res = false;
            return 0;
        }
        return max(l, r) + 1;
    }
public:
    bool isBalanced(TreeNode* root) {
        if (root == nullptr)
            return true;
        depth(root);
        return res;
    }
};

// 时间复杂度为O(n)，空间复杂度为O(n)