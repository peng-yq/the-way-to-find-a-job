// https://leetcode.cn/problems/sum-root-to-leaf-numbers

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
    int sumNumbers(TreeNode* root) {
        int res = 0;
        function<void(TreeNode*, int)> dfs = [&](TreeNode* root, int pre) {
            if (root == nullptr)
                return;
            if (root->left == nullptr && root->right == nullptr) {
                res += pre * 10 + root->val;
                return;
            }
            dfs(root->left, pre * 10 + root->val);
            dfs(root->right, pre * 10 + root->val);
        };
        dfs(root, 0);
        return res;
    }
};