#### C++和Java的区别

- java语法更简洁，通过jvm可以实现一次编码，到处运行；而C++则需要针对不同的平台系统进行编译
- java没有指针的概念
- java有gc
- c++底层

#### struct和class的区别

- struct和class都有成员函数，共有和私有部分，任何用class完成的工作，都可以同struct完成
- 不对成员指定公私有，struct默认是公有，class默认是私有；类似的，struct默认是共有继承，class是私有继承

C++和C中struct的区别：

- c++中的struct可以作为类的特例，可以有访问权限，可以有成员函数，可以继承，可以实现多态

#### define宏定义和const的区别

- define在预处理的时候起作用，只进行替换，不做检查，最好加上一个大括号包住全部内容，不然容易出错
- const有数据类型，编译器可以进行类型安全检查
- 宏定义的数据由于是替换，不分配内存空间；const定义的是值不能改变，要分配内存空间
- 最好是用const替换define，出错了方便debug

#### C++中const和static的作用

const声明变量为常量，初始化后就不能修改：

- 修饰变量
- 修饰指针：常量指针（指针是常量，const在\*后面），指针常量（指针指向的是常量，const在\*前面）
- 修饰成员函数：表示这个函数不会修改类成员变量

static：

- 修饰局部变量，使变量值可以在函数调用之间持久化
- 修饰全局变量，使得作用域只能在声明它的文件内
- 修饰类的成员，使成员属于类本身，也就是所有类对象共享一个成员
- 修饰类的成员函数，使得函数可以在没有类实例的情况被调用，只可以访问类的静态成员
- 单例模式，通过局部静态变量实现线程安全的单例模式（C++11之后，规定局部静态变量的线程安全初始化）

```c++
class Singleton {
private:
    // 私有构造函数，防止外部构造
    Singleton() {};
    // 禁止拷贝构造
    Singleton(const Singleton& other) = delete;
    // 禁止拷贝赋值运算符
    Singleton& operator=(const Singleton& other) = delete;
 public:
    // 全局访问点
    static Singleton& getInstance() {
        static Singleton instance; // 局部静态变量
        return instance;
    }
}

int main() {
    Singleton& s = Singleton::getInstance();
}
```

#### C++的顶层const和底层const

常量指针：顶层const

指针常量：底层const

#### 数组名和指针（指向数组首元素的地址）区别

- 都可以通过增减偏移量来访问数组中的元素
- 数组名不是真正意义上的指针，可以看作数组首元素的地址
- 数组名不可以赋值，指针可以赋值更加灵活
- 数组名作为形参进行传递，退化成了一般指针，可以自增、自减，sizeof大小也变了

#### final和override关键字

C++11中被引入

final：

- 修饰类，表示该类不能被继承，防止类的进一步派生
- 修饰虚函数表示，该虚函数在当前类是最终实现，不能在任何派生类中被重写

override：

- 只用于虚函数，明确指出需要重写基类中的一个虚函数，有助于编译器检查函数签名是否匹配基类中的一个虚函数

#### 拷贝初始化和直接初始化

- 直接初始化，通常是()，可以调用explicit构造函数，更高效，允许直接的对象构造
- 拷贝初始化，通常是=，只能调用非explicit构造函数，会分配一个临时对象，再使用拷贝构造函数

```c++
string str1("I am a string");//语句1 直接初始化
string str2(str1);//语句2 直接初始化，str1是已经存在的对象，直接调用拷贝构造函数对str2进行初始化
string str3 = "I am a string";//语句3 拷贝初始化，先为字符串”I am a string“创建临时对象，再把临时对象作为参数，使用拷贝构造函数构造str3
string str4 = str1;//语句4 拷贝初始化，这里相当于隐式调用拷贝构造函数，而不是调用赋值运算符函数
```

#### 初始化和赋值的区别

- 初始化发生在对象的创建，为成员分配初始值，比如构造函数完成，也可以初始化列表或直接在类定义中为成员指定默认值
- 赋值发生在对象存在之后，改变其内容，涉及赋值运算符=
- 对于简单数据类型，两者没什么区别
- 对于类和复杂数据类型，可能有区别，比如去重载赋值运算符

#### extern “C”

加上后可以正确的调用C语言的代码，相当于告诉编译器这部分代码是C写的，按照C语言进行编译。

这个语句一般位于.h头文件或cpp文件（.c文件不支持）

#### extern的作用

- 在多个文件中使用同一个全局变量时，你可以在一个文件中定义该变量，并在其他文件中使用 `extern` 来声明它，以便使用。这样做可以避免多重定义错误，并确保所有文件中的变量都引用同一个内存位置。
- extern “C”

#### 野指针和悬空指针

野指针：没有初始化过的指针，解决办法：使用指针最好都初始化或为nullptr

```c++
int main(void) { 
    
    int* p;     // 未初始化
    std::cout<< *p << std::endl; // 未初始化就被使用
    
    return 0;
}
```

悬空指针：

- 指针指向的对象被删除或释放，比如使用delete删除了一个动态分配的对象，但指向该对象的指针任然存在
- 函数返回局部变量的地址
- 指针未初始化

```c++
int main(void) { 
  int * p = nullptr;
  int* p2 = new int;
  
  p = p2;

  delete p2;
}
// p和p2就是悬空指针，需要如下设置
// p = p2 = nullptr
```

解决办法：

- 及时设置为nullptr
- 使用智能指针自动管理内存
- 避免返回局部变量的地址

#### C和C++的类型安全

什么是类型安全：编译时能够确保类型的正确使用，避免类型错误冲突的运行时错误

C语言相对较少类型安全，允许广泛的类型转换，容易出错

C++类型安全更多，比如：

- 强类型检查，编译时更严格的类型检查，函数重载参数必须明确
- 类型转换符：C++ 提供了 `static_cast`、`dynamic_cast`、`const_cast` 和 `reinterpret_cast`，使类型转换更明确和安全
- 智能指针
- 模板提供了编译时的类型检查

#### C++中的重载、重写（覆盖）和隐藏

重载：函数名相同，但是参数类型和数目不同，不能仅依靠返回值不同来区分，和是否是虚函数无关

重写：在派生类中重写基函数，函数名，参数类型和个数，返回值都得一样

重载和重写：

- 重载是不同函数之间的水平关系，重写是父类和子类的垂直关系
- 参数，返回值不同
- 重写根据调用的类型确定，重载根据形参和实参确定

隐藏：派生类的函数隐藏了基类的同名函数。比如基类函数不是虚函数；或者两个函数参数不同，不管是不是虚函数，都会被隐藏。

```c++
// 父类
class A {
public:
    virtual void fun(int a) { // 虚函数
        cout << "This is A fun " << a << endl;
    }  
    void add(int a, int b) {
        cout << "This is A add " << a + b << endl;
    }
};

// 子类
class B: public A {
public:
    void fun(int a) override {  // 覆盖
        cout << "this is B fun " << a << endl;
    }
    void add(int a) {   // 隐藏
        cout << "This is B add " << a + a << endl;
    }
};

int main() {
    // 基类指针指向派生类对象时，基类指针可以直接调用到派生类的覆盖函数，也可以通过 :: 调用到基类被覆盖
    // 的虚函数；而基类指针只能调用基类的被隐藏函数，无法识别派生类中的隐藏函数。

    A *p = new B();
    p->fun(1);      // 调用子类 fun 覆盖函数
    p->A::fun(1);   // 调用父类 fun
    p->add(1, 2);
    // p->add(1);      // 错误，识别的是 A 类中的 add 函数，参数不匹配
    // p->B::add(1);   // 错误，无法识别子类 add 函数
    return 0;
}
```

#### C++有哪几种构造函数

- 默认构造函数：没有任何参数
- 参数化构造函数：接受参数
- 拷贝构造函数：ClassName(const ClassName& other)
- 移到构造函数：接受一个同类型对象的右值引用作为参数。用于支持将一个临时对象的资源“移动”到一个新对象中，而不是复制。形式通常为 `ClassName(ClassName&& other)`
- 委托构造函数：同一个类中的一个构造函数调用另一个构造函数
- 继承构造函数：C++11，允许从基类继承构造函数

#### 深拷贝和浅拷贝

浅拷贝：只拷贝一个指针，没有新开辟一个地址，拷贝的指针的原来的指针指向同一个地址，如果原来指针指向的资源释放了，再释放浅拷贝指针的资源就会出现错误。

深拷贝：拷贝值，并且开辟一块新的空间来存放，即使原来的对象不存在，也不会对深拷贝的值有影响。

```c++
#include <iostream>  
#include <string.h>
using namespace std;
 
class Student
{
private:
	int num;
	char *name;
public:
	Student(){
        name = new char(20);
		cout << "Student" << endl;
    };
	~Student(){
        cout << "~Student " << &name << endl;
        delete name;
        name = NULL;
    };
	Student(const Student &s){//拷贝构造函数
        //浅拷贝，当对象的name和传入对象的name指向相同的地址
        name = s.name;
        //深拷贝
        //name = new char(20);
        //memcpy(name, s.name, strlen(s.name));
        cout << "copy Student" << endl;
    };
};
 
int main()
{
	{// 花括号让s1和s2变成局部对象，方便测试
		Student s1;
		Student s2(s1);// 复制对象
	}
	system("pause");
	return 0;
}
//浅拷贝执行结果：
//Student
//copy Student
//~Student 0x7fffed0c3ec0
//~Student 0x7fffed0c3ed0
//*** Error in `/tmp/815453382/a.out': double free or corruption (fasttop): 0x0000000001c82c20 ***

//深拷贝执行结果：
//Student
//copy Student
//~Student 0x7fffebca9fb0
//~Student 0x7fffebca9fc0
```

#### 内联函数（inline）和宏定义

宏在预处理阶段做简单替换，内联函数可以在编译时进行类型检查。

内联函数在编译时直接将函数代码嵌入，省去函数调用开销。

宏不方便debug，并且需要用{}括起来，否则容易用歧义，内联函数则不会，使用宏的地方都可以使用inline。

```c++
#include <iostream>

// 使用inline关键字定义内联函数
inline int max(int x, int y) {
    return (x > y) ? x : y;
}

int main() {
    int a = 5;
    int b = 10;

    // 调用内联函数
    std::cout << "The maximum of " << a << " and " << b << " is " << max(a, b) << std::endl;

    return 0;
}
```

#### public，private和protected

public：类的内部外部都可以访问

private：只能类内部访问、友元函数或友元类访问

protected：类的内部和其派生类中访问

继承：

- public：如果一个类以`public`方式继承另一个类，基类的`public`成员在派生类中仍然是`public`，`protected`成员在派生类中仍然是`protected`，而`private`成员仍然是不可访问的。
- private：如果一个类以`private`方式继承另一个类，基类的`public`和`protected`成员都会成为派生类的`private`成员，而基类的`private`成员在派生类中仍然是不可访问的。
- protected：如果一个类以`protected`方式继承另一个类，基类的`public`和`protected`成员都会成为派生类的`protected`成员，而基类的`private`成员仍然是不可访问的。

#### 如何用代码判断大小端存储

大端存储：数据的高字节存储在低地址

小端存储：数据的低字节存储在低地址

x86架构一般是小端存储，arm和mips大小端都支持。

而网络传输使用大端存储，即网络字节顺序，这是一种约定，因此使用socket编程需要转换，c和c++提供了一些函数。

- htonl()：将主机字节顺序的无符号长整型转换为网络字节顺序。
- htons()：将主机字节顺序的短整型转换为网络字节顺序。
- ntohl()：将网络字节顺序的无符号长整型转换为主机字节顺序。
- ntohs()：将网络字节顺序的短整型转换为主机字节顺序。

可以使用强制类型转换判断：

```c++
#include <iostream>
using namespace std;
int main()
{
    int a = 0x1234;
    unsigned char c = (unsigned char)(a);  // 使用 unsigned char 以避免符号问题
    if (c == 0x12)
        cout << "big endian" << endl;
    else if (c == 0x34)
        cout << "little endian" << endl;
}
```

#### volatile、mutable和explicit

volatile：防止编译器对变量的访问进行优化，确保每次读取或写入都对应原始内存地址

mutable：放宽类中const函数的限制，const函数保证不会修改类成员变量，有时候需要修改一些类成员，可以加上mutable，常用于需要修改的是类的内部状态，不影响外部可观察行为。

explicit：防止C++隐式类型转换

```c++
class MyClass {
public:
    explicit MyClass(int a) {
        // Constructor code
    }
};

void func(MyClass m) {
    // Function code
}

int main() {
    MyClass obj = MyClass(10); // 正确: 显式调用
    // MyClass obj2 = 10;       // 错误: 不能隐式转换
    func(MyClass(20));         // 正确: 显式调用
    // func(20);                // 错误: 不能隐式转换
}
```

#### 什么情况会调用拷贝构造函数

1. 用类的实例化对象去初始化另一个对象
2. 函数的参数是类的对象（非引用传递）

