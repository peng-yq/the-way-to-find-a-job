// https://leetcode.cn/problems/diameter-of-binary-tree

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
    int lenOfBinaryTree(TreeNode* root, int& res) {
        if (root == nullptr)
            return 0;
        int left = lenOfBinaryTree(root->left, res);
        int right = lenOfBinaryTree(root->right, res); 
        res = max(res, left+right);
        return max(left, right) + 1;
    }
    int diameterOfBinaryTree(TreeNode* root) {
        int res = 0;
        lenOfBinaryTree(root, res);
        return res;
    }
};

// 只需要注意这条路径可能经过也可能不经过根节点 root 即可ac，然后就是记忆化搜索