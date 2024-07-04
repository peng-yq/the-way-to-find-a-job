// https://leetcode.cn/problems/count-complete-tree-nodes

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
    int countNodes(TreeNode* root) {
        auto getDepth = [&](TreeNode* root, int flag)->int {
            int res = 0;
            while (root) {
                ++res;
                if (flag)
                    root = root->left;
                else 
                    root = root->right;
            }
            return res;
        };
        TreeNode* leftNode = root, *rightNode = root;
        int leftDepth = getDepth(root, 1), rightDepth = getDepth(root, 0);
        if (leftDepth == rightDepth)
            return pow(2, leftDepth) - 1;
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
};