## Golang调度器的由来

- 单进程
- 多进程/多线程
- 协程及其与线程的数量模型
- 早期的Golang调度器

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406172217135.png"/>

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406172220062.png"/>

## GMP模型

### GMP模型简介

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406172223022.png"/>

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406172227329.png"/>

P和M的总数量关系不是1：1的，M可能更多，P也可能更多，但一个P同一时刻最多只有一个M与其绑定。

至于为什么不直接将本地队列放在 M 上、而是要放在 P 上呢？ **这是因为当一个线程 M 阻塞（可能执行系统调用或 IO请求）的时候，可以将和它绑定的 P 上的 G 转移到其他线程 M 去执行，如果直接把可运行 G 组成的本地队列绑定到 M，则万一当前 M 阻塞，它拥有的 G 就不能给到其他 M 去执行了**。

在Go语言的调度器中，`P` 结构体拥有一个本地的环形队列，用于存放可运行的 `Goroutine`（简称 `G`）。这个队列的长度为 256，设计为环形主要是为了高效地进行元素的插入和删除操作。**环形队列的一个关键特性是它支持无锁的访问，这主要是通过使用比较并交换（Compare-And-Swap，CAS）操作实现的**。CAS：先比较内存位置当前值是否匹配预期值，如果为true则进行写入，否则不会执行任何写入。通过CAS操作确保G入队和出队的原子性。更具体来说：

- 入队（Enqueue）：当一个Goroutine被创建或者需要调度时，它会被添加到P的本地队列中。入队操作首先读取队列的tail索引，然后尝试通过CAS将G放在tail位置，并更新tail索引。如果CAS操作失败（通常是因为其他线程已经修改了tail），则重试直到成功。
- 出队（Dequeue）：当一个M需要执行Goroutine时，它会从P的本地队列的head索引处取出一个G来执行。出队操作同样使用CAS来更新head索引，确保在多线程环境下的正确性和一致性。

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406172234722.png"/>

### Golang调度器的设计策略

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406172226730.png"/>

**work stealing**：优先去全局队列中拿G，没有再去其他P的队列中stealing，一般是拿P队列的后面一半。下图中M2绑定的P队列中一开始无G执行，但此时全局队列中也没有G，只有从M1的P队列中偷队列后面的G3过来调度。

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406172235431.png"/>

**hand off**：一开始M1绑定的是M3现在绑定的P，在执行G1的过程中发生了阻塞，为了不浪费P的资源，会从M列表中唤醒一个M，并将P进行转移。当G1阻塞完成，其会优先去寻找之前执行的P，如果P已满并且P列表为空则加入全局队列，同时M休眠或GC。**一般来说G和M会一起阻塞，但如果是M上的G进入Channel阻塞，则该M不会一起进入阻塞，因为Channel数据传输涉及内存拷贝，不涉及系统资源等待。相反，它会从本地或全局运行队列中寻找另一个可运行的Goroutine来执行。这样做的目的是保持CPU的利用率，避免因单个Goroutine的阻塞而导致整个线程空闲**。

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406172239103.png"/>

**基于协作的抢占式调度**：为了保证公平性和防止 Goroutine 饥饿问题，Go 程序会保证每个 G 运行 10ms 就让出 M，交给其他 G 去执行，这个 G 运行 10ms 就让出 M 的机制，是**由单独的系统监控线程通过 retake() 函数给当前的 G 发送抢占信号实现的，如果所在的 P 没有陷入系统调用且没有满，让出的 G 优先进入本地 P 队列，否则进入全局队列**。注意这里的信号更多的是Go Runtime内部的处理，而非操作系统级别的。

**基于信号的真抢占机制**：尽管基于协作的抢占机制能够缓解长时间 GC 导致整个程序无法工作和大多数 Goroutine 饥饿问题，但是还是有部分情况下，Go调度器有无法被抢占的情况，例如，for 循环或者垃圾回收长时间占用线程，为了解决这些问题， **Go1.14 引入了基于信号的抢占式调度机制，能够解决 GC 垃圾回收和栈扫描时存在的问题**。

**全局队列**：全局队列的 **G 永远会有 1/61 的机会被获取到**，调度循环中，优先从本地队列获取 G 执行，不过每隔61次，就会直接从全局队列获取，至于为啥是 61 次，Dmitry 的视频讲解了，就是要**一个既不大又不小的数，而且不能跟其他的常见的2的幂次方的数如 64 或 48 重合**。

### go func()的过程

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406172323912.png"/>

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406172326504.png"/>

### Golang调度器的生命周期

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406172330889.png"/>

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406172331547.png"/>

以下面的例子，即使没有明确使用go func创建goroutinue，但main函数也是一个G，并被G0调度在M上执行。

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406172332353.png"/>

调度器的启动逻辑是：初始化 g0 和 m0，并将二者互相绑定， m0 是程序启动后的初始线程，**g0 是 m0 线程的系统栈代表的 G 结构体，负责普通 G 在 M 上的调度切换 --> runtime.schedinit()**：M、P 的初始化过程，分别调用runtime.mcommoninit() 初始化 M 的全局队列allm 、调用 runtime.procresize() 初始化全局 P 队列 allp --> runtime.newproc()：负责获取空闲的 G 或创建新的 G --> runtime.mstart() 启动调度循环；；

调度器的循环逻辑是：运行函数 schedule() --> 通过 runtime.globrunqget() 从全局队列、通过 runtime.runqget() 从 P 本地队列、 runtime.findrunnable 从各个地方，获取一个可执行的 G --> 调用 runtime.execute() 执行 G --> 调用 runtime.gogo() 在汇编代码层面上真正执行G --> 调用 runtime.goexit0() 执行 G 的清理工作，重新将 G 加入 P 的空闲队列 --> 调用 runtime.schedule() 进入下一次调度循环。

G 在运行时中的状态可以简化成三种：等待中_Gwaiting（比如阻塞等待）、可运行_Grunnable、运行中_Grunning，运行期间大部分情况是在这三种状态间来回切换。

### 可视化的GMP编程（go tool trace）

go tool trace一般做性能分析。	

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406172337573.png"/>

使用debug trace。

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406172339048.png"/>

## GMP场景分析

### 场景1

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406180922441.png"/>

### 场景2

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406180928980.png"/>

### 场景3

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406180929136.png"/>

### 场景4

此时P1本地队列已满了，但G2要创建G7，调度器会将P1本地队列的前面一半和新创建的G7打乱顺序加入到全局队列中。

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406180930078.png"/>

### 场景5

此时P1全局队列未满，G2创建G8则会和场景1一样放入至P1的本地队列。

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406180933095.png"/>

### 场景6

如果有空闲的M和P，会尝试让这个组合去执行G，实现负载均衡。如果P和M没有G来执行，那么M此时为自旋状态，一直去寻找G。

自旋线程M的寻找方式：当一个M（操作系统线程）在执行完其当前的Goroutine后，它会尝试寻找新的Goroutine来执行。寻找的顺序通常如下：

- 本地运行队列：每个P拥有一个本地的Goroutine队列。M首先检查其绑定的P的本地队列是否有待执行的Goroutines。

- 全局运行队列：如果本地队列为空，M会检查全局Goroutine队列。全局队列是一个系统级的队列，存储了那些还未被分配到某个P的Goroutines。


- 从其他P窃取：如果全局队列也为空，M会尝试从其他P的本地队列中“窃取”Goroutines。这通常是通过一种称为“work stealing”（工作窃取）的算法完成的，M会从其他P的队列的尾部尝试窃取Goroutines，以减少对那个P当前执行的干扰。


自旋线程的必要性：**自旋线程M的存在是为了减少系统在高并发环境下的延迟和提高CPU的利用率**。关于自旋线程的必要性，可以从以下几点理解：

- **快速响应**：通过保持一些M在自旋状态，系统可以更快地响应新的Goroutines。当新的工作到来时，已经在自旋的M可以立即开始执行，而不需要等待操作系统调度新的线程，从而减少启动延迟。
- **平衡负载**：自旋可以帮助系统在多个P之间更平衡地分配工作负载。通过工作窃取，空闲的M可以帮助忙碌的P处理积压的工作，从而提高整体的处理效率。
- **效率与成本的权衡**：虽然自旋会消耗CPU资源（可能看起来像是浪费），但在并发高、任务分布不均的情况下，这种成本是为了更大的效益—即减少总体的任务处理时间和提高响应速度。

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406180939715.png"/>

### 场景7

下面图中的函数有无，准确来说那个函数是从各个地方去找可执行的G。下图也是实现负载均衡，注意从全局队列取的数量，不会太多也不会太少，使得可以平均分到每一个P。

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406180947640.png"/>

### 场景8

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406180949089.png"/>

### 场景9

自旋线程是在运行的线程，是与P绑定的。因此自旋线程+在运行的线程<=GOMAXPROCS

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406180950653.png"/>

### 场景10

其实就是hand off，下图场景中如果P2本地队列为空，全局队列不为空，新版定的P2会从全局队列中取G来执行。

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406180953635.png"/>

### 场景11

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406181002131.png"/>

## GMP源码

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406181009149.JPG"/>