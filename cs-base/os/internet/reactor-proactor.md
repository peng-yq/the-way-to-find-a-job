## reactor，proactor与epoll的关系

Reactor和Proactor模式都是处理并发 I/O 的模式，但它们在处理I/O事件的方式上有所不同。**Reactor主要用于同步非阻塞I/O，而Proactor用于异步I/O。epoll 是这些模式的一个实现工具，它提供了高效的事件通知机制，可以被用于实现Reactor或Proactor模式**。

## reactor

reactor模式主要由reactor和处理资源池组成：

- reactor负责监听和分发事件，比如连接事件和I/O事件
- 处理资源池负责如何处理事件

reactor可以是单个或多个，处理资源池可以是单个进程/线程，也可以是多个进程/线程。reactor模式主要可分为：

1. 单reactor 单进程/线程
2. 单reactor 多进程/线程
3. 多reactor 单进程/线程

### 单reactor 单进程/线程

以经典的C/S架构为例，单reactor 单进程/线程模型的示意图如下：

<img src="https://cdn.xiaolincoding.com/gh/xiaolincoder/ImageHost4@main/%E6%93%8D%E4%BD%9C%E7%B3%BB%E7%BB%9F/Reactor/%E5%8D%95Reactor%E5%8D%95%E8%BF%9B%E7%A8%8B.png">

上图主要可分为reactor，acceptor和handler三个组件：

1. reactor用于监听和分发事件
2. acceptor用于获取连接
3. handler用于处理业务

单reactor 单进程/线程模型流程可描述如下：

1. reactor通过I/O多路复用接口（图中是select）监听事件，并根据不同的事件类型分发（dispatch）给不同的处理对象
2. 如果是连接事件，则交付给acceptor处理，acceptor通过accept建立连接，并创建一个handler对象处理后续的响应事件
3. 如果是业务事件，则交付给handler对象进行处理，比如读->业务处理->发送

单reactor 单进程/线程实现较为简单，监听，分发处理事件都是在一个进程/线程中进行的，不用考虑进程/线程间通信。但也存在一些问题：

1. 无法充分利用多核CPU的性能
2. handler对象处理业务时，无法进行其他连接，如果业务处理较为复杂，则可能造成一定的响应延迟

redis 6.0版本之前采用的是单reactor 单进程的方案，因为redis在内存中进行处理。

### 单reactor 多进程/多线程

单reactor 多进程/线程模型的示意图如下：

<img src="https://cdn.xiaolincoding.com/gh/xiaolincoder/ImageHost4@main/%E6%93%8D%E4%BD%9C%E7%B3%BB%E7%BB%9F/Reactor/%E5%8D%95Reactor%E5%A4%9A%E7%BA%BF%E7%A8%8B.png">

相较于单reactor 单进程/线程，单reactor 多进程/多线程的变化如下：

1. handler不再负责业务处理，而是交予线程池中的线程进行，只负责数据的读与发送。

由于采用了多线程，因此需要使用互斥锁等操作来避免多线程对共享资源的竞争。此外，多进程的开销远大于多线程的开销了，所以此模型一般是单reactor 多线程。虽然单reactor 多线程模型可以很好的利用多核CPU的性能优势，但由于只有一个reactor对象负责事件的监听和分发，因此遇到突然的高并发事件时，可能会出现性能瓶颈。

### 多reactor 多进程/线程

多reactor 多进程/线程模型的示意图如下：

<img src="https://cdn.xiaolincoding.com/gh/xiaolincoder/ImageHost4@main/%E6%93%8D%E4%BD%9C%E7%B3%BB%E7%BB%9F/Reactor/%E4%B8%BB%E4%BB%8EReactor%E5%A4%9A%E7%BA%BF%E7%A8%8B.png">


多reactor 多进程/线程模型的流程可描述为：

1. mainreactor监控连接事件对象，当发生连接事件时，交付给acceptor建立连接，并将建立的连接分发给subreactor
2. subreactor继续监听分发的连接，监听到有业务处理事件时，创建一个handler对象来处理业务事件

多reactor 多进程/线程模型其实比单reactor 多线程模型简单：

1. mainreactor只负责新事件的连接，具体的业务处理由subreactor进行
2. mainreactor和subreactor的交互也很简单，无需subreactor返回

Netty和Memcache都采用了多 Reactor 多线程的方案。采用了多 Reactor 多进程方案的开源软件是Nginx，不过方案与标准的多Reactor多进程有些差异。具体差异表现在主进程中仅仅用来初始化socket，并没有创建mainReactor来accept连接，而是由子进程的Reactor来accept连接，通过锁来控制一次只有一个子进程进行accept（防止出现惊群现象），子进程accept新连接后就放到自己的Reactor进行处理，不会再分配给其他子进程。

## Proactor

最开始提到reactor模型是同步非阻塞I/O，而proactor是异步I/O。

阻塞I/O：进程在内核准备好数据（数据从磁盘到内核缓冲区）并将内核缓冲区中的数据拷贝至用户缓冲区完成前，进程一直是阻塞的。

<img src="https://cdn.xiaolincoding.com/gh/xiaolincoder/ImageHost/%E6%93%8D%E4%BD%9C%E7%B3%BB%E7%BB%9F/%E6%96%87%E4%BB%B6%E7%B3%BB%E7%BB%9F/%E9%98%BB%E5%A1%9E%20I_O.png">

非阻塞I/O：内核没准备好数据前，进程可以去做其他事；过段时间再次发起调用，若内核已经准备好数据，需要等待内核将数据拷贝至用户缓冲区。

<img src="https://cdn.xiaolincoding.com/gh/xiaolincoder/ImageHost/%E6%93%8D%E4%BD%9C%E7%B3%BB%E7%BB%9F/%E6%96%87%E4%BB%B6%E7%B3%BB%E7%BB%9F/%E9%9D%9E%E9%98%BB%E5%A1%9E%20I_O%20.png">

不管是阻塞I/O还是非阻塞I/O，这两者都是同步的，内核将数据从内核空间拷贝到用户空间的过程都是需要等待的，也就是说这个过程是同步的，如果内核实现的拷贝效率不高，read调用就会在这个同步过程中等待比较长的时间。

异步I/O：进程发起调用后，去做其他事；内核将数据拷贝至用户缓冲区后，通知进程进行处理。

<img src="https://cdn.xiaolincoding.com/gh/xiaolincoder/ImageHost/%E6%93%8D%E4%BD%9C%E7%B3%BB%E7%BB%9F/%E6%96%87%E4%BB%B6%E7%B3%BB%E7%BB%9F/%E5%BC%82%E6%AD%A5%20I_O.png">

> 食堂打饭的例子来解释阻塞I/O，非阻塞I/O和异步I/O：阻塞 I/O 好比，你去饭堂吃饭，但是饭堂的菜还没做好，然后你就一直在那里等啊等，等了好长一段时间终于等到饭堂阿姨把菜端了出来（数据准备的过程），但是你还得继续等阿姨把菜（内核空间）打到你的饭盒里（用户空间），经历完这两个过程，你才可以离开。非阻塞 I/O 好比，你去了饭堂，问阿姨菜做好了没有，阿姨告诉你没，你就离开了，过几十分钟，你又来饭堂问阿姨，阿姨说做好了，于是阿姨帮你把菜打到你的饭盒里，这个过程你是得等待的。异步 I/O 好比，你让饭堂阿姨将菜做好并把菜打到饭盒里后，把饭盒送到你面前，整个过程你都不需要任何等待。

**reactor是同步非阻塞I/O，感知就绪I/O事件，也就是有事件发生时，os通知应用进程，进程进行处理；proactor是异步I/O，感知已完成I/O事件，也就是有事件发生时，os处理完后再通知进程**。


<img src="https://cdn.xiaolincoding.com/gh/xiaolincoder/ImageHost4@main/%E6%93%8D%E4%BD%9C%E7%B3%BB%E7%BB%9F/Reactor/Proactor.png">

proactor模型流程可描述为：

1. proactor initiator创建handler和proactor
2. proactor initiator在asy...中进行handler和proactor注册
3. asy...完成I/O操作后通知proactor
4. proactor根据不同的事件类型调用不同的handler
5. handler完成事件处理

在Linux下的异步I/O是不完善的， aio系列函数是由POSIX定义的异步操作接口，不是真正的操作系统级别支持的，而是在用户空间模拟出来的异步，并且仅仅支持基于本地文件的aio异步操作，网络编程中的socket是不支持的，这也使得基于Linux的高性能网络程序都是使用Reactor方案。而Windows里实现了一套完整的支持socket的异步编程接口，这套接口就是IOCP，是由操作系统级别实现的异步I/O，真正意义上异步I/O，因此在Windows里实现高性能网络程序可以使用效率更高的Proactor方案。
