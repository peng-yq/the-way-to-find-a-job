#include <vector>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    for (int i = 1; i < v.size(); i += 2) {
        v[i/2] = std::move(v[i]);
    }
    v.resize(v.size() / 2);
    v.shrink_to_fit()
}