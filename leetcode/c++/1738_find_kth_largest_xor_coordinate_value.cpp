// https://leetcode.cn/problems/find-kth-largest-xor-coordinate-value

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int kthLargestValue(vector<vector<int>>& matrix, int k) {
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> res(m + 1, vector<int>(n + 1, 0));
        vector<int>nums;
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                res[i][j] = res[i][j - 1] ^ res[i - 1][j] ^ res[i - 1][j - 1] ^ matrix[i - 1][j - 1];
                nums.push_back(res[i][j]);
            }
        }
        nth_element(nums.begin(), nums.begin() + k - 1, nums.end(), greater<int>());
        return nums[k - 1];
    }
};

// 模板题，二维前缀和
// 避免边界，使用m+1*n+1大小的矩阵，并且初始化为0，因为0异或任何元素都是其本身
// a ^ b = c, a = b ^ c
// 找topk，就有很多种解法了，直接使用库函数nth_element，其时间复杂度为O(k)，只会将第k大的元素（索引为k-1）排列到正确位置
// 也可以sort，也可以使用k大小的小顶堆（这个很慢，会进行m*n次堆操作即m*n*logk）
// 总体时间复杂度为O(m*n)，空间复杂度为O(m*n)