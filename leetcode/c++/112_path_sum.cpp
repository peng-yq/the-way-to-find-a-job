// https://leetcode.cn/problems/path-sum

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
    bool hasPathSum(TreeNode* root, int targetSum) {
        bool res = false;
        function<void(TreeNode*, int)> dfs = [&](TreeNode* root, int sum) {
            if (root == nullptr)
                return;
            if (root->left == nullptr && root->right == nullptr && root->val == sum) {
                res = true;
                return;
            }
            dfs(root->left, sum - root->val);
            dfs(root->right, sum - root->val);
        };
        dfs(root, targetSum);
        return res;
    }
};

// O(n), O(n)