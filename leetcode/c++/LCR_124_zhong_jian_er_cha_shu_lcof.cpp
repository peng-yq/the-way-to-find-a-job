// https://leetcode.cn/problems/zhong-jian-er-cha-shu-lcof

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
    TreeNode* dfs(vector<int>& preorder, unordered_map<int, int>& index, int i, int l, int r) {
        if (r < l)
            return nullptr;
        TreeNode* root = new TreeNode(preorder[i]);
        int m = index[preorder[i]];
        root->left = dfs(preorder, index, i+1, l, m-1);
        root->right = dfs(preorder, index, i+m-l+1, m+1, r);
        return root;
    }
    TreeNode* deduceTree(vector<int>& preorder, vector<int>& inorder) {
        unordered_map<int, int> index;
        for (int i = 0; i < inorder.size(); i++) 
            index[inorder[i]] = i;
        TreeNode* root = dfs(preorder, index, 0, 0, inorder.size()-1);
        return root;
    }
};

// 时间复杂度和空间复杂度为O(n)