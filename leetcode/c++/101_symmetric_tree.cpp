// https://leetcode.cn/problems/symmetric-tree/description

#include<bits/stdc++.h>
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
    bool isSymmetric(TreeNode* root) {
        return root == nullptr || dfs(root->left, root->right);
    }
private:
    vector<int> node;
    bool dfs(TreeNode* left, TreeNode* right) {
        if (left == nullptr && right == nullptr)
            return true;
        if (left == nullptr || right == nullptr || left->val != right->val)
            return false;
        return dfs(left->left, right->right) && dfs(left->right, right->left);
    }
};

// 时间复杂度为O(n)，空间复杂度最差为O(n)