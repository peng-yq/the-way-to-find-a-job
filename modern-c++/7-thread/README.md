**进程和线程**

进程是操作系统分配资源的基本单位。每个进程都有自己独立的地址空间、内存、数据栈以及其他记录其运行轨迹的辅助数据。进程之间相互独立，一个进程无法直接访问另一个进程的资源和数据，因此进程是资源隔离和保护的基本边界。不同进程间的通信（IPC，Inter-Process Communication）需要通过操作系统提供的机制进行，如管道、消息队列、共享内存等。在C++中创建新进程通常依赖于操作系统提供的API。在Unix/Linux系统中，可以使用fork()系统调用来创建新进程。

线程是进程内的执行单元，一共进程可以包含一个或多个线程。线程是操作系统调度的实体和基本单位，操作系统的调度器（Scheduler）会在可运行的线程之间进行切换，决定哪个线程将获得CPU时间进行执行。线程不拥有资源，只拥有一点在运行中必不可少的资源（如执行栈、寄存器状态等），但能访问隶属进程的资源。同一进程内的线程共享该进程的地址空间和资源，这使得线程间的通信和数据共享变得更加容易，但也需要注意同步和数据一致性的问题。在C++中，创建和管理线程可以通过C++11引入的线程库来实现。

主要区别：
- 资源独立性：进程拥有独立的资源，而线程共享进程资源。
- 通信方式：进程间通信需要特殊的IPC机制，线程间通信更加方便，因为它们自然地共享了进程的资源。
- 开销：创建和销毁进程的开销远大于线程，同理，进程间的切换开销也大于线程间的切换。
- 数据共享、同步：由于线程共享进程资源，因此线程间的数据共享和同步非常重要，以避免数据不一致等问题。

## 并行与并发

并行和并发的概念很容易混淆，都是用于描述系统如何处理多个任务的方式。
- [之前写的博客：Concurrency and Parallelism](https://peng-yq.github.io/2023/12/22/concurrency-parallelism/)
- [Talk：Rob Pike：Concurrency and Parallelism](https://www.bilibili.com/video/BV1EN411o7FY/)

并发是指系统能够处理多个任务的能力。在并发模型中，一个处理器在同一时间点或时间段内处理多个任务。这不意味着这些任务实际上是在同一时刻执行的；而是通过任务之间的快速切换，给用户一种多个任务同时进行的错觉。**并发更多地关注的是结构上的分离，即如何组织程序或系统以同时处理多个任务**。并发的一个常见场景是在单核CPU上运行的多任务操作系统。尽管CPU在任意时刻只能执行一个任务，但操作系统通过在不同任务之间迅速切换，使得多个程序似乎是“同时”运行。在c++中可以通过std::thread来实现并发（不使用则程序主要运行在单个线程上，即主线程，除非使用的某些外部库内部创建了线程）。

并行是指多个处理器或多核处理器同时执行多个任务或同一个任务的不同部分的能力。并行计算的目的是通过同时使用多个计算资源来加速处理过程。**并行更多地关注的是性能上的提升，即如何利用多个处理器或多核心同时执行任务以提高效率和速度**。一个典型的并行计算例子是在多核CPU上运行的程序，其中每个核心被分配了不同的任务或同一个任务的不同部分，它们真正意义上是在同一时刻并行执行的。在c++中可以通过std::thread和std::async来实现并行。

可以说并行是并发的一个子集或特例。

### 并行基础

std::thread用于创建一个执行的线程实例，使用时需要包含 <thread> 头文件，它提供了很多基本的线程操作，例如get_id()来获取所创建线程的线程ID，使用join()来等待一个线程结束（与该线程汇合）等等：

```c++
#include <iostream>
#include <thread>

int main() {
    std::thread t([](){
        std::cout << "hello world." << std::endl;
    });
    t.join();
    return 0;
}
```

### 互斥量与临界区

互斥量与临界区都是用于同步多个线程对共享资源访问的机制，避免发生竞态条件和保证数据的一致性。

互斥量是一种同步原语，用于保护共享资源，确保在任何时刻只有一个线程可以访问该资源。互斥量可以是跨进程的（即可以在不同进程的线程之间同步）。适用于需要跨进程同步或者需要更细粒度控制的场景。例如，C++中的std::mutex就提供了一个跨线程的互斥锁实现。互斥量提供了锁定（lock）和解锁（unlock）操作。当一个线程锁定了互斥量后，其他试图锁定该互斥量的线程将会阻塞，直到互斥量被解锁。可以跨不同的代码区域使用。

临界区通常指代代码中访问共享资源的部分，用于控制同一进程内多个线程对共享资源的访问。主要用于同一进程内的线程同步，由于临界区对象通常存储在用户进程的内存空间中，因此它们不能用于进程间同步。临界区相对于互斥量有更轻量级的开销，因为它们是为了同一进程内的线程同步而设计的。

std::mutex是C++11中最基本的mutex类，通过实例化std::mutex可以创建互斥量，而通过其成员函数lock()可以进行上锁，unlock()可以进行解锁。但是在实际编写代码的过程中，最好不去直接调用成员函数， 因为调用成员函数就需要在每个临界区的出口处调用unlock()，当然，还包括异常。这时候C++11还为互斥量提供了一个RAII语法的模板类std::lock_guard。RAII在不失代码简洁性的同时，很好的保证了代码的异常安全性。在RAII用法下，对于临界区的互斥量的创建只需要在作用域的开始部分。

```c++
#include <iostream>
#include <mutex>
#include <thread>

int v = 1;

void critical_section(int change_v) {
    static std::mutex mtx;
    std::lock_guard<std::mutex> lock(mtx);

    // 执行竞争操作
    v = change_v;

    // 离开此作用域后 mtx 会被释放
}

int main() {
    std::thread t1(critical_section, 2), t2(critical_section, 3);
    t1.join();
    t2.join();

    std::cout << v << std::endl;
    return 0;
}
```

由于C++保证了所有栈对象在生命周期结束时会被销毁，所以上述代码也是异常安全的。无论critical_section()正常返回、还是在中途抛出异常，都会引发堆栈回退，也就自动调用了unlock()。

而std::unique_lock则是相对于 std::lock_guard 出现的，std::unique_lock更加灵活，std::unique_lock的对象会以独占所有权（没有其他的unique_lock对象同时拥有某个mutex对象的所有权）的方式管理mutex对象上的上锁和解锁的操作。所以在并发编程中，推荐使用std::unique_lock。**std::lock_guard 不能显式的调用lock和unlock， 而std::unique_lock可以在声明后的任意位置调用，可以缩小锁的作用范围，提供更高的并发度。**如果用到了条件变量std::condition_variable::wait则必须使用std::unique_lock作为参数。

```c++
#include <iostream>
#include <mutex>
#include <thread>

int v = 1;

void critical_section(int change_v) {
    static std::mutex mtx;
    std::unique_lock<std::mutex> lock(mtx);
    // 执行竞争操作
    v = change_v;
    std::cout << v << std::endl;
    // 将锁进行释放
    lock.unlock();

    // 在此期间，任何人都可以抢夺 v 的持有权

    // 开始另一组竞争操作，再次加锁
    lock.lock();
    v += 1;
    std::cout << v << std::endl;
}

int main() {
    std::thread t1(critical_section, 2), t2(critical_section, 3);
    t1.join();
    t2.join();
    return 0;
}
```

### 期物

期物（Future）表现为std::future，它提供了一个访问异步操作结果的途径，这句话很不好理解。试想当主线程A希望新开辟一个线程B去执行某个我们预期的任务，并返回我一个结果。而这时候，线程A可能正在忙其他的事情，无暇顾及B的结果，所以我们会很自然的希望能够在某个特定的时间获得线程B的结果。在C++11的std::future被引入之前，通常的做法是：创建一个线程A，在线程A里启动任务B，当准备完毕后发送一个事件，并将结果保存在全局变量中。而主函数线程A里正在做其他的事情，当需要结果的时候，调用一个线程等待函数来获得执行的结果。例如下面的例子，条件变量后面会介绍。

```c++
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

// 全局变量用于保存任务结果
int result;
// 互斥锁和条件变量用于同步
std::mutex mtx;
std::condition_variable cv;
bool ready = false; // 用于指示任务是否完成

// 任务函数
void square(int x) {
    std::this_thread::sleep_for(std::chrono::seconds(1)); // 模拟耗时操作
    int temp_result = x * x;
    
    // 保存结果到全局变量，并通知等待的线程
    {
        std::lock_guard<std::mutex> lk(mtx);
        result = temp_result;
        ready = true;
    }
    cv.notify_one();
}

int main() {
    // 创建并启动线程
    std::thread t(square, 4);
    
    // 在主线程中等待任务完成
    {
        std::unique_lock<std::mutex> lk(mtx);
        cv.wait(lk, []{return ready;});
    }
    
    // 使用结果
    std::cout << "Result is: " << result << std::endl;
    
    // 确保线程结束
    t.join();
    return 0;
}
```

而C++11提供的std::future简化了这个流程，可以用来获取异步任务的结果。 自然地，我们很容易能够想象到把它作为一种简单的线程同步手段，即屏障（barrier）。为了看一个例子，这里额外使用 std::packaged_task，它可以用来封装任何可以调用的目标，从而用于实现异步的调用。

```c++
#include <iostream>
#include <future>
#include <thread>
#include <chrono>

// 定义一个简单的计算函数
int square(int x) {
    // 假设这个计算需要一些时间
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return x * x;
}

int main() {
    // 使用std::packaged_task封装square函数，int(int)是square的签名
    std::packaged_task<int(int)> task(square);
    // 获取与packaged_task相关联的future
    std::future<int> result = task.get_future();

    // 在一个新线程上执行任务
    std::thread t(std::move(task), 4); // 计算4的平方

    // 主线程可以继续做其他事情...
    std::cout << "主线程正在做其他事情..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "主线程等待结果..." << std::endl;

    // 等待异步任务的结果
    int value = result.get(); // 这里会阻塞，直到异步任务完成并返回结果

    std::cout << "计算结果: " << value << std::endl;

    // 确保线程执行完成
    t.join();

    return 0;
}
```

> std::packaged_task对象是不可复制的，但可以被移动。这意味着你不能通过简单地复制一个std::packaged_task对象来将其从一个作用域传递到另一个作用域（例如，从主线程传递到子线程）。这是因为复制一个std::packaged_task对象会引起所有权和状态的不明确，特别是它关联的std::future对象的状态。**使用std::move可以有效地将task对象的所有权从主线程转移到新创建的线程t中。在std::move后，原始的task对象在主线程中变为处于“已移动”状态，这意味着它不再持有之前封装的任务或任何资源。而在新线程中，移动后的task对象则完整地拥有了原始任务和资源的所有权，可以安全地执行封装的任务**。

### 条件变量

互斥锁（std::mutex）是实现线程同步的基本工具之一，它可以保护共享数据，防止多个线程同时访问，从而避免数据竞争和不一致性。然而，仅仅使用互斥锁并不能解决所有的线程同步问题。特别是，当某些操作需要在特定条件满足时才能进行时，仅使用互斥锁可能会导致问题。例如，如果一个线程需要等待某个条件变为真才能继续执行，它可能会进入一个忙等待（busy-wait）状态，不断检查条件是否满足。这种忙等待不仅浪费CPU资源，两个或多个进程或线程在等待对方持有的资源，从而导致它们之间的循环等待，就会导致死锁。更具体地说，如果线程A持有互斥锁并且在等待某个条件（这个条件需要线程B的操作才能成立），但是线程B为了执行使条件成立的操作，也需要获取之前被线程A持有的互斥锁，这时就发生了死锁。线程A等待条件成立才释放锁，而线程B需要锁才能使条件成立。

为了解决这个问题，C++标准库提供了条件变量（std::condition_variable）。条件变量允许一个或多个线程在某个条件变为真之前挂起（等待），而不占用任何CPU资源。当条件可能已经满足时，其他线程可以通过条件变量通知等待的线程重新检查条件，并根据需要继续执行。

std::condition_variable主要通过以下三个成员函数实现其功能：
- wait(lock, predicate): 该函数使调用线程等待（挂起），直到被通知（通过notify_one或notify_all），同时释放传入的lock（通常是基于std::unique_lock<std::mutex>的锁）。**在重新获得锁后，wait函数会再次检查predicate（一个返回布尔值的函数或lambda表达式），如果predicate结果为false，线程会再次等待。这防止了虚假唤醒（spurious wakeups）**。
- notify_one(): 唤醒一个等待（挂起）在这个条件变量上的线程。如果有多个线程在等待，选择哪个线程被唤醒是不确定的。
- notify_all(): 唤醒所有等待（挂起）在这个条件变量上的线程。

```c++
#include <queue>
#include <chrono>
#include <mutex>
#include <thread>
#include <iostream>
#include <condition_variable>


int main() {
    std::queue<int> produced_nums;
    std::mutex mtx;
    std::condition_variable cv;
    bool notified = false;  // 通知信号

    // 生产者
    auto producer = [&]() {
        for (int i = 0; ; i++) {
            std::this_thread::sleep_for(std::chrono::milliseconds(900));
            std::unique_lock<std::mutex> lock(mtx);
            std::cout << "producing " << i << std::endl;
            produced_nums.push(i);
            notified = true;
            cv.notify_all(); // 此处也可以使用 notify_one
        }
    };
    // 消费者
    auto consumer = [&]() {
        while (true) {
            std::unique_lock<std::mutex> lock(mtx);
            while (!notified) {  // 避免虚假唤醒
                cv.wait(lock);
            }
            // 短暂取消锁，使得生产者有机会在消费者消费空前继续生产
            lock.unlock();
            // 消费者慢于生产者
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            lock.lock();
            while (!produced_nums.empty()) {
                std::cout << "consuming " << produced_nums.front() << std::endl;
                produced_nums.pop();
            }
            notified = false;
        }
    };

    // 分别在不同的线程中运行
    std::thread p(producer);
    std::thread cs[2];
    for (int i = 0; i < 2; ++i) {
        cs[i] = std::thread(consumer);
    }
    p.join();
    for (int i = 0; i < 2; ++i) {
        cs[i].join();
    }
    return 0;
}
```

上述代码存在一些潜在的问题：在消费者线程中，lock.unlock()和随后的lock.lock()之间存在一个时间窗口，其他线程（例如生产者线程）可能会在这个时间窗口内修改produced_nums和notified，这可能导致一些不一致的行为。

一部分输出结果如下：

```shell
producing 0
producing 1
consuming 0
consuming 1
producing 2
producing 3
consuming 2
consuming 3
```

生产者线程的工作是无限循环生成整数，并将其放入队列中。对于每个生成的整数，生产者都会：

1. 暂停900毫秒，模拟生产过程。
2. 获取互斥锁mtx。
3. 打印生产的整数。
4. 将整数推入队列produced_nums。
5. 设置notified为true，表示有数据可供消费。
6. 通过调用cv.notify_all()通知等待的消费者线程（在这个场景中，使用notify_one()也可以，但notify_all()确保所有消费者线程都被唤醒，这在多消费者场景下更有用），如果我们打印出当前消费者的编号，你会发现是随机的。

消费者线程的工作也是无限循环，但它等待生产者生成数据后才开始消费。对于每次消费操作，消费者都会：

1. 获取互斥锁mtx。
2. 检查notified是否为false，如果是，则等待条件变量cv的通知。这里使用while循环是为了防止虚假唤醒（即线程被唤醒但条件并未真正满足）。
3. 暂时释放互斥锁mtx，允许生产者有机会生产更多数据。
4. 暂停1000毫秒，模拟消费过程，这里消费者故意设置为比生产者慢，以便观察生产和消费的过程。
5. 再次获取互斥锁mtx。
6. 消费队列中的所有数据，打印每个被消费的整数。
7. 设置notified为false，表示所有数据已被消费完毕。

### 原子操作和内存模型

上节中的生产者消费者模型的例子可能存在编译器优化导致程序出错的情况。 例如，布尔值notified没有被volatile修饰，编译器可能对此变量存在优化，例如将其作为一个寄存器的值， 从而导致消费者线程永远无法观察到此值的变化。这是一个好问题，为了解释清楚这个问题，我们需要进一步讨论从C++ 11 起引入的内存模型这一概念。

> volatile：用于告诉编译器，一个变量的值可能会在没有明显的程序代码修改的情况下发生改变。这通常用于访问硬件设备、中断处理、多线程应用中共享变量的读写等场景。**当一个变量被声明为volatile时，编译器会避免对这个变量的读写操作进行优化，确保每次访问都直接从内存中读取数据，而不是从缓存或寄存器中**。

```c++
#include <thread>
#include <iostream>

int main() {
    int a = 0;
    int flag = 0;

    std::thread t1([&]() {
        while (flag != 1);

        int b = a;
        std::cout << "b = " << b << std::endl;
    });

    std::thread t2([&]() {
        a = 5;
        flag = 1;
    });

    t1.join();
    t2.join();
    return 0;
}
```

从直观上看，t2中a = 5; 这一条语句似乎总在flag = 1; 之前得到执行，而t1中while (flag != 1) 似乎保证了 std::cout << "b = " << b << std::endl; 不会再标记被改变前执行。从逻辑上看，似乎 b 的值应该等于 5。 但实际情况远比此复杂得多，或者说这段代码本身属于未定义的行为，因为对于 a 和 flag 而言，他们在两个并行的线程中被读写， 出现了竞争。除此之外，即便我们忽略竞争读写，仍然可能受 CPU 的乱序执行，编译器对指令的重排的影响， 导致 a = 5 发生在 flag = 1 之后。从而 b 可能输出 0。

> 笔者跑了几次，都是b=5，总体而言这个示例还是太简单太弱了，但理论上确实是可能的

#### 原子操作

为了使上述代码能够正确且可靠地在多线程环境下工作，可以采用以下任一解决方案：

- 使用std::atomic来声明a和flag变量，确保它们的读写操作是原子的，从而避免数据竞争和确保内存可见性。
- 使用互斥锁（std::mutex）和条件变量（std::condition_variable）来同步线程之间的操作。
  
std::mutex可以解决上面出现的并发读写的问题，但互斥锁是操作系统级的功能，这是因为一个互斥锁的实现通常包含两条基本原理：1.提供线程间自动的状态转换，即『锁住』这个状态；2.保障在互斥锁操作期间，所操作变量的内存与临界区外进行隔离。这是一组非常强的同步条件，换句话说当最终编译为CPU指令时会表现为非常多的指令。 这对于一个仅需原子级操作（没有中间态）的变量，似乎太苛刻了。现代CPU体系结构提供了CPU指令级的原子操作，因此在C++11中多线程下共享变量的读写这一问题上，还引入了std::atomic模板，使得我们实例化一个原子类型，将一个原子类型读写操作从一组指令，最小化到单个CPU指令。

```c++
std::atomic<int> counter;
```

并为整数或浮点数的原子类型提供了基本的数值成员函数，举例来说，包括 fetch_add, fetch_sub等，同时通过重载方便的提供了对应的+，-版本。 

```c++
#include <atomic>
#include <thread>
#include <iostream>

std::atomic<int> count = {0};

int main() {
    std::thread t1([](){
        count.fetch_add(1);
    });
    std::thread t2([](){
        count++;        // 等价于 fetch_add
        count += 1;     // 等价于 fetch_add
    });
    t1.join();
    t2.join();
    std::cout << count << std::endl;
    return 0;
}
```

当然，并非所有的类型都能提供原子操作，这是因为原子操作的可行性取决于具体的 CPU 架构，以及所实例化的类型结构是否能够满足该 CPU 架构对内存对齐 条件的要求，因而我们总是可以通过 std::atomic<T>::is_lock_free 来检查该原子类型是否需支持原子操作

```c++
#include <atomic>
#include <iostream>

struct A {
    float x;
    int y;
    long long z;
};

int main() {
    std::atomic<A> a;
    std::cout << std::boolalpha << a.is_lock_free() << std::endl;
    return 0;
}
```

> 报编译错误了

#### 一致性模型

一致性模型是在并行计算中，定义了对共享数据的访问在多个处理器或线程间如何被看到的规则。并行执行的多个线程，从某种宏观层面上讨论，可以粗略的视为一种分布式系统。在分布式系统中，任何通信乃至本地操作都需要消耗一定时间，甚至出现不可靠的通信。每个线程可以对应为一个集群节点，而线程间的通信也几乎等价于集群节点间的通信。削弱进程间的同步条件从而提升效率，通常我们会考虑四种不同的一致性模型：

1. 线性一致性：又称强一致性或原子一致性。它要求任何一次读操作都能读到某个数据的最近一次写的数据，并且所有线程的操作顺序与全局时钟下的顺序是一致的。

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202404051857382.png">

在这种情况下线程T1, T2对x的两次写操作是原子的，且x.store(1)是严格的发生在x.store(2) 之前，x.store(2)严格的发生在 x.load() 之前。值得一提的是，**线性一致性对全局时钟的要求是难以实现的**，这也是人们不断研究比这个一致性更弱条件下其他一致性的算法的原因。

2. 顺序一致性：同样要求任何一次读操作都能读到数据最近一次写入的数据，但未要求与全局时钟的顺序一致。

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202404051859866.png">

在顺序一致性的要求下，x.load()必须读到最近一次写入的数据，因此x.store(2)与x.store(1)并无任何先后保障，即只要T2的x.store(2)发生在x.store(3)之前即可。

3. 因果一致性：它的要求进一步降低，只需要有因果关系的操作顺序得到保障，而非因果关系的操作顺序则不做要求。

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202404051902786.png">

上面给出的三种例子都是属于因果一致的，因为整个过程中，只有c对a和b产生依赖，而x和y在此例子中表现为没有关系（但实际情况中我们需要更详细的信息才能确定x与y确实无关）。**这是分布式系统中常见的一致性模型，允许系统在保证因果关系的前提下优化性能**。

4. 最终一致性：是最弱的一致性要求，它只保障某个操作在未来的某个时间节点上会被观察到，但并未要求被观察到的时间。因此我们甚至可以对此条件稍作加强，例如规定某个操作被观察到的时间总是有界的。

#### 内存一致性

为了追求极致的性能，实现各种强度要求的一致性，C++11为原子操作定义了六种不同的内存顺序std::memory_order的选项，表达了四种多线程间的同步模型（PS：太高级了x，得对体系结构比较熟练了x）：

1. 宽松模型：在此模型下，单个线程内的原子操作都是顺序执行的，不允许指令重排，但不同线程间原子操作的顺序是任意的。类型通过 std::memory_order_relaxed指定。
2. 释放/消费模型：在此模型中，我们开始限制进程间的操作顺序，如果某个线程需要修改某个值，但另一个线程会对该值的某次操作产生依赖，即后者依赖前者。具体而言，线程A完成了三次对x的写操作，线程B仅依赖其中第三次x的写操作，与x的前两次写行为无关，则当A主动x.release()时候（即使用 std::memory_order_release），选项std::memory_order_consume能够确保B在调用x.load()时候观察到A中第三次对x的写操作。
3. 释放/获取模型：在此模型下，我们可以进一步加紧对不同线程间原子操作的顺序的限制，在释放 std::memory_order_release 和获取 std::memory_order_acquire 之间规定时序，即发生在释放（release）操作之前的所有写操作，对其他线程的任何获取（acquire）操作都是可见的，亦即发生顺序（happens-before）。可以看到，std::memory_order_release 确保了它之前的写操作不会发生在释放操作之后，是一个向后的屏障（backward），而 std::memory_order_acquire 确保了它之前的写行为不会发生在该获取操作之后，是一个向前的屏障（forward）。对于选项 std::memory_order_acq_rel 而言，则结合了这两者的特点，唯一确定了一个内存屏障，使得当前线程对内存的读写不会被重排并越过此操作的前后。
4. 顺序一致模型：在此模型下，原子操作满足顺序一致性，进而可能对性能产生损耗。可显式的通过 std::memory_order_seq_cst 进行指定。
