## 语言可用性的强化

语言可用性是指程序运行之前的行为，包括编写代码和编译器编译过程中产生的行为。

### 变量

**隐式转换**：编译器自动进行的类型转换，无需程序员干预。这种转换通常发生在当表达式中涉及多种不同的数据类型时，编译器会自动将其中某些类型转换为其他类型，以满足操作的需求。

```c++
int i = 5;
double d = 6.7;
auto result = i + d; // i 被隐式转换为 double
```

**显式转换**：程序员明确指定的类型转换。在C++中，显式转换可以通过四种C++风格的转换操作符实现：static_cast、dynamic_cast、const_cast和reinterpret_cast，以及传统的C风格类型转换。

```c++
double d = 9.5;
int i = static_cast<int>(d); // 显式转换
```

#### nullptr

nullptr出现的目的是为了替代NULL。传统C++会把NULL、0 视为同一种东西，这取决于编译器如何定义 NULL，有些编译器会将NULL定义为 ((void*)0)，有些则会直接将其定义为0。

C++不允许直接将void \*隐式转换到其他类型。但如果编译器尝试把 NULL 定义为 ((void*)0)，那么在下面这句代码中：

```c++
char *ch = NULL;
```

没有了void *隐式转换的C++只好将NULL定义为 0。而这依然会产生新的问题，将NULL定义成0将导致C++中重载特性发生混乱。考虑下面这两个foo函数：

```c++
void foo(char*);
void foo(int);
```

那么foo(NULL); 这个语句将会去调用 foo(int)，从而导致代码违反直觉（**实际过程中这个语句不能编译**）。为了解决这个问题，C++11引入了nullptr关键字，专门用来区分空指针、0。而nullptr的类型为nullptr_t，能够隐式的转换为任何指针或成员指针的类型，也能和他们进行相等或者不等的比较。

#### constexpr

C++11提供了constexpr让用户显式的声明函数或对象构造函数在编译期会成为常量表达式，从C++14开始，constexpr函数可以在内部使用局部变量、循环和分支等简单语句。这将能增加程序的性能，因为调用函数会使用堆栈。

```c++
constexpr int len_foo_constexpr() {
    return 5;
}

int nums[len_foo_constexpr()] // 在编译期间这里会直接变成int nums[5]，而不是在运行期间
```

### 变量及其初始化

#### if/switch变量声明强化

c++17中可以在if/switch中声明临时变量：

```c++
// 将临时变量放到 if 语句内
if (const std::vector<int>::iterator itr = std::find(vec.begin(), vec.end(), 3);
    itr != vec.end()) {
    *itr = 4;
}
```

这和go很像

```go
if v, found := someMap["key"]; found {
    fmt.Println("Found:", v)
} else {
    fmt.Println("Not found")
}
```

#### 初始化列表

在C++11之前，初始化容器（如std::vector, std::map等）时，通常需要逐个插入元素。使用初始化列表（std::initializer_list）后，可以直接在容器创建时初始化所有元素，大大简化了代码。

```c++
std::vector<int> v = {1, 2, 3, 4, 5};
std::map<int, std::string> m = {{1, "one"}, {2, "two"}, {3, "three"}};
```

初始化对象：

```c++
class MagicFoo {
public:
    std::vector<int> vec;
    MagicFoo(std::initializer_list<int> list) {
        for (std::initializer_list<int>::iterator it = list.begin();
             it != list.end(); ++it)
            vec.push_back(*it);
    }
    void foo(std::initializer_list<int> list) {
        for (std::initializer_list<int>::iterator it = list.begin();
            it != list.end(); ++it) vec.push_back(*it);
    }
};
MagicFoo magicFoo = {1, 2, 3, 4, 5};
```

作为形参：

```c++
magicFoo.foo({6,7,8,9});
```

#### 结构化绑定

在go中函数可以返回多个相同/不同类型的值，而c++通常只能返回一个值（普遍的做法是传引用），c++11之前则可以通过std::pair返回两个值，c++11后新增了std::tuple 容器用于构造一个元组，进而囊括多个返回值。但缺陷是，C++11/14并没有提供一种简单的方法直接从元组中拿到并定义元组中的元素，尽管我们可以使用std::tie对元组进行拆包，但我们依然必须非常清楚这个元组包含多少个对象，各个对象是什么类型，非常麻烦。

C++17完善了这一设定，给出的结构化绑定可以让我们写出这样的代码：

```c++
#include <iostream>
#include <tuple>

std::tuple<int, double, std::string> f() {
    return std::make_tuple(1, 2.3, "456");
}

int main() {
    auto [x, y, z] = f();
    std::cout << x << ", " << y << ", " << z << std::endl;
    return 0;
}
```

### 类型推导

#### auto

auto就不说了，迭代器里面经常用，很好用。

#### decltype

decltype 关键字是为了解决 auto 关键字只能对变量进行类型推导的缺陷而出现的。它的用法和 typeof 很相似：

```c++
decltype(表达式)
```

#### 尾返回类型

c++14开始可以直接让普通函数具备返回值推导：

```c++
template<typename T, typename U>
auto add3(T x, U y){
    return x + y;
}
```
也可以用decltype(auto)，decltype(auto)的优势在于能够正确处理更复杂的类型推导场景，比如当函数返回一个变量的引用或者带有cv限定符的类型时。decltype(auto)会保留返回表达式的完整类型，包括其引用性和cv限定符，而auto则不会。

### 控制流

#### if constexpr

c++17后constexpr可以用在if语句中来优化性能。

#### 区间for迭代

这个就用的很多了，注意需要用引用来可写：

```c++
for (auto element : vec)
    std::cout << element << std::endl; // 只是拷贝，read only
for (auto &element : vec) {
    element += 1;                      // writeable
}
```

### 模板

实际开发中模板其实用的不多（除非造轮子写基础库

#### 外部模板

传统C++中，模板只有在使用时才会被编译器实例化。换句话说，只要在每个编译单元（文件）中编译的代码中遇到了被完整定义的模板，都会实例化。这就产生了重复实例化而导致的编译时间的增加。并且，我们没有办法通知编译器不要触发模板的实例化。

为此，C++11引入了外部模板，扩充了原来的强制编译器在特定位置实例化模板的语法，使我们能够显式的通知编译器何时进行模板的实例化：

template class std::vector<bool>;          // 强行实例化，通常是在定义模板或专门实例化模板的文件中
extern template class std::vector<double>; // 不在该当前编译文件中实例化模板，其他使用模板的文件中都应该声明

#### 类型别名模板

C++11使用using支持模板别名：

```c++
template<typename T>
using TrueDarkMagic = MagicType<std::vector<T>, std::string>;

int main() {
    TrueDarkMagic<bool> you;
}
```

#### 变长参数模板

在C++11之前，无论是类模板还是函数模板，都只能按其指定的样子， 接受一组固定数量的模板参数；而C++11加入了新的表示方法， 允许任意个数、任意类别的模板参数，同时也不需要在定义时将参数的个数固定。

```c++
template<typename... Ts> class Magic;
```

模板类 Magic 的对象，能够接受不受限制个数的 typename 作为模板的形式参数，例如下面的定义：

```c++
class Magic<int, std::vector<int>, std::map<std::string, std::vector<int>>> darkMagic;
```

既然是任意形式，所以个数为0的模板参数也是可以的：class Magic<> nothing;。

如果不希望产生的模板参数个数为 0，可以手动的定义至少一个模板参数：

```c++
template<typename Require, typename... Args> class Magic;
```

变长参数模板也能被直接调整到到模板函数上。除了在模板参数中能使用...表示不定长模板参数外， 函数参数也使用同样的表示法代表不定长参数， 这也就为我们简单编写变长参数函数提供了便捷的手段，例如：

```c++
template<typename... Args> void printf(const std::string &str, Args... args);

// 计算参数个数可用以下办法：
template<typename... Ts>
void magic(Ts... args) {
    std::cout << sizeof...(args) << std::endl;
}

// 展开
template<typename T0, typename... T>
void printf2(T0 t0, T... t) {
    std::cout << t0 << std::endl;
    if constexpr (sizeof...(t) > 0) printf2(t...);
}
```

#### 折叠表达式

```c++
#include <iostream>
template<typename ... T>
auto sum(T ... t) {
    return (t + ...);
}
int main() {
    std::cout << sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10) << std::endl;
}
```

#### 非类型模板参数

类型模板参数：

```c++
template <typename T, typename U>
auto add(T t, U u) {
    return t+u;
}
```

非类型模板参数：

```c++
template <typename T, int BufSize>
class buffer_t {
public:
    T& alloc();
    void free(T& item);
private:
    T data[BufSize];
}

buffer_t<int, 100> buf; // 100 作为模板参数
```

C++17可以使用auto关键字，让编译器辅助完成具体类型的推导：

```c++
template <auto value> void foo() {
    std::cout << value << std::endl;
    return;
}

int main() {
    foo<10>();  // value 被推导为 int 类型
}
```

### 面向对象

#### 委托构造

C++11引入了委托构造的概念，这使得构造函数可以在同一个类中一个构造函数调用另一个构造函数：

```c++
#include <iostream>
class Base {
public:
    int value1;
    int value2;
    Base() {
        value1 = 1;
    }
    Base(int value) : Base() { // 委托 Base() 构造函数
        value2 = value;
    }
};
```

#### 继承构造

```c++
#include <iostream>
class Base {
public:
    int value1;
    int value2;
    Base() {
        value1 = 1;
    }
    Base(int value) : Base() { // 委托 Base() 构造函数
        value2 = value;
    }
};
class Subclass : public Base {
public:
    using Base::Base; // 继承构造
};
```

#### 显示虚函数构造

**override**

当重载虚函数时，引入override关键字将显式的告知编译器进行重载，编译器将检查基函数是否存在这样的其函数签名一致的虚函数，否则将无法通过编译：

```c++
struct Base {
    virtual void foo(int);
};
struct SubClass: Base {
    virtual void foo(int) override; // 合法
    virtual void foo(float) override; // 非法, 父类没有此虚函数
};
```

**final**

final则是为了防止类被继续继承以及终止虚函数继续重载引入的。

```c++
struct Base {
    virtual void foo() final;
};
struct SubClass1 final: Base {
}; // 合法

struct SubClass2 : SubClass1 {
}; // 非法, SubClass1 已 final

struct SubClass3: Base {
    void foo(); // 非法, foo 已 final
};
```

#### 显式禁用默认函数

c++11允许显式的声明采用或拒绝编译器自带的函数（构造函数、析构函数、复制构造和赋值运算符）。

```c++
class Magic {
    public:
    Magic() = default; // 显式声明使用编译器生成的构造
    Magic& operator=(const Magic&) = delete; // 显式声明拒绝编译器生成构造
    Magic(int magic_number);
}
```

#### 强类型枚举

C++11 入了枚举类（enumeration class），并使用enum class的语法进行声明：

```c++
enum class new_enum : unsigned int {
    value1,
    value2,
    value3 = 100,
    value4 = 100
};
```

这样定义的枚举实现了类型安全，首先他不能够被隐式的转换为整数，同时也不能够将其与整数数字进行比较， 更不可能对不同的枚举类型的枚举值进行比较。但相同枚举值之间如果指定的值相同，那么可以进行比较。望获得枚举值的值时，将必须显式的进行类型转换，不过我们可以通过重载<<来进行输出。