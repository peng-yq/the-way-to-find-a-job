// https://leetcode.cn/problems/insert-delete-getrandom-o1

#include <bits/stdc++.h>
using namespace std;

class RandomizedSet {
private:
    unordered_map<int, int> s;
    vector<int> nums;
public:
    RandomizedSet() {
        srand((unsigned)time(NULL));
    }
    
    bool insert(int val) {
        if (s.count(val))
            return false;
        else { 
            nums.push_back(val);
            s[val] = nums.size() - 1;
            return true;
        }
    }
    
    bool remove(int val) {
        if (s.count(val)) {
            s[nums[nums.size() - 1]] = s[val];
            swap(nums[s[val]], nums[nums.size() - 1]);
            nums.pop_back();
            s.erase(val);
            return true;
        } 
        return false;
    }
    
    int getRandom() {
        int randomIndex = rand() % nums.size();
        return nums[randomIndex];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */

// O(1)判断元素是否存在是有很多容器的，比如set和哈希表，但是最后要返回随机一个元素，因此需要使用动态数组，这样才能O(1)
// 如何进行动态数组的增删呢，需要使用哈希表记录元素的位置，每次在数组最后进行操作。