// https://leetcode.cn/problems/find-elements-in-a-contaminated-binary-tree

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

class FindElements {
private:
    TreeNode* root;
    unordered_set<int> s;
    void dfs(TreeNode* root, int val) {
        if (root == nullptr)
            return;
        root->val = val;
        s.insert(val);
        dfs(root->left, val*2+1);
        dfs(root->right, val*2+2);
    }
public:
    FindElements(TreeNode* root) {
        this->root = root;
        dfs(root, 0);
    }
    
    bool find(int target) {
        return s.find(target) != s.end();
        // c++20的写法：return s.contains(target);
    }   
};

// 查找直接通过哈希表使得时间复杂度为O(1)，复习了类