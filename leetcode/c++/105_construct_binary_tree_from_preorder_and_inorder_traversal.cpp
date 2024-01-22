// https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/description

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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        unordered_map<int, int> map;
        for (int i = 0; i < inorder.size(); i++)
            map[inorder[i]] = i;
        TreeNode* root = dfs(preorder, map, 0, 0, inorder.size() - 1);
        return root;
    }
private:
    TreeNode* dfs(vector<int>& preorder, unordered_map<int, int>& map, int i, int l, int r) {
        if (r < l)
            return nullptr;
        TreeNode* root = new TreeNode(preorder[i]);
        int m = map[preorder[i]];
        root->left = dfs(preorder, map, i + 1, l, m-1);
        root->right = dfs(preorder, map, i + m - l + 1, m + 1, r);
        return root;
    }
};

// 时间复杂度和空间复杂度为O(n)