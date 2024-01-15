// https://leetcode.cn/problems/path-sum-ii/description

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
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        recur(root, targetSum);
        return res;
    }
private:
    vector<vector<int>> res;
    vector<int> path;
    void recur(TreeNode* root, int targetSum) {
        if (root == nullptr) return;
        path.push_back(root->val);
        targetSum -= root->val;
        if (targetSum == 0 && root->left == nullptr && root->right == nullptr)
            res.push_back(path);
        recur(root->left, targetSum);
        recur(root->right, targetSum);
        path.pop_back();
    }
};

// 时间复杂度和空间复杂度都为O(n)