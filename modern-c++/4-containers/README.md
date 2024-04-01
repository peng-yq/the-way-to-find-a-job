在腾讯技术工程中看到的一些问题，遂记录：

- 空指针到底能不能访问？(int *p = nullptr; p = 5;)：不可以。尝试通过空指针（nullptr）访问或修改数据会导致未定义行为（Undefined Behavior, UB），通常会导致程序崩溃。例如，int *p = nullptr; *p = 5; 这段代码尝试通过空指针p写入值5，这是不合法的操作。

- 给一个变量取地址，取到的是不是物理地址？(int a; std::cout << &a;)：取到的是虚拟地址，而非物理地址。在现代操作系统中，程序看到的地址是虚拟内存地址，操作系统和硬件协同工作，通过内存管理单元（MMU）将虚拟地址映射到物理地址上。因此，std::cout << &a; 输出的是变量a的虚拟地址。
  
- 操作一个常数地址是否合法？（(int \*)0xa0000 = 0x41;）：通常不合法且危险。尽管技术上可以通过强制类型转换将一个地址常量转换为指针并尝试写入（如*(int *)0xa0000 = 0x41;），但这种操作依赖于特定的硬件和操作系统环境，且很容易导致程序崩溃或者未定义行为。在受保护的操作系统中，随意访问某个物理地址是被禁止的。
  
- 全局变量、静态局部变量、字符串字面量等在内存中是如何布局的？
  - 全局变量：存储在程序的数据段（data segment）或BSS段（未初始化的全局变量）。
  - 静态局部变量：存储在数据段，与全局变量类似，但只在声明它的函数内可见。
  - 字符串字面量：存储在只读数据段（rodata segment），尝试修改字符串字面量的内容会导致未定义行为。
  
- C/C++程序如何编译为内核代码，运行在内核态程序上？：C/C++代码通常编译为用户态程序。要运行在内核态，代码需要以内核模块的形式编写并加载到内核中，或者直接编写为操作系统的一部分。这涉及到使用特定于操作系统的API和遵守内核编程的规则（如内存管理、同步机制等）。编译内核代码通常需要使用特定的编译器选项和链接到内核提供的服务。
  
- gdb过程中，看到的寄存器是否是真实的？：是真实的。在使用GDB调试程序时，看到的寄存器值反映的是当前CPU寄存器的状态或者特定时刻的快照。这些信息对于理解程序的执行流程和调试非常有用。

## 容器

### 线性容器

#### std::array

1.std::array和std::vector：std::array 对象的大小是固定的，如果容器大小是固定的，那么可以优先考虑使用 std::array 容器。 另外由于 std::vector 是自动扩容的，当存入大量的数据后，并且对容器进行了删除操作， 容器并不会自动归还被删除元素相应的内存，这时候就需要手动运行 shrink_to_fit() 释放这部分内存。

```c++
std::vector<int> v;
std::cout << "size:" << v.size() << std::endl;         // 输出 0
std::cout << "capacity:" << v.capacity() << std::endl; // 输出 0

// 如下可看出 std::vector 的存储是自动管理的，按需自动扩张
// 但是如果空间不足，需要重新分配更多内存，而重分配内存通常是性能上有开销的操作
v.push_back(1);
v.push_back(2);
v.push_back(3);
std::cout << "size:" << v.size() << std::endl;         // 输出 3
std::cout << "capacity:" << v.capacity() << std::endl; // 输出 4

// 这里的自动扩张逻辑与 Golang 的 slice 很像
v.push_back(4);
v.push_back(5);
std::cout << "size:" << v.size() << std::endl;         // 输出 5
std::cout << "capacity:" << v.capacity() << std::endl; // 输出 8

// 如下可看出容器虽然清空了元素，但是被清空元素的内存并没有归还
v.clear();                                             
std::cout << "size:" << v.size() << std::endl;         // 输出 0
std::cout << "capacity:" << v.capacity() << std::endl; // 输出 8

// 额外内存可通过 shrink_to_fit() 调用返回给系统
v.shrink_to_fit();
std::cout << "size:" << v.size() << std::endl;         // 输出 0
std::cout << "capacity:" << v.capacity() << std::endl; // 输出 0
```

2.std::array和普通数组：std::array能够让代码变得更加“现代化”，而且封装了一些操作函数，比如获取数组大小以及检查是否非空，同时还能够友好的使用标准库中的容器算法，比如std::sort。

```c++
std::array<int, 4> arr = {1, 2, 3, 4};

arr.empty(); // 检查容器是否为空
arr.size();  // 返回容纳的元素数

// 迭代器支持
for (auto &i : arr)
{
    // ...
}

// 用 lambda 表达式排序
std::sort(arr.begin(), arr.end(), [](int a, int b) {
    return b < a;
});

// 数组大小参数必须是常量表达式
constexpr int len = 4;
std::array<int, len> arr = {1, 2, 3, 4};

// 非法,不同于 C 风格数组，std::array 不会自动退化成 T*
// int *arr_p = arr;
```

如果需要兼容c风格的接口，可采用以下做法：

```c++
void foo(int *p, int len) {
    return;
}

std::array<int, 4> arr = {1,2,3,4};

// C 风格接口传参
// foo(arr, arr.size()); // 非法, 无法隐式转换
foo(&arr[0], arr.size());
foo(arr.data(), arr.size());
```

#### std::forward_list

和std::list的双向链表的实现不同，std::forward_list使用单向链表进行实现， 提供了O(1)复杂度的元素插入，不支持快速随机访问（这也是链表的特点）， 也是标准库容器中唯一一个不提供size()方法的容器。当不需要双向迭代时，具有比std::list更高的空间利用率。

**需要使用list的场景**：需要频繁在序列的中间插入或删除元素时，list是一个很好的选择。例如，在实现一个撤销功能时，你可能需要在操作的历史记录中频繁地插入和删除记录。

### 无序容器

传统C++中的有序容器std::map/std::set，**这些元素内部通过红黑树进行实现， 插入和搜索的平均复杂度均为O(log(size))（二分查找）**。在插入元素时候，会根据<操作符比较元素大小并判断元素是否相同， 并选择合适的位置插入到容器中。当对这个容器中的元素进行遍历时，输出结果会按照<操作符的顺序来逐个遍历。

**而无序容器中的元素是不进行排序的，内部通过Hash表实现，插入和搜索元素的平均复杂度为O(constant)**， 在不关心容器内部元素顺序时，能够获得显著的性能提升。

C++11引入了的两组无序容器分别是：std::unordered_map/std::unordered_multimap 和std::unordered_set/std::unordered_multiset。它们的用法和原有的std::map/std::multimap/std::set/set::multiset基本类似。

### 元组

#### 元组基本操作

关于元组的使用有三个核心的函数：

- std::make_tuple: 构造元组
- std::get: 获得元组某个位置的值
- std::tie: 元组拆包

```c++
#include <tuple>
#include <iostream>

auto get_student(int id)
{
    // 这个时候用auto就很方便，返回类型被推断为 std::tuple<double, char, std::string>

    if (id == 0)
        return std::make_tuple(3.8, 'A', "张三");
    if (id == 1)
        return std::make_tuple(2.9, 'C', "李四");
    if (id == 2)
        return std::make_tuple(1.7, 'D', "王五");
    return std::make_tuple(0.0, 'D', "null");
    // 如果只写 0 会出现推断错误, 编译失败
}

int main()
{
    auto student = get_student(0);
    std::cout << "ID: 0, "
    << "GPA: " << std::get<0>(student) << ", "
    << "成绩: " << std::get<1>(student) << ", "
    << "姓名: " << std::get<2>(student) << '\n';

    double gpa;
    char grade;
    std::string name;

    // 元组进行拆包
    std::tie(gpa, grade, name) = get_student(1);
    std::cout << "ID: 1, "
    << "GPA: " << gpa << ", "
    << "成绩: " << grade << ", "
    << "姓名: " << name << '\n';
}
```
std::get除了使用常量获取元组对象外，C++14增加了使用类型来获取元组中的对象：

```c++
std::tuple<std::string, double, double, int> t("123", 4.5, 6.7, 8);
std::cout << std::get<std::string>(t) << std::endl;
```

**ps：后面还有运行期索引和元组合并和遍历，感觉比较鸡肋，一般还是自己定义结构体然后返回**