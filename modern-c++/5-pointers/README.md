## 智能指针与内存管理

### RAII与引用计数

引用计数这种计数是为了防止内存泄露而产生的。 基**本想法是对于动态分配的对象，进行引用计数，每当增加一次对同一个对象的引用，那么引用对象的引用计数就会增加一次， 每删除一次引用，引用计数就会减一，当一个对象的引用计数减为零时，就自动删除指向的堆内存**。

在传统 C++ 中，『记得』手动释放资源，总不是最佳实践。因为我们很有可能就忘记了去释放资源而导致泄露。 所以通常的做法是对于一个对象而言，我们在构造函数的时候申请空间，而在析构函数（在离开作用域时调用）的时候释放空间， 也就是我们常说的RAII资源获取即初始化技术。

凡事都有例外，我们总会有需要将对象在自由存储上分配的需求，在传统C++里我们只好使用new和delete去『记得』对资源进行释放。**而C++11引入了智能指针的概念，使用了引用计数的想法，让程序员不再需要关心手动释放内存。 这些智能指针包括std::shared_ptr/std::unique_ptr/std::weak_ptr，使用它们需要包含头文件 <memory>**。

**引用计数和垃圾回收的大概区别**

引用计数：引用计数是一种内存管理技术，通过在对象上维护一个引用计数器来跟踪对象的引用数量。当引用计数为0时，表示没有任何指针指向该对象，可以安全地释放对象占用的内存。

优点：

- 立即回收：对象在成为垃圾时会立即被回收，不需要等待垃圾回收器的运行。简单高效：引用计数的实现相对简单，不需要进行停顿性的垃圾回收操作。
  
缺点：

- 循环引用问题：引用计数难以处理循环引用，即两个对象互相引用导致引用计数永远不会为0，从而导致内存泄漏。
  
- 开销大：每次引用计数发生变化时都需要更新计数器，可能会带来额外的性能开销（更新计数器本身其实是很小的开销，但是所有的引用传递都去更新，累积起来也很大）。
  
垃圾回收：垃圾回收是一种自动内存管理技术，通过检测和回收不再被程序使用的内存来避免内存泄漏。**常见的垃圾回收算法包括标记-清除、引用计数、复制算法**等。

优点：

- 处理循环引用：垃圾回收器可以处理循环引用，通过识别不可达对象并将其回收来解决内存泄漏问题。

- 自动化：程序员无需手动管理内存，减少了出错的可能性。
  
缺点：

- 停顿：某些垃圾回收算法可能导致程序在进行垃圾回收时出现停顿，影响程序性能。
  
- 实现复杂：一些高效的垃圾回收算法实现较为复杂，可能会消耗额外的计算资源。

### std::shared_ptr

**std::shared_ptr能够记录多少个shared_ptr共同指向一个对象，从而消除显式的调用delete，当引用计数变为零的时候就会将对象自动删除**。因为使用 std::shared_ptr 仍然需要使用new来调用，这使得代码出现了某种程度上的不对称。**std::make_shared就能够用来消除显式的使用new，所以std::make_shared会分配创建传入参数中的对象， 并返回这个对象类型的std::shared_ptr指针**。std::shared_ptr可以通过get()方法来获取原始指针，通过reset()来减少一个引用计数， 并通过use_count()来查看一个对象的引用计数。

```c++
#include <iostream>
#include <memory>
void foo(std::shared_ptr<int> i) {
    (*i)++;
}
int main() {
    // auto pointer = new int(10); // illegal, no direct assignment
    // Constructed a std::shared_ptr
    auto pointer = std::make_shared<int>(10);
    foo(pointer);
    std::cout << *pointer << std::endl; // 11
    // The shared_ptr will be destructed before leaving the scope
    return 0;
}
auto pointer = std::make_shared<int>(10);
auto pointer2 = pointer; // 引用计数+1
auto pointer3 = pointer; // 引用计数+1
int *p = pointer.get();  // 这样不会增加引用计数
std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl;   // 3
std::cout << "pointer2.use_count() = " << pointer2.use_count() << std::endl; // 3
std::cout << "pointer3.use_count() = " << pointer3.use_count() << std::endl; // 3

pointer2.reset();
std::cout << "reset pointer2:" << std::endl;
std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl;   // 2
std::cout << "pointer2.use_count() = "
          << pointer2.use_count() << std::endl;           // pointer2 已 reset; 0
std::cout << "pointer3.use_count() = " << pointer3.use_count() << std::endl; // 2
pointer3.reset();
std::cout << "reset pointer3:" << std::endl;
std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl;   // 1
std::cout << "pointer2.use_count() = " << pointer2.use_count() << std::endl; // 0
std::cout << "pointer3.use_count() = " << pointer3.use_count() << std::endl;  // pointer3 已 reset; 0
```

### std::unique_ptr

std::unique_ptr是一种独占的智能指针，它禁止其他智能指针与其共享同一个对象，从而保证代码的安全。虽然不可复制，但是可以使用std::move（可以将左值转换为右值）转移给其他的std::unique_ptr。

```c++
std::unique_ptr<int> pointer = std::make_unique<int>(10); // make_unique 从 C++14 引入，C++11没有是单纯被忘记了:(
std::unique_ptr<int> pointer2 = pointer; // 非法
```

### std::weak_ptr

前面提到引用计数无法处理循环引用，从而导致资源的引用永远不会变为0，从而导致内存泄漏。

```c++
struct A;
struct B;

struct A {
    std::shared_ptr<B> pointer;
    ~A() {
        std::cout << "A 被销毁" << std::endl;
    }
};
struct B {
    std::shared_ptr<A> pointer;
    ~B() {
        std::cout << "B 被销毁" << std::endl;
    }
};
int main() {
    auto a = std::make_shared<A>();
    auto b = std::make_shared<B>();
    a->pointer = b;
    b->pointer = a;
}
```

<img src="https://changkun.de/modern-cpp/assets/figures/pointers1.png">

std::weak_ptr，std::weak_ptr是一种弱引用（相比较而言 std::shared_ptr 就是一种强引用），弱引用不会引起引用计数增加。

<img src="https://changkun.de/modern-cpp/assets/figures/pointers2.png">

上图中，由于b->pointer为弱引用，因此a->pointer只有a一个引用，当a销毁后，a->pointer也随之销毁，b被销毁后，b->pointer没有引用，内存资源被释放。

std::weak_ptr没有 * 运算符和 -> 运算符，所以不能够对资源进行操作，它可以用于检查std::shared_ptr是否存在，其expired()方法能在资源未被释放时，会返回false，否则返回true；除此之外，它也可以用于获取指向原始对象的std::shared_ptr指针，其lock()方法在原始对象未被释放时，返回一个指向原始对象的std::shared_ptr指针，进而访问原始对象的资源，否则返回nullptr。
