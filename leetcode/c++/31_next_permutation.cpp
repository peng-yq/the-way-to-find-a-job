// https://leetcode.cn/problems/next-permutation

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        if (nums.size() == 1)
            return;
        for (int i = nums.size() - 1; i >= 1; --i) {
            if (nums[i] > nums[i-1]) {
                for (int j = nums.size() - 1; j >= i; --j) {
                    if (nums[j] > nums[i-1]) {
                        swap(nums[j], nums[i-1]);
                        reverse(nums.begin() + i, nums.end());
                        return;
                    }
                }
            }
        }
        reverse(nums.begin(), nums.end());
    }
};

// 题目翻译的很拉，白话来说就是给你一个数组，这个数组的每个元素从左到右组成了一个数字，比如{1, 2, 4, 5}组成了1245
// 我们需要找出这个数组元素的排列中下一个比它大的排列，并且只能原地排序和空间复杂度为常数，
// 例子中的{1, 2, 4, 5}下一个排列为{1, 2, 5, 4}，因为1254是大于1245冰最接近1245的排列。
// 这题其实是规律题，因为是求最接近的一个比原数组排列大的排列，因此我们从后往前找，当找到降序时（从右向左，nums[i] > nums[i-1])
// 做好标记，并且从[i, end]（这部分从左到右为降序，因此我们也是从后往前找）中找到第一个大于nums[i-1]的元素nums[j]
// 将nums[j]和nums[i-1]进行交换，此外我们还需要保证[i, end]从走到右是升序的，这样才是最接近原排列的。由于[i, end]为降序，我们只需让其升序即可
// 如果在循环中都没找到（从左到右全部是降序的，也就是最大的那个排列了，我们需要返回最小的排列），在最后直接进行reverse即可
// 时间复杂度为O(n)，注意是O(n)不是O(n^2)，因为是顺序执行的，空间复杂度为O(1)