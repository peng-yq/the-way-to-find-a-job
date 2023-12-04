#include <bits/stdc++.h>
using namespace std;

class Item {
    public:
        int w;
        int v;
    Item(int w, int v) : w(w), v(v) {
    }
};

double fractionalKnapsack(vector<int> &wgt, vector<int> &val, int cap) {
    vector<Item> items;
    for (int i = 0; i < wgt.size(); i++) {
        items.push_back(Item(wgt[i], val[i]));
    }

    sort(items.begin(), items.end(), [](Item &a, Item &b) {return (double)a.v/a.w > (double)b.v/b.w;});
    double res = 0;
    for(auto item : items) {
        if (item.w <= cap) {
            res += item.v;
            cap -= item.w;
        }else {
            res += (double)item.v / item.w * cap;
            break;
        }
    }
    return res;
}