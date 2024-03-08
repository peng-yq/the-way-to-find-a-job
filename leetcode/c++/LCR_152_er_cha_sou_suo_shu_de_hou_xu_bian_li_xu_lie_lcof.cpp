// https://leetcode.cn/problems/er-cha-sou-suo-shu-de-hou-xu-bian-li-xu-lie-lcof

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool dfs(vector<int>& postorder, int i, int j) {
        if (j < i) 
            return true;
        int m = 0;
        while(postorder[m] < postorder[j])
            m++;
        int k = m;
        while(m < j && postorder[m] > postorder[j])
            m++;
        return m == j && dfs(postorder, i, k-1) && dfs(postorder, k, j-1);
    }
    bool verifyTreeOrder(vector<int>& postorder) {
        return dfs(postorder, 0, postorder.size() - 1);
    }
};

// 递归的做法，先遍历找出第一个大于根节点的值，则这个值左边的范围为左子树（遍历过程中已经保证了左子树的所有节点都小于根节点），右边到根节点的范围为右子树
// 接着再遍历右子树检查是否均大于根节点的值，然后再对左右子树进行递归
// 时间复杂度为O(n^2)，空间复杂度为O(n)

// 单调栈的做法，后序遍历的颠倒为根节点|右子树|左子树，使用单调栈入栈递增的节点即为右子树部分，遇到第一个递减的节点表示进入了左子树部分
//（可能是根节点右子树的左子树），出栈所有大于此节点值的节点，最后一个出栈的则为其根节点，继续此过程，如果遇到节点值大于当前根节点的值则返回false
// 因为左子树节点值均小于根节点，初始我们可以让根节点为max，表示此二叉搜索树为max的左子树
// 时间复杂度为O(n)，空间复杂度为O(n)

class Solution {
public:
    bool verifyTreeOrder(vector<int>& postorder) {
        int root = INT_MAX;
        stack<int> stk;
        for (int i = postorder.size() - 1; i >= 0; i--) {
            if (postorder[i] > root)
                return false;
            while (!stk.empty() && stk.top() > postorder[i]) {
                root = stk.top();
                stk.pop();
            }
            stk.push(postorder[i]);
        }
        return true;
    }
};
 