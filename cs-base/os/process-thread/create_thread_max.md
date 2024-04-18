Linux中虚拟地址空间分为用户地址空间和内核地址空间。

<img src="https://cdn.xiaolincoding.com//mysql/other/20210715092026648.png">

32位操作系统总的虚拟地址空间为2^32，共4G，其中内核空间1G，用户空间占3G。64位操作系统，内核空间和用户空间分别位于最开始的和结束的128t，中间的内存未定义。

## 一个进程可以创建多少个线程

- 进程的虚拟地址空间上限：创建线程要分配栈空间，线程越多，进程虚拟地址空间占用越大
- 系统参数限制：内核参数没有限定单个进程能创建多少个线程，但限制了整个系统的最大线程数

```shell
$ ulimit -a
-t: cpu time (seconds)              unlimited
-f: file size (blocks)              unlimited
-d: data seg size (kbytes)          unlimited
-s: stack size (kbytes)             8192
-c: core file size (blocks)         0
-m: resident set size (kbytes)      unlimited
-u: processes                       31761
-n: file descriptors                1024
-l: locked-in-memory size (kbytes)  65536
-v: address space (kbytes)          unlimited
-x: file locks                      unlimited
-i: pending signals                 31761
-q: bytes in POSIX msg queues       819200
-e: max nice                        0
-r: max rt priority                 0
-N 15:                              unlimited
```

可以通过上述命令查看堆栈空间，上述显示单个堆栈所用空间位8M，32位操作系统所支持的最大堆栈数为3G/8M，大概是300+个线程。

下面3个系统参数也会影响单个进程所能创建的最大线程数目：

```shell
# pyq @ 0x505951-Y7000P in ~ [23:09:45]
# 系统支持的最大线程数
$ cat /proc/sys/kernel/threads-max
63522

# pyq @ 0x505951-Y7000P in ~ [23:09:47]
# 可以分配的最大进程号
$ cat /proc/sys/kernel/pid_max
4194304

# pyq @ 0x505951-Y7000P in ~ [23:10:10]
# 每个进程可以拥有的最大内存映射段数
$ cat /proc/sys/vm/max_map_count
65530
```

PID (Process ID)：这是分配给每个进程的唯一标识符。在Linux中，每个进程都有一个唯一的PID。
TID (Thread ID)：在Linux中，线程也被赋予一个唯一的标识符，称为线程ID或TID。对于多线程应用，每个线程都有其自己的TID，但它们共享相同的PID，即它们所属进程的PID。

为什么物理内存只有2G，进程的虚拟内存却可以使用25T呢？

**因为虚拟内存并不是全部都映射到物理内存的，程序是有局部性的特性，也就是某一个时间只会执行部分代码，所以只需要映射这部分程序就好**。