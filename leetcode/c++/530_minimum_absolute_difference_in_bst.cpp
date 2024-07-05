// https://leetcode.cn/problems/minimum-absolute-difference-in-bst

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
    int getMinimumDifference(TreeNode* root) {
        int res = INT_MAX;
        TreeNode* pre = nullptr;
        function<void(TreeNode*)> dfs = [&](TreeNode* root){
            if (root == nullptr)
                return;
            dfs(root->left);
            if (pre != nullptr)
                res = min(res, abs(root->val - pre->val));
            pre = root;
            dfs(root->right);
        };
        dfs(root);
        return res;
    }
};

// 利用二叉搜索树中序遍历是从小到大排列的特性