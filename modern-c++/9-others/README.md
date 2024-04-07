在C++中，基本数据类型的大小（以字节为单位）并不是固定的，而是依赖于编译器实现和运行平台（操作系统和硬件架构）。

- char：1字节
- int：4字节（在32位和64位系统上普遍如此）
- long：
    - 在32位系统上通常是4字节
    - 在64位系统上可能是4字节（如Windows）或8字节（如Linux和MacOS）
- float：4字节
- long long：8字节

## 其他杂项

### 新类型

#### long long int

long long int并不是C++11最先引入的，其实早在C99，long long int就已经被纳入C标准中（long long），所以大部分的编译器早已支持。**C++11的工作则是正式把它纳入标准库， 规定了一个long long int类型至少具备64位的比特数**。

#### noexcept的修饰和操作

C++11 将异常的声明简化为以下两种情况，并使用noexcept对这两种行为进行限制：

1. 函数可能抛出任何异常
2. 函数不能抛出任何异常

```c++
void may_throw(); // 可能抛出异常
void no_throw() noexcept; // 不可能抛出异常
```

**使用noexcept修饰过的函数如果抛出异常，编译器会使用std::terminate()来立即终止程序运行**。noexcept还能够做操作符，用于操作一个表达式，当表达式无异常时，返回true，否则返回false。

```c++
#include <iostream>
void may_throw() {
    throw true;
}
auto non_block_throw = []{
    may_throw();
};
void no_throw() noexcept {
    return;
}

auto block_throw = []() noexcept {
    no_throw();
};
int main()
{
    std::cout << std::boolalpha
        << "may_throw() noexcept? " << noexcept(may_throw()) << std::endl
        << "no_throw() noexcept? " << noexcept(no_throw()) << std::endl
        << "lmay_throw() noexcept? " << noexcept(non_block_throw()) << std::endl
        << "lno_throw() noexcept? " << noexcept(block_throw()) << std::endl;
    return 0;
}
```

noexcept修饰完一个函数之后能够起到封锁异常扩散的功效，如果内部产生异常，外部也不会触发。

```c++
try {
    may_throw();
} catch (...) {
    std::cout << "捕获异常, 来自 may_throw()" << std::endl;
}
try {
    non_block_throw();
} catch (...) {
    std::cout << "捕获异常, 来自 non_block_throw()" << std::endl;
}
try {
    block_throw();
} catch (...) {
    std::cout << "捕获异常, 来自 block_throw()" << std::endl;
}

/*
捕获异常, 来自 may_throw()
捕获异常, 来自 non_block_throw()
*/
```

#### 字面量

传统C++里面要编写一个充满特殊字符的字符串其实是非常痛苦的一件事情， 比如一个包含HTML本体的字符串需要添加大量的转义符， 例如一个Windows上的文件路径经常会：`C:\\File\\To\\Path`。**C++11提供了原始字符串字面量的写法，可以在一个字符串前方使用R来修饰这个字符串， 同时，将原始字符串使用括号包裹**。

```c++
#include <iostream>
#include <string>

int main() {
    std::string str = R"(C:\File\To\Path)";
    std::cout << str << std::endl;
    return 0;
}
```

#### 自定义字面量

（感觉没太大用）

C++11引进了自定义字面量的能力，通过重载双引号后缀运算符实现。自定义字面量支持四种字面量：

```c++
// 字符串字面量自定义必须设置如下的参数列表
std::string operator"" _wow1(const char *wow1, size_t len) {
    return std::string(wow1)+"woooooooooow, amazing";
}

std::string operator"" _wow2 (unsigned long long i) {
    return std::to_string(i)+"woooooooooow, amazing";
}

int main() {
    auto str = "abc"_wow1;
    auto num = 1_wow2;
    std::cout << str << std::endl;
    std::cout << num << std::endl;
    return 0;
}
```

- 整型字面量：重载时必须使用unsigned long long、const char *、模板字面量算符参数，在上面的代码中使用的是前者；
- 浮点型字面量：重载时必须使用long double、const char *、模板字面量算符；
- 字符串字面量：必须使用 (const char *, size_t) 形式的参数表；
- 字符字面量：参数只能是 char, wchar_t, char16_t, char32_t 这几种类型。

### 内存对齐

C++ 11引入了两个新的关键字alignof和alignas来支持对内存对齐进行控制。 alignof关键字能够获得一个与平台相关的std::size_t类型的值，用于查询该平台的对齐方式。 当然我们有时候并不满足于此，甚至希望自定定义结构的对齐方式，同样，C++ 11还引入了alignas来重新修饰某个结构的对齐方式。其中 std::max_align_t要求每个标量类型的对齐方式严格一样，因此它几乎是最大标量没有差异，进而大部分平台上得到的结果为long double，因此我们这里得到的 AlignasStorage 的对齐要求是8或16。

```c++
#include <iostream>

struct Storage {
    char      a;
    int       b;
    double    c;
    long long d;
};

struct alignas(std::max_align_t) AlignasStorage {
    char      a;
    int       b;
    double    c;
    long long d;
};

int main() {
    std::cout << alignof(Storage) << std::endl;
    std::cout << alignof(AlignasStorage) << std::endl;
    return 0;
}
/*
8
16
*/
```