// https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-search-tree/description

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        while (root != NULL) {
            if (root->val < p->val && root ->val < q->val) root = root->right;
            else if (root->val > p->val && root->val > q->val) root = root->left;
            else break;
        }
        return root;
    }
};


// 迭代的时间复杂度为O(N)（最差，最小为O(logN)），空间复杂度为O(1)
// 如果用递归的话同上，空间复杂度为O(N)（最差）