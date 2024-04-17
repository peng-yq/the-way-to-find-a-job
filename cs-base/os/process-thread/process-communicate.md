进程拥有独立的用户地址空间，共享内核地址空间，进程间通信必须通过内核，进程间通信的方式包括：

1. 管道
2. 消息队列
3. 共享内存
4. 信号量
5. 信号
6. socket

## 管道

Linux中的`|`就是管道，这种管道是单向数据传输的，称为匿名管道，用完即销毁。若想实现双向数据传输，则需要创建两个管道。

```shell
ps auxf | grep mysql
```

> ps auxf：ps 是一个命令，用于报告当前进程的快照。
>
> - a 告诉 ps 列出所有用户的进程。
> - u 显示进程的用户/所有者。
> - x 包括没有控制终端的进程，如守护进程。
> - f 启用完整格式列表，包括进程树。

除了匿名管道，管道还有另外一种类型，即命名管道`FIFO`，数据先进先出。

```shell
mkfifo pyqpipe
ls -l
# 可以看到文件类型显示为p，pipe
prw-r--r-- 1 pyq pyq    0 Apr 17 10:46 pyqpipe
# 使用标准输出重定向向管道中发送消息
echo "hello" > pyqpipe
# 读取管道中的内容
cat pyqpipe
```

> I/O重定向：允许改变命令的标准输入，输出和错误的位置
> 标准输出重定向：> 和 >>，前者是替换文件内容，后者是追加到文件后面
> 标准错误重定向：2> 和 2>>
> 标准输入重定向： <
> 管道也是一种I/O重定向

如果管道中的内容没被读取，`echo`命令不能正常退出。管道创建简单，很容易知道管道中的数据是否被另外一个进程所读取。缺点也很明显，效率低，不适合进程间频繁的数据交换。

c中创建管道的方式：用于创建一个匿名管道，返回两个描述符，fd[0]为读端，fd[1]为写端。创建的管道仅位于内存中，本质是内核中的缓存

```c
int pipe(int fd[2])
```

进程间使用管道通信的方式如下：注意同一时间只有一个读端或写端开启，可以看mit s6.081的实验。

<img src="https://cdn.xiaolincoding.com/gh/xiaolincoder/ImageHost/%E6%93%8D%E4%BD%9C%E7%B3%BB%E7%BB%9F/%E8%BF%9B%E7%A8%8B%E9%97%B4%E9%80%9A%E4%BF%A1/7-%E7%AE%A1%E9%81%93-pipe-fork-%E5%8D%95%E5%90%91%E9%80%9A%E4%BF%A1.jpg">

使用`ps auxf | grep mysql`命令时，ps和grep都是shell的子进程，过程如下：

<img src="https://cdn.xiaolincoding.com/gh/xiaolincoder/ImageHost/%E6%93%8D%E4%BD%9C%E7%B3%BB%E7%BB%9F/%E8%BF%9B%E7%A8%8B%E9%97%B4%E9%80%9A%E4%BF%A1/8-%E7%AE%A1%E9%81%93-pipe-shell.jpg">

**匿名管道的通信范围是存在父子关系的进程，因为管道没有实体，只能通过fork父进程的fd来实现通信；而命名管道的适用范围更广些，因为存在实体；不管是匿名管道还是命名管道，通信数据都是FIFO的**。

## 消息队列

相较于管道，消息队列更适合进程间频繁通信。A进程需要给B进程发送消息，只需要把消息放置对应的消息队列即可返回（管道则是没有读取就不能返回），B再前往对应的消息队列读取即可。**消息队列本质是内核中的消息链表，发送数据格式是消息体（自定义的存储块，非管道中五格式的字节流数据）**。不主动释放消息队列，其生命周期随内核一起存在（区别于匿名管道）。

消息队列的缺点：一是通信不及时，二是附件也有大小限制。

- **消息队列不适合比较大数据的传输，因为在内核中每个消息体都有一个最大长度的限制，同时所有队列所包含的全部消息体的总长度也是有上限**。在Linux内核中，会有两个宏定义MSGMAX和MSGMNB，它们以字节为单位，分别定义了一条消息的最大长度和一个队列的最大长度。
- **消息队列通信过程中，存在用户态与内核态之间的数据拷贝开销**，因为进程写入数据到内核中的消息队列时，会发生从用户态拷贝数据到内核态的过程，同理另一进程读取内核中的消息数据时，会发生从内核态拷贝数据到用户态的过程。

## 共享内存

消息队列中数据的发送和读取需要用户态和内核态的拷贝，**而共享内存通过将两个进程的虚拟地址空间映射至同一个物理内存中**，一个进程进行写入，另外一个进程可直接读取，无需拷贝。

<img src="https://cdn.xiaolincoding.com/gh/xiaolincoder/ImageHost/%E6%93%8D%E4%BD%9C%E7%B3%BB%E7%BB%9F/%E8%BF%9B%E7%A8%8B%E9%97%B4%E9%80%9A%E4%BF%A1/9-%E5%85%B1%E4%BA%AB%E5%86%85%E5%AD%98.jpg">

## 信号量

两个进程使用共享内存通信涉及到一个问题，也就是互斥和同步，如果两个进程同时写就可能发生冲突。**信号量是一个整形的计数器，用于进程间的互斥和同步**。

信号量表示资源的数量，控制信号量主要通过两种原子操作：

- P操作：使用资源前，将信号量-1：如果信号量在p操作后<0，表示当前已无可用资源，需阻塞等待；若信号量在p操作后>=0，表示进程可以使用资源。
- V操作：使用资源后，将信号量+1，如果信号量在v操作后<=0，表示当前有阻塞中的进程，需要将其唤醒；若信号量在v操作后>0，表示无阻塞中的进程。

**将信号量设置为1，可以实现进程间互斥**，保证任一时间只有1个进程在访问资源。

<img src="https://cdn.xiaolincoding.com/gh/xiaolincoder/ImageHost/%E6%93%8D%E4%BD%9C%E7%B3%BB%E7%BB%9F/%E8%BF%9B%E7%A8%8B%E9%97%B4%E9%80%9A%E4%BF%A1/10-%E4%BF%A1%E5%8F%B7%E9%87%8F-%E4%BA%92%E6%96%A5.jpg">

**将信号量设置为0，可以实现进程间同步（被依赖的进程执行V操作，依赖的进程执行P操作）**，比如A进程写，B进程读，B进程需要在A进程写后来读。

<img src="https://cdn.xiaolincoding.com/gh/xiaolincoder/ImageHost/%E6%93%8D%E4%BD%9C%E7%B3%BB%E7%BB%9F/%E8%BF%9B%E7%A8%8B%E9%97%B4%E9%80%9A%E4%BF%A1/11-%E4%BF%A1%E5%8F%B7%E9%87%8F-%E5%90%8C%E6%AD%A5.jpg">

- 假如B先执行，首先进行P操作，信号量变为-1，阻塞等待
- A执行，执行V操作，信号量变为0，唤醒B进程
- 假如A先执行，执行V操作，信号量变为1
- B执行，执行P操作，信号量变为0，可以执行

## 信号

前面所列举的进程间通信方式均是进程正常状态下的，而**对于异常情况下的工作状态，需要使用信号的方式来通知进程，主要用于通知各种异常事件**。**信号是进程间唯一的异步通信，因为它们可以在任何时候发送到一个进程，通常与进程的正常控制流无关。这意味着信号可以在程序执行的任何点被接收和处理，而不需要进程显式地在某个时刻等待或检查信号的到来**。

Linux中的信号包括：Ctrl+C产生SIGINT信号，表示终止该进程；Ctrl+Z产生SIGTSTP信号，表示停止该进程，但还未结束；kill也是一种信号；

```shell
$ kill -l
 1) SIGHUP       2) SIGINT       3) SIGQUIT      4) SIGILL       5) SIGTRAP
 6) SIGABRT      7) SIGBUS       8) SIGFPE       9) SIGKILL     10) SIGUSR1
11) SIGSEGV     12) SIGUSR2     13) SIGPIPE     14) SIGALRM     15) SIGTERM
16) SIGSTKFLT   17) SIGCHLD     18) SIGCONT     19) SIGSTOP     20) SIGTSTP
21) SIGTTIN     22) SIGTTOU     23) SIGURG      24) SIGXCPU     25) SIGXFSZ
26) SIGVTALRM   27) SIGPROF     28) SIGWINCH    29) SIGIO       30) SIGPWR
31) SIGSYS      34) SIGRTMIN    35) SIGRTMIN+1  36) SIGRTMIN+2  37) SIGRTMIN+3
38) SIGRTMIN+4  39) SIGRTMIN+5  40) SIGRTMIN+6  41) SIGRTMIN+7  42) SIGRTMIN+8
43) SIGRTMIN+9  44) SIGRTMIN+10 45) SIGRTMIN+11 46) SIGRTMIN+12 47) SIGRTMIN+13
48) SIGRTMIN+14 49) SIGRTMIN+15 50) SIGRTMAX-14 51) SIGRTMAX-13 52) SIGRTMAX-12
53) SIGRTMAX-11 54) SIGRTMAX-10 55) SIGRTMAX-9  56) SIGRTMAX-8  57) SIGRTMAX-7
58) SIGRTMAX-6  59) SIGRTMAX-5  60) SIGRTMAX-4  61) SIGRTMAX-3  62) SIGRTMAX-2
63) SIGRTMAX-1  64) SIGRTMAX
```

用户进程对信号的处理方式。

1. 执行默认操作。Linux对每种信号都规定了默认操作，例如，上面列表中的SIGTERM信号，就是终止进程的意思。

2. 捕捉信号。我们可以为信号定义一个信号处理函数。当信号发生时，我们就执行相应的信号处理函数。

3. 忽略信号。当我们不希望处理某些信号的时候，就可以忽略该信号，不做任何处理。有两个信号是应用进程无法捕捉和忽略的，即SIGKILL和 SEGSTOP，它们用于在任何时候中断或结束某一进程。 

> 中断并不是进程间通信，是操作系统用来处理硬件信号的一种机制，允许硬件设备通知CPU有即时处理需求的事件，或者用于操作系统内核管理软件事件。这种机制使得CPU可以响应和处理外部或内部的事件，而不必持续检查事件的状态。中断也是异步的。

## socket

TCP（字节流 SOCK_STREAM）

<img src="https://cdn.xiaolincoding.com/gh/xiaolincoder/ImageHost/%E6%93%8D%E4%BD%9C%E7%B3%BB%E7%BB%9F/%E8%BF%9B%E7%A8%8B%E9%97%B4%E9%80%9A%E4%BF%A1/12-TCP%E7%BC%96%E7%A8%8B%E6%A8%A1%E5%9E%8B.jpg">

UDP（数据报 SOCK_DGRAM）

<img src="https://cdn.xiaolincoding.com/gh/xiaolincoder/ImageHost/%E6%93%8D%E4%BD%9C%E7%B3%BB%E7%BB%9F/%E8%BF%9B%E7%A8%8B%E9%97%B4%E9%80%9A%E4%BF%A1/13-UDP%E7%BC%96%E7%A8%8B%E6%A8%A1%E5%9E%8B.jpg">

本地进程通信：本地字节流socket和本地数据报socket在bind的时候，不像TCP和UDP要绑定IP地址和端口，而是**绑定一个本地文件**，这也就是它们之间的最大区别。

