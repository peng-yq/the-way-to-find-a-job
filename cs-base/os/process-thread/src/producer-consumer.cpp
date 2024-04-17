#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

const int BUFFER_SIZE = 10;  // 缓冲区大小
std::vector<int> buffer;     // 缓冲区

std::mutex mtx;              // 互斥锁
std::condition_variable cv;  // 条件变量
int count = 0;               // 当前缓冲区中的项目数

void producer(int id) {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return count < BUFFER_SIZE; }); // 等待直到缓冲区有空间

        // 生产一个项目（这里简单地使用数字表示）
        int item = rand() % 100;
        buffer.push_back(item);
        count++;
        std::cout << "Producer " << id << " produced " << item << std::endl;

        lock.unlock();
        cv.notify_all(); // 通知消费者有新的产品可以消费

        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // 模拟生产时间
    }
}

void consumer(int id) {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return count > 0; }); // 等待直到缓冲区有产品

        // 消费一个产品
        int item = buffer.back();
        buffer.pop_back();
        count--;
        std::cout << "Consumer " << id << " consumed " << item << std::endl;

        lock.unlock();
        cv.notify_all(); // 通知生产者有空间可以生产

        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // 模拟消费时间
    }
}

int main() {
    std::thread producers[5];
    std::thread consumers[5];

    // 创建生产者和消费者线程
    for (int i = 0; i < 5; i++) {
        producers[i] = std::thread(producer, i);
        consumers[i] = std::thread(consumer, i);
    }

    // 等待所有线程完成
    for (int i = 0; i < 5; i++) {
        producers[i].join();
        consumers[i].join();
    }

    return 0;
}
