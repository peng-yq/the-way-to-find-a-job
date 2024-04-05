#include <atomic>
#include <iostream>

struct A {
    float x;
    int y;
    long long z;
};

int main() {
    std::atomic<string> a;
    std::cout << std::boolalpha << a.is_lock_free() << std::endl;
    return 0;
}