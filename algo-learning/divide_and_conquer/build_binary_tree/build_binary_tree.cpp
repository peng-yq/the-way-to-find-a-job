#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;          
    TreeNode *left;   
    TreeNode *right;  
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode *dfs(vector<int> &preorder, unordered_map<int, int> &inorderMap, int i, int l, int r) {
    if(r < l)
        return NULL;
    TreeNode *root = new TreeNode(preorder[i]);
    int m = inorderMap[preorder[i]];
    root->left = dfs(preorder, inorderMap, i+1, l, m-1);
    root->right = dfs(preorder, inorderMap, i+1+(m-l), m+1, r);
    return root;
}

TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
    unordered_map<int, int>inorderMap;
    for(int i = 0; i < inorder.size(); i++){
        inorderMap[inorder[i]] = i;
    }
    TreeNode *root = dfs(preorder, inorderMap, 0, 0, inorder.size()-1);
    return root;
}