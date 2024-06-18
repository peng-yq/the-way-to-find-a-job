# Golang GC

## Mark and Sweep

早期的golang使用最简单的GC算法，即mark and sweep。

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406181644706.png"/>

首先STW，然后从根集合开始，访问并标记堆中可达的对象。

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406181655321.png" style="width: 50%; height: auto;"/>

标记完成后，再遍历堆中的全部对象，并将未标记的对象进行垃圾回收，并将内存进行释放加入空闲链表。完成后再停止STW，继续工作。

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406181658666.png" style="width: 50%; height: auto;"/>

mark and sweep的缺点：

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406181658934.png" />

早期的尝试：将sweep放到暂停STW后，但STW的时间依然很长。

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406181702525.png"/>

## 三色标记法 (v1.5)

三色标记法将对象分为白色、灰色和黑色：

- 白色：尚未被访问的对象。
- 灰色：已被访问但其引用的对象尚未全部访问的对象。
- 黑色：已被访问，且其引用的对象也已被访问的对象。

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406181710923.png" style="width: 50%; height: auto;"/>

### 第一步

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406181713388.png"/>

### 第二步

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406181727690.png"/>

### 第三步

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406181728058.png"/>

### 第四步

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406181729805.png"/>

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406181729644.png"/>

### 第五步

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406181729183.png"/>

### 三色标记的问题

假如三色标记法不需要STW，当在标记的过程种，白色对象被黑色对象引用，但无灰色对象或有灰色对象的链路引用，就会触发错误。也就是说下面两种条件同时达到时，就会造成这个白色对象被错当作垃圾对象被GC。但是如果使用三色标记又使用STW，那么岂不是更复杂了。

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406181731294.png"/>

## 强三色不变式和弱三色不变式

回顾三色标记法的问题，只有当2种条件同时达成才会造成错误。因此只需破坏其中一个条件成立即可，就和破坏死锁一样。破坏两个条件，分别是强三色不变式和弱三色不变式。

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406181749156.png"/>

### 强三色不变式

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406181750379.png"  style="width: 50%; height: auto;"/>

### 弱三色不变式

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406181752428.png" style="width: 50%; height: auto;"/>

强/弱三色不变式都是对黑色对象引用白色对象进行的一些限制。

## 屏障机制

**垃圾收集中的屏障技术更像是一个钩子方法，它是在用户程序读取对象、创建新对象以及更新对象指针时执行的一段代码**，根据操作类型的不同，我们可以将它们分成**读屏障（Read barrier）和写屏障（Write barrier）两种，因为读屏障需要在读操作中加入代码片段，对用户程序的性能影响很大，所以编程语言往往都会采用写屏障保证三色不变性**。

Golang也不例外，通过**插入写屏障**和**删除写屏障**技术保证三色不变性和GC的正确性。

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406181811679.png"/>

### 插入写屏障

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406181812134.png"/>

插入写屏障流程

> 关于GC为什么处理栈上的对象：如果栈上的对象引用了堆上的对象，GC需要访问并标记这些堆对象。然而，栈上的对象本身通常不需要被GC回收，因为它们的生命周期由函数调用和返回控制，一旦函数返回，相关的栈帧即自动清理。尽管Go的GC不直接“回收”栈上的对象，它确实会在垃圾回收的标记阶段检查栈上的对象，以确保正确处理栈上对象可能引用的堆上对象。这样做是为了维护堆内存的正确引用图，确保只有真正不再被任何活跃对象引用的堆内存才被标记为可回收。

但一般来说为了程序稳定性和栈对象加入写指针开销，栈对象不启用插入屏障。而是在结束时通过STW重新扫描栈对象。

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406181817245.png"/>

### 删除写屏障

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406181823522.png"/>

删除写屏障的流程：

一开始5被1引用，然后删除。被标记为灰色，后续被遍历，从而确保假如有一个黑色的去引用它，后续遍历不到，从而被标记成垃圾；**但回收精度低，也就是说假如对象5没有引用它的对象了，那么这一轮gc，对象5不会被删除，下一轮才会被删除**

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406181824722.png"/>

## 混合写屏障 (v1.8)

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406181954109.png"/>

### 场景1

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406182001033.png"/>

### 场景2

下面的描述有点问题，GC不会直接对栈对象进行删除。

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406182005708.png"/>

### 场景3

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406182007522.png"/>

### 场景4

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406182010348.png"/>

总体来说只需要记住栈上的对象被标记为黑色后不变，堆上要删除或添加对象都标记为灰色。

## 增量和并发

今天的计算机往往都是多核的处理器，垃圾收集器一旦开始执行就会浪费大量的计算资源，为了减少应用程序暂停的最长时间和垃圾收集的总暂停时间，我们会使用下面的策略优化现代的垃圾收集器：

- 增量垃圾收集 — 增量地标记和清除垃圾，降低应用程序单次暂停的最长时间；例如，标记阶段可以分成多个小的标记步骤，每处理一定量的对象后，GC暂停，应用程序继续执行，然后GC再次启动处理下一批对象。
- 并发垃圾收集 — 利用多核的计算资源，在用户程序执行时并发标记和清除垃圾；在并发GC模式下，大部分垃圾收集活动（如标记和清除）是在应用程序线程正在运行时同时进行的，这减少了GC需要的总暂停时间。

当然上述两种机制都要配合屏障机制，并且GC需要在提前进行，不能等内存告急了才开始，那样无异于停止程序。

## Golang GC的变更

下图中的变更和前面讲的差不多，比较大的节点是1.5的三色标记、1.7的并行栈收缩，1.8的混合写屏障（包括1.9的彻底移除STW前面也讲到了）。

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202406182019626.png"/>

## Golang GC的时机

- Go 语言运行时的默认配置会在堆内存达到上一次垃圾收集的 2 倍时（因为并发垃圾收集器与程序一起运行，无法准确控制堆内存的大小，一般在达到目标前触发），触发新一轮的垃圾回收，这个行为可以通过 `GOGC` 变量调整。它的默认值为 100，即增长 100% 的堆内存才会触发 GC；
- 如果一定时间内没有通过方式 1 触发，也会触发新的循环，这个定时时长由 `runtime.forcegcperiod` 变量控制，默认为 2 分钟。
- 手动触发
