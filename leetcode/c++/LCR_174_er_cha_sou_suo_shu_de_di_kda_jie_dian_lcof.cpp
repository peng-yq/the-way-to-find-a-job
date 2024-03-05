// https://leetcode.cn/problems/er-cha-sou-suo-shu-de-di-kda-jie-dian-lcof/description

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
    int res;
    void dfs(TreeNode* root, int& cnt) {
        if (root == nullptr || cnt == 0)
            return;
        dfs(root->right, cnt);
        if (--cnt == 0) {
            res = root->val;
            return;
        }
        dfs(root->left, cnt);
    }
public:
    int findTargetNode(TreeNode* root, int cnt) {
        dfs(root, cnt);
        return res;
    }
};

// 时间复杂度为O(n)，空间复杂度为O(n)