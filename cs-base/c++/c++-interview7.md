#### static_cast优点

1. 更安全，不允许逻辑上的大跨步，比如将整数直接转换为指针，在编译时会检查
2. 可读性更高，类型转换更明确

#### 回调函数

发生某种事件时，系统或其它函数会自动调用这段函数。

声明

定义

设置触发条件

将函数指针作为参数传入

#### 友元函数和友元类

将一个函数或一个类声明为某个类的“友元”，可以允许这些函数或类访问当前类的private和protected成员。

优势：

1. 灵活
2. 封装
3. 友元关系不能被继承、是单向的、不能有传递性

```c++
class Box {
public:
    Box(double w, double h, double d) : width(w), height(h), depth(d) {}

    // 声明一个非成员函数为友元
    friend double calculateVolume(const Box& b);

private:
    double width, height, depth;
};

double calculateVolume(const Box& b) {
    return b.width * b.height * b.depth;
}

class Engine;

class Car {
public:
    Car() : engine(nullptr) {}

    void setEngine(Engine* eng) {
        engine = eng;
    }

    // 声明另一个类为友元
    friend class Mechanic;

private:
    Engine* engine;
};

class Mechanic {
public:
    void repairEngine(Car& car) {
        // 访问 Car 类的私有成员
        car.engine = new Engine();
        // 可以执行更多与引擎相关的操作
    }
};
```

#### C语言模拟C++的继承

用结构体和函数指针

#### 静态编译和动态编译

静态编译：依赖的库在编译中进行链接，运行时不依赖动态链接库

动态编译：运行时加载动态链接库，所有用到该库的程序都共享这个文件

#### 介绍一下几种锁

读写锁：

1. 多个读者读
2. 一个写者写
3. 读优先锁、写优先锁

互斥锁：

1. 只有一个线程能拥有锁，等待的线程进入睡眠直到锁的状态改变被唤醒，也可能是自旋一段时间，超过阈值再睡眠，因为会涉及CPU的上下文切换

条件变量：

1. 只有锁定和非锁定两种状态
2. 与互斥锁使用
3. 锁状态变化通过条件变量唤醒一个或多个等待的线程，是同步机制

自旋锁：

1. 拿不到锁就一直尝试获取CPU直到获取为止，加锁时间比较短的场景效率比较高

#### 内联函数

只适合简单的代码比较少的函数

#### 虚函数表和虚函数指针

虚函数表和虚函数指针都是实现多态的关键。

1. 虚函数表：某个类包含至少一个虚函数时，编译器会为这个类生成虚函数表，这个表包含指向类的虚函数指针的数组
2. 虚函数指针：指向与对象类型相对应的虚函数表，当通过基类指针调用虚函数时，实际调用的函数通过虚函数指针找到虚函数表中对应的函数，实现动态绑定。

