#### 什么是内存泄露，如何检测和避免

内存泄露一般指堆内存的泄露，对于没有GC的语言，比如C/C++，需要程序员去管理这部分内存的申请和释放，如果用完忘记释放，就会导致这块内存不可用，导致内存泄露。

如何避免：

- 使用new/malloc的时候，要注意使用成对的delete/free

- 使用智能指针

- 使用继承的时候，将基类的析构函数设置为虚函数，这样不管是使用基类或派生类的对象进行删除，都会触发正确的析构过程，先派生类，后基类。否则只会触发基类的析构函数。

  ```c++
  #include <iostream>
  
  class Base {
  public:
      virtual ~Base() { std::cout << "Base destructor\n"; }
  };
  
  class Derived : public Base {
  private:
      int* data;
  public:
      Derived() : data(new int(42)) { std::cout << "Derived constructor\n"; }
      ~Derived() {
          std::cout << "Derived destructor\n";
          delete data;
      }
  };
  
  int main() {
      Base* b = new Derived();
      delete b;  // 正确调用Derived的析构函数，然后是Base的析构函数
      return 0;
  }
  ```

  > 构造函数是先基类->派生类；析构函数是先派生类->基类；主要是派生类可能会基类的资源

检测工具：

- Valgrind

#### 对象复用了解吗，零拷贝呢

对象复用就是提前创建一批资源，然后存储到资源池，实现重复利用，避免频繁的创建释放开销。比如线程池、sql连接池，并发互斥。

零拷贝：减少CPU搬运数据

- DMA之前：CPU需要将数据从设备缓冲区拷贝到内核缓冲区，再到用户缓冲区
- DMA之后：每个设备都有自己的DMA，会将数据拷贝到内核缓冲区
- 共享内存，sendfile（直接将源地址到目标地址，减少一次到用户缓冲区）

vector中的emplace_back()就用了零拷贝的思路，减少不必要的拷贝；会将插入的元素直接在容器空间内的原地构造，不需要触发拷贝构造和转移构造（push_back则需要）

```c++
#include <vector>
#include <string>
#include <iostream>
using namespace std;

struct Person
{
    string name;
    int age;
    //初始构造函数
    Person(string p_name, int p_age): name(std::move(p_name)), age(p_age)
    {
         cout << "I have been constructed" <<endl;
    }
     //拷贝构造函数
     Person(const Person& other): name(std::move(other.name)), age(other.age)
    {
         cout << "I have been copy constructed" <<endl;
    }
     //转移构造函数
     Person(Person&& other): name(std::move(other.name)), age(other.age)
    {
         cout << "I have been moved"<<endl;
    }
};

int main()
{
    vector<Person> e;
    cout << "emplace_back:" <<endl;
    e.emplace_back("Jane", 23); //不用构造类对象

    vector<Person> p;
    cout << "push_back:"<<endl;
    p.push_back(Person("Mike",36));
    return 0;
}
//输出结果：
//emplace_back:
//I have been constructed
//push_back:
//I have been constructed
//I am being moved.
```

#### 面向对象的特性，并举例

1. 继承：子类继承父类的属性和方法，比如人作为一个基类，拥有基本的成员比如器官，基本的方法吃饭睡觉等；到更具体的一类人，就可以继承人，然后再加上独特的成员和方法
2. 封装：将客观食物抽象成具体的类，类可以通过private、public和protected做访问控制
3. 多态：同一个事物对不同的消息展现出不同的表现，或者说允许将子类的指针赋值给父类的指针
   1. 重载（overload）：同样的函数名，但是参数类型和数量不同（不能只通过返回值不同，但返回值可以不同），编译时多态
   2. 覆盖（override）：虚函数，在子类中重新定义

#### C++的四种强制转换

都会在编译时进行检查

1. static_cast：最常用，执行非多态类型的转换，在相关类型之间进行转换，比如整型和浮点型

```c++
int a = 10;
double b = static_cast<double>(a);  // 将 int 转换为 double
```

2. dynamic_cast：处理多态类型，可以在类的继承体系中安全向下转换，比如基类向派生类转换，但要求基类至少有一个虚函数

```c++
class Base { virtual void dummy() {} };
class Derived : public Base { int a; };

Base* base = new Derived();
Derived* derived = dynamic_cast<Derived*>(base);  // 合法的向下转换
```

3. const_cast：修改类型的const或volatile属性（禁止编译器对变量进行优化，直接从内存地址读取）

```c++
const int a = 10;
int* pa = const_cast<int*>(&a);  // 去除常量性
*pa = 20;  // 实际上这样做是未定义行为，因为a是常量
```

4. reinterpret_cast：用于低级别的、不安全的类型重新解释

```c++
int* p = new int(10);
char* pc = reinterpret_cast<char*>(p);  // 将 int* 转换为 char*
```

#### C++函数调用的压栈过程

```c++
#include <iostream>
using namespace std;

int f(int n) 
{
	cout << n << endl;
	return n;
}

void func(int param1, int param2)
{
	int var1 = param1;
	int var2 = param2;
	printf("var1=%d,var2=%d", f(var1), f(var2));//如果将printf换为cout进行输出，输出结果则刚好相反
}

int main(int argc, char* argv[])
{
	func(1, 2);
	return 0;
}
//输出结果
//2
//1
//var1=1,var2=2
```

1. 程序从main函数开始执行，编译器将**操作系统运行状态，main函数的返回地址，main函数的参数，main函数中的变量**依次压栈。
2. main调用func()，编译器将**main函数的状态、func函数的返回地址、func函数的参数从右到左、func函数定义的变量**依次压栈。
3. main函数调用f()，编译器将**func函数的状态，f函数的返回地址、f函数的参数从右到左、f定义的变量依次压栈**。

从代码可以看出，f(var1)、f(var2)依次入栈，先执行f(var2)，再执行f(var1)，最后打印整个字符串，栈中的变量依次弹出，主函数返回。

#### 函数调用为什么使用栈，队列不行吗

栈是后进先出的，这种结构特点十分适合函数调用和递归，确保了最后调用的函数最先返回，再压栈的时候对函数的返回地址、函数的参数、函数的变量依次压栈，函数执行完毕后，会依次出栈，回到函数被调用的地方。

队列是先进先出，与函数需求不符，并且队列管理更加复杂。

#### coredump，怎么调试

coredump是由异常退出或终止，比如段错误生成的core文件，这个core文件会记录程序运行时的内存、寄存器状态、内存指针和堆栈等信息，可以使用gdb进行定位调试。

```c++
#include<stdio.h>
int main(){
    int i;
    scanf("%d",i);//正确的应该是&i,这里使用i会导致segment fault
    printf("%d\n",i);
    return 0;
}
```

```shell
g++ coredumpTest.cpp -g -o coredumpTest
./coredumpTest
gdb [可执行文件名] [core文件名]
```

#### 移动构造函数

比如用对象a初始化对象b，a的作用仅是初始化，后续不在使用b，使用拷贝构造函数会把a的内容拷贝到b中。但由于a后续不再使用，那么可以直接使用a的空间来初始化b，于是有了移动构造函数。

拷贝构造函数的参数是一个左值引用，移动构造函数的参数是右值或将亡值的引用，换句话说只有用右值或将亡值的初始化另一个对象时，才会调用移动构造函数，move语句用于将一个左值变成一个将亡值。

#### C++将临时变量作为返回值时的处理过程

函数退出时，临时变量出栈被销毁，返回值会存储到寄存器中，与临时变量的生命周期没有关系。通常步骤如下：

1. **临时变量的构造**：在函数内部，临时变量被构造。
2. **返回值的拷贝**：在函数返回时，临时变量需要被拷贝到返回值中。这可能涉及到调用拷贝构造函数或移动构造函数。
3. **销毁临时变量**：一旦临时变量的内容被拷贝（或移动）到返回位置，该临时变量就会被销毁，即其析构函数被调用。
4. **使用返回值**：调用者接收返回值。如果涉及到进一步的拷贝或移动，可能会有额外的构造和析构发生。

但编译器会进行优化，比如返回值优化：

1. 直接构造：在返回值的存储位置直接构造临时变量，而不是在函数内部构造然后拷贝或移动到返回位置。
2. 无需拷贝/移动：通过这种方式，可以避免调用拷贝构造函数或移动构造函数。
3. 直接使用：函数返回后，调用者可以直接使用这个已经构造好的对象。

#### 如何获得结构成员相对于结构开头的字节偏移量

使用<stddef.h>中的offsetof宏

```c++
#include <iostream>
#include <stddef.h>
using namespace std;

struct  S
{
	int x;
	char y;
	int z;
	double a;
};
int main()
{
	cout << offsetof(S, x) << endl; // 0
	cout << offsetof(S, y) << endl; // 4
	cout << offsetof(S, z) << endl; // 8
	cout << offsetof(S, a) << endl; // 16
	return 0;
}
```

#### 静态类型和动态类型，静态绑定和动态绑定

静态类型：对象声明时采用的类型，编译期已确定

动态类型：一个指针或引用目前所指对象的类型，运行期确定

静态绑定：绑定的是静态类型，对应的函数或属性依赖于对象的静态类型，发生在编译器

动态绑定：绑定的是动态类型，对应的函数或属性依赖于对象的动态类型，发生在运行期

一般来说对象非虚函数都是静态绑定，虚函数是动态绑定

```c++
#include <iostream>
using namespace std;

class A
{
public:
	/*virtual*/ void func() { std::cout << "A::func()\n"; }
};
class B : public A
{
public:
	void func() { std::cout << "B::func()\n"; }
};
class C : public A
{
public:
	void func() { std::cout << "C::func()\n"; }
};
int main()
{
	C* pc = new C(); //pc的静态类型是它声明的类型C*，动态类型也是C*；
	B* pb = new B(); //pb的静态类型和动态类型也都是B*；
	A* pa = pc;      //pa的静态类型是它声明的类型A*，动态类型是pa所指向的对象pc的类型C*；
	pa = pb;         //pa的动态类型可以更改，现在它的动态类型是B*，但其静态类型仍是声明时候的A*；
	C *pnull = NULL; //pnull的静态类型是它声明的类型C*,没有动态类型，因为它指向了NULL；
    
    pa->func();      //A::func() pa的静态类型永远都是A*，不管其指向的是哪个子类，都是直接调用A::func()；
	pc->func();      //C::func() pc的动、静态类型都是C*，因此调用C::func()；
	pnull->func();   //C::func() 不用奇怪为什么空指针也可以调用函数，因为这在编译期就确定了，和指针空不空没关系；
	return 0;
}
```

#### 引用能否实现动态绑定，为什么

可以的，虚函数。

```c++
#include <iostream>
using namespace std;

class Base 
{
public:
	virtual void  fun()
	{
		cout << "base :: fun()" << endl;
	}
};

class Son : public Base
{
public:
	virtual void  fun()
	{
		cout << "son :: fun()" << endl;
	}
    // 非虚函数，b中无法调用
	void func()
	{
		cout << "son :: not virtual function" <<endl;
	}
};

int main()
{
	Son s;
	Base& b = s; // 基类类型引用绑定已经存在的Son对象，引用必须初始化
	s.fun(); //son::fun()
	b.fun(); //son :: fun()
	return 0;
}
```

#### 全局变量和局部变量的区别

作用域不同，一个是整个程序都可以用，一个是在局部，比如{}，两者都是离开其作用域即销毁.

全局变量在main函数执行前就被初始化，在.data段，局部变量则是运行过程在被加载，在堆栈。

#### 指针加减需要注意什么

不要让指针指向一块未知的内存地址，指针运算转换为10进制，加减是对应个数的指针类型的长度。

```c++
#include <iostream>
using namespace std;

int main()
{
	int *a, *b, c;
	a = (int*)0x500;
	b = (int*)0x520;
	c = b - a;
    /*
    在 C++ 中，两个指针相减的结果是它们之间的元素数量。由于这里的指针都是 int*，指向整数，每个整数通常占用 4 个字节（这取决于平台）。因此，地址差 0x520 - 0x500 等于 32（十六进制的 20），除以每个整数的大小 4 字节，得到 8。这是指针之间的整数元素数量。
    */
	printf("%d\n", c); // 8
	a += 0x020;
	c = b - a;
	printf("%d\n", c); // -24
	return 0;
}
```

#### 如何判断两个浮点数是否相等

不能直接用==来比较两个浮点数是否相等，浮点数的计算涉及到精度问题和舍入误差，因此判断方法是看这两个浮点数的差值是否足够小，并且在某个误差范围内。

```c++
#include <cmath> // 引入数学库以使用fabs函数

bool areAlmostEqual(double a, double b, double epsilon = 1e-9) {
    return std::fabs(a - b) < epsilon;
}
```

#### 指针参数传递和引用参数传递

指针参数传递：拷贝实参的地址，对指针的改变不会改变实参（想改变用指针的指针或引用），解引用会改变实参的值

引用参数传递：实参的别名，任何改变都会影响到实参

#### 类如何实现只能静态分配和只能动态分配

静态分配：编译器为对象在栈空间分配内存

动态分配：使用new为对象在堆空间中分配内存

**只能静态分配：将new和delete运算符重载为private属性**

**只能动态分配：构造函数和析构函数设置为private或protected，再提高一个静态方法来创建对象**

#### 想使用某个类作为基类，为什么基类必须定义而非声明

派生类需要继承基类的属性和方法，为了使用这些成员，基类必须定义

#### 继承机制中对象如何转换？指针和引用之间如何转换

1. 向上转换，定义一个派生类的指针或引用再转换为基类指针，会自动进行，这是安全的
2. 向下转换，将基类指针或引用转换为派生类指针或引用，不会自动进行，因为不知道对应哪个派生类，需要使用dynamic_cast

