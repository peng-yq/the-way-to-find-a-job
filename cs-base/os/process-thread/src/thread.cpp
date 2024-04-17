#include <iostream>
#include <thread>

int num = 0;

void addOne() {
    for (int i = 0; i < 1000; ++i)
        num += 1;
}

int main() {
    std::cout << "Start 2 threads" << std::endl;
    
    std::thread th1(addOne);
    std::thread th2(addOne);

    th1.join();
    th2.join();

    std::cout << "2 threads end" << std::endl;
    std::cout << "num: " << num << std::endl;
}