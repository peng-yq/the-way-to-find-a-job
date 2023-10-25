#include <bits/stdc++.h>
using namespace std;

void bucketSort(vector<float> &nums) {
    int k = nums.size() / 2;
    vector<vector<float>>buckets(k);
    for(float num : nums){
        int i = num * k;
        buckets[i].push_back(num);
    }
    for(vector<float> &bucket : buckets)
        sort(bucket.begin(), bucket.end());
    int i = 0;
    for(vector<float> &bucket : buckets) {
         for(float num : bucket){
            nums[i++] = num;
        }
    }      
}