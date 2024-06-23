#### int main(int argc, cha* argv[])

argc：参数个数

argv：存储参数，第一个参数为程序名称

#### 如果有一个空类，它会默认添加哪些函数

1. 默认构造函数
2. 拷贝构造函数
3. 赋值运算符
4. 析构函数

#### const char*和string

string：c++标准库、封装了对字符串的操作，是类，长度自动扩展

char*：c风格字符串，以'\0'结尾，长度限定

```c++
a)  string转const char* 

string s = “abc”; 

const char* c_s = s.c_str(); 

b)  const char* 转string，直接赋值即可 

const char* c_s = “abc”; 
 string s(c_s); 

c)  string 转char* 
 string s = “abc”; 
 char* c; 
 const int len = s.length(); 
 c = new char[len+1]; 
 strcpy(c,s.c_str()); 

d)  char* 转string 
 char* c = “abc”; 
 string s(c); 

e)  const char* 转char* 
 const char* cpc = “abc”; 
 char* pc = new char[strlen(cpc)+1]; 
 strcpy(pc,cpc);

f)  char* 转const char*，直接赋值即可 
 char* pc = “abc”; 
 const char* cpc = pc;
```

#### 什么时候使用指针作为参数，什么时候使用引用

指针：

1. 基础类型数组
2. 可选参数，传递nullptr

引用：

1. 类
2. 确保参数非空

#### 如何设计一个计算仅单个子类的对象的个数

类中使用static变量作为计数并初始化（未显式初始化默认为0）。

构造函数、拷贝构造函数、赋值构造函数对count+1，析构函数-1

#### 将引用作为返回值

最大的好处是内存中不产生被返回值的副本

不能返回局部变量的引用

不能返回new分配的内存的引用

可以返回类的引用

#### sprintf

sprintf用于格式化数据写入字符串，是printf的变体，printf是将格式化的输出到标准输出。

```c++
int sprintf(char *str, const char *format, ...);
#include <stdio.h>

int main() {
    char buffer[100];
    int num = 250;
    float pi = 3.14159;

    sprintf(buffer, "Number: %d, Pi: %.2f", num, pi);
    printf("%s\n", buffer);  // 输出: Number: 250, Pi: 3.14

    return 0;
}
```

#### 如何禁止程序自动生成拷贝构造函数

将拷贝构造函数标记为delete来明确禁止生成拷贝构造函数。

#### main的返回值

0传递给调用者表示程序正常退出

