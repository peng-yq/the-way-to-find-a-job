// https://leetcode.cn/problems/shu-de-zi-jie-gou-lcof/description

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
    bool check(TreeNode* A, TreeNode* B) {
        if (B == NULL)
            return true;
        if (A == NULL || A->val != B->val)
            return false;
        return check(A->left, B->left) && check(A->right, B->right);
    }
    bool isSubStructure(TreeNode* A, TreeNode* B) {
        if (A == NULL || B == NULL)
            return false;
        if (check(A, B))
            return true;
        return isSubStructure(A->left, B) || isSubStructure(A->right, B);
    }
};

// 暴力，依次去判断A的每个节点（判断过程再递归），用递归，也就是先序遍历
// 时间复杂度为O(mn)，空间复杂度为O(m)