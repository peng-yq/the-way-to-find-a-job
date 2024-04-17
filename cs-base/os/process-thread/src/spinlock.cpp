#include <atomic>
#include <thread>
#include <iostream>

// lock和unlock都是原子操作

class SpinLock {
private:
    std::atomic_flag lock_flag = ATOMIC_FLAG_INIT;
public:
    void lock() {
        // 尝试设置atomic_flag，如果已经被设置，则忙等待
        while (lock_flag.test_and_set(std::memory_order_acquire)) {
            // 自旋等待锁释放
        }
    }

    void unlock() {
        // 清除atomic_flag，释放锁
        lock_flag.clear(std::memory_order_release);
    }
};

// 示例使用自旋锁保护共享数据
int shared_data = 0;
SpinLock spin_lock;

void increment_shared_data(int num_increments) {
    for (int i = 0; i < num_increments; ++i) {
        spin_lock.lock();
        ++shared_data;
        spin_lock.unlock();
    }
}

int main() {
    std::thread t1(increment_shared_data, 10000);
    std::thread t2(increment_shared_data, 10000);

    t1.join();
    t2.join();

    std::cout << "Final value of shared_data: " << shared_data << std::endl;

    return 0;
}
