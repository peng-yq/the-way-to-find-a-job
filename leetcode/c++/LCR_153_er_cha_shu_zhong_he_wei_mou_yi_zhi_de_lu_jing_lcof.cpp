// https://leetcode.cn/problems/er-cha-shu-zhong-he-wei-mou-yi-zhi-de-lu-jing-lcof/description

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
    void find(TreeNode* root, int target, vector<vector<int>>& res, vector<int>& tmp) {
        if (root == nullptr) 
            return;
        tmp.push_back(root->val);
        if (root->left == nullptr && root->right == nullptr && target == root->val) {
            res.push_back(tmp);
        } else {
            find(root->left, target-root->val, res, tmp);
            find(root->right, target-root->val, res, tmp);
        }
        tmp.pop_back();
    }
    vector<vector<int>> pathTarget(TreeNode* root, int target) {
        vector<vector<int>> res;
        vector<int> tmp;
        if (root == nullptr) 
            return res;
        find(root, target, res, tmp);
        return res;
    }
};

// 时间复杂度为O(n), 空间复杂度为O(n)