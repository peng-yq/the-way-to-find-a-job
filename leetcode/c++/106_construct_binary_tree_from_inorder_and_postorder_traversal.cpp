// https://leetcode.cn/problems/construct-binary-tree-from-inorder-and-postorder-traversal

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
    TreeNode* dfs(vector<int>& postorder, unordered_map<int, int>& index, int i, int l, int r) {
        if (r < l)
            return nullptr;
        int m = index[postorder[i]];
        TreeNode* root = new TreeNode(postorder[i]);
        root->right = dfs(postorder, index, i-1, m+1, r);
        root->left = dfs(postorder, index, i-(r-m)-1, l, m-1);
        return root;
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        unordered_map<int, int>index;
        for (int i = 0; i < inorder.size(); i++) {
            index[inorder[i]] = i;
        }
        TreeNode* root = dfs(postorder, index, postorder.size() - 1, 0, inorder.size() - 1);
        return root;
    }
};

// O(n), O(n)