#### C++有几种类型的new

- plain new：最普通的new，也就是常用的new，如果内存空间分配失败，会panic，需要catch捕捉异常
- nothrow new：内存空间分配失败的情况下不抛出异常，返回nullptr
- placement new：允许在已经分配的内存上构造对象

```c++
// nothrow new
#include <new>  // 必须包含这个头文件

void* place = ...; // 指向预先分配好的内存
MyClass* myObject = new(place) MyClass(arguments);

// placement new
#include <iostream>
#include <string>
using namespace std;

int main()
{
	char *p = new(nothrow) char[10e11];
	if (p == NULL) 
	{
		cout << "alloc failed" << endl;
	}
	delete p;
	return 0;
}
//运行结果：alloc failed
```

#### C++异常处理的方法

常见的异常：

- 数组下标越界
- 除数为0
- 动态分配空间不足

异常处理：try、throw和catch

```c++
#include <iostream>
using namespace std;
int main()
{
    double m = 1, n = 0;
    try {
        cout << "before dividing." << endl;
        if (n == 0)
            throw - 1;  //抛出int型异常
        else if (m == 0)
            throw - 1.0;  //拋出 double 型异常
        else
            cout << m / n << endl;
        cout << "after dividing." << endl;
    }
    catch (double d) {
        cout << "catch (double)" << d << endl;
    }
    catch (...) {
        cout << "catch (...)" << endl;
    }
    cout << "finished" << endl;
    return 0;
}
//运行结果
//before dividing.
//catch (...)
//finished
```

先执行try，如果没有发生异常，不会进入catch，否则throw出异常，catch进行捕获。

catch(...)表示捕获任何异常，catch里面还可以throw通知上一层调用者。

还可以通过异常类

#### 形参和实参

形参就是函数定义声明时那个变量，只有在调用时才为其分配内存单元，调用结束释放内存单元，也就是只在函数内部有效。

实参就是调用函数时，传递给形参的变量，做一次拷贝，需要与形参相匹配。如果不是指针参数，相当于是两个变量。

#### 值传递、指针传递和引用传递

值传递：对实参对象做一次拷贝，赋值给形参，大小根据参数类型确定，不会修改原始数据。

指针传递：只对地址做一次拷贝，大小为固定的地址大小，通过指针可以对原始数据进行修改。

引用传递：不涉及数据拷贝，是原始数据的一个直接别名。

指针传递和引用传递效率比值传递高，更推荐引用传递，高效并且语义更好。

#### 静态变量什么时候初始化

初始化只有一次，赋值可以有多次。

- 全局静态变量，它会在程序开始时初始化。
- 局部静态变量：如果你在函数内部定义了一个静态变量，它会在该函数的第一次调用时在该变量首次使用的地方初始化。

#### const关键字的作用

1. 阻止一个变量被改变，使用const关键字定义变量通常需要对其初始化。
2. 常量指针，指针常量
3. 修饰函数的形参，避免这个参数被改变
4. 修饰类的成员函数，表面这个函数不会对成员变量进行修改
5. 修饰返回值，避免返回一个左值
6. const对象只能调用const成员函数
7. const变量可以通过const_cast转换为非const类型

#### 什么是类的继承

首先类和类之间的关系：

1. has-a，类的类成员是另外一个类
2. use-a，通过成员函数
3. is-a，继承，具有传递性

继承就是一个类继承了另外一个类的属性和方法，子类/派生类，父类/基类，子类对象可以当作父类对象使用。

#### 从汇编层面去解释一下引用

引用相对于指针更加安全，为什么更加安全，比如野指针和空指针。

引用就是原来变量的别名，地址是相同的。引用必须在定义时初始化，并且不能重新指向。

#### delete p、delete []p、allocator的作用

- delete p：释放new 分配的单个对象
- delete []p：释放new分配的数组的内存

delete除了释放内存，还会调用对象的析构函数

allocator是stl容器的默认内存管理工具

#### new/delete的实现原理，delete如何知道释放内存的大小

new：

- 分配内存：调用malloc为对象分配足够的内存，除了对象本身需要的空间，还包括额外的元数据，比如对象的大小和类型
- 调用构造函数：在分配的内存上调用对象的构造函数

delete：

- 调用对象的析构函数
- 释放内存：调用free来释放对象所占用的内存
- new内存分配时会存储对象大小的元数据，也得看编译器的实现

#### malloc申请的内存能用delete释放吗

malloc需要使用free配套使用，需要明确的大小，不能用在动态类，并且不会执行析构函数。

#### malloc和free的原理

malloc：

- 小于128KB，使用brk()，移动堆顶指针
- 大于128KB，使用mmap系统调用，在文件映射区进行私有匿名映射，私有表示只能这个进程访问，匿名表示和磁盘文件无关
- 申请内存是申请虚拟内存，第一次访问会发生缺页中断，然后分配物理内存
- 使用brk申请的内存不会立刻还给操作系统，会存起来下次再用，但容易产生内存碎片，因为分配的内存是连续的
- 而mmap申请的内存则会立刻还给操作系统，因此也更容易发生缺页中断

#### malloc、realloc、calloc的区别

名字可以区分

malloc：需要手动计算，成功返回分配内存的指针，失败返回NULL，分配的内存内容没有初始化，可能包含任意数据

```c++
void* malloc(size_t size);
```

calloc：需要指定每个元素的大小和数量，更方便计算大小，成功和失败返回和malloc一致，会对分配的内存区域初始化为零

```c++
void* calloc(size_t num, size_t size);
```

realloc：重新调整分配的内存大小，成功和失败返回和malloc一致

- 如果 `new_size` 大于原始大小，新分配的部分不会被初始化。
- 如果 `new_size` 小于原始大小，可能会丢失超出新大小部分的数据。
- 如果 `ptr` 是 `NULL`，`realloc` 的行为类似于 `malloc(new_size)`。

```c++
void* realloc(void* ptr, size_t new_size);
```

#### 类成员初始化的方式，构造函数执行顺序，为什么用成员初始化列表会更快

初始化：

- 成员列表初始化：更推荐，会在对象的内存分配后，构造函数体执行前初始化成员变量，可以直接调用成员的构造函数来初始化成员
- 构造函数体内赋值初始化：先默认构造函数后再赋值（拷贝构造）

为什么更快：成员列表初始化少一次调用类的默认构造函数，对于内置类型没有差别，但为了保持写法相同也采用成员列表初始化。

执行顺序：

1. 基类构造函数
2. 成员变量初始化（按照类声明顺序，而非成员初始化列表中顺序）
3. 构造函数体

#### 哪些情况必须用到成员列表初始化，作用是什么

因为成员列表初始化是分配内存后就初始化成员变量，在构造函数体之前；而构造函数体赋值则是先构造再初始化赋值，因此考虑必须在定义时初始化的成员：

1. const
2. 引用
3. 调用基类的非默认构造函数，也就是这个构造函数有参数

```c++
class Base {
public:
    Base(int x) {}
};

class Derived : public Base {
public:
    Derived(int x) : Base(x) {}
};
```

1. 有个成员是另外一个类，需要调用他的非默认构造函数

```c++
class Member {
public:
    Member(int x) {}
};

class Container {
    Member m;
public:
    Container(int x) : m(x) {}
};
```

#### string和char \*

string对char \*进行了封装：char \*，容量，长度；可以动态扩展（申请原空间两倍的空间，再拷贝过去，增加新的内容），更安全
