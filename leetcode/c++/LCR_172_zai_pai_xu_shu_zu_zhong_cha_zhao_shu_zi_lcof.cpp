// https://leetcode.cn/problems/zai-pai-xu-shu-zu-zhong-cha-zhao-shu-zi-lcof/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countTarget(vector<int>& scores, int target) {
        int res = 0;
        for (int score : scores) {
            if (score > target)
                return res;
            if (score == target)
                res++;
        }
        return res;
    }
    int countTarget(vector<int>& scores, int target) {
        int i = 0, j = scores.size() - 1;
        if (j >= 0 && scores[0] > target)
            return 0;
        while (i <= j) {
            int mid = i + (j - i) / 2;
            if (scores[mid] < target)
                i = mid + 1;
            else if (scores[mid] > target)
                j = mid - 1;
            else {
                if (scores[i] == scores[j])
                    return j - i + 1;
                if (scores[i] < target)
                    i++;
                if (scores[j] > target)
                    j--;
            }
        }
        return 0;
    }
};

// 两种方法，列表查找最好还是用二分，时间复杂度为O(logn)，空间复杂度为O(1)