// https://leetcode.cn/problems/binary-tree-maximum-path-sum

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
private:
    int maxSum(TreeNode* root, int& res) {
        if (root == nullptr)
            return 0;
        int leftVal = max(maxSum(root->left, res), 0);
        int rightVal = max(maxSum(root->right, res), 0);
        int sum = leftVal + rightVal + root->val;
        res = max(sum, res);
        return max(leftVal, rightVal) + root->val;
    }
public:
    int maxPathSum(TreeNode* root) {
        int res = INT_MIN;
        maxSum(root, res);
        return res;
    }
};

// 某个节点的最大路径有3种情况，
// 【当前节点的值 + 左子树的最大路径和 + 右子树的最大路径和】，【当前节点值】， 【当前节点值 + max(左子树的最大路径和, 右子树的最大路径和)】
// 取3种情况的最大值，分别对应，左右子树中的路径和当前节点构成路径，左右子树中的最大值和当前节点构成路径（左右子树中一个可能为负），当前节点
// 其中左右子树最大路径有2种情况：
// 【左右节点值 + max(其左子树的最大路径，其右子树的最大路径)】，【当前节点值】
// 因为路径不能出现分叉
// 最大路径可能不经过根节点，因此递归更新最大路径和即可
/*
    // 保证正数，减少判断
    int leftVal = max(maxSum(root->left, res), 0);
    int rightVal = max(maxSum(root->right, res), 0);
    int sum = leftVal + rightVal + root->val;
    res = max(sum, res);
    return max(leftVal, rightVal) + root->val;
*/
// 时间复杂度为O(n)，空间复杂度为O(n)

