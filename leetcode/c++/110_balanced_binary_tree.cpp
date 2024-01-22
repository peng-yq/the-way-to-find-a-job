// https://leetcode.cn/problems/balanced-binary-tree

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
    bool isBalanced(TreeNode* root) {
        return recur(root) != -1;
    }
private:
    int recur(TreeNode* root) {
        if (root == nullptr)
            return 0;
        int left = recur(root->left);
        if (left == -1)
            return -1;
        int right = recur(root->right);
        if (right == -1)
            return -1;
        return abs(left - right) <= 1 ? max(left, right) + 1 : -1;
    }
};

// 时间复杂度为O(n)，空间复杂度为O(n)