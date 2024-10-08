## 虚拟内存

单片机没有操作系统，每次写完程序需要通过工具烧录进去，程序才能跑起来。在单片机中，CPU直接操作物理内存，这对于同时运行多个程序而言是不可能，因为假如多个程序同时操作了同一个物理地址会有不确定性和安全隐患。因此，为了将每个进程地址空间隔离开来，引入了虚拟地址空间。操作系统为每个进程分配了一套完整的虚拟地址空间，让进程有拥有了整个地址空间的错觉。进程只能访问虚拟地址空间，不能直接访问物理地址空间，虚拟地址空间到物理地址空间的映射由CPU中的MMU（内存管理单元）完成。

<img src="https://cdn.xiaolincoding.com//mysql/other/72ab76ba697e470b8ceb14d5fc5688d9.png">

虚拟地址空间到物理地址空间的映射可分为：

- 内存分段
- 内存分页

## 内存分段

**程序可分为不同的逻辑分段：代码段，数据段，堆段和栈段，不同的段有不同的属性**。

<img src="https://cdn.xiaolincoding.com//mysql/other/a9ed979e2ed8414f9828767592aadc21.png">

内存分段机制下，虚拟地址由段选择因子和段内偏移量组成：

- 段选择因子通常包括段号和特权等标志位，通过段号可以在段表（GDT或LDT）中索引到唯一的段描述符。
- 段描述符包括段的基地址，界限和特权级等。
- 如果虚拟地址的段内偏移量在界限中，则通过段的基地址+段偏移量得到具体的物理地址。

> 全局描述符表（GDT）：GDT是由操作系统维护的全局表，它包含了系统中所有内存段的描述符。这些段包括操作系统的代码段、数据段以及其他可能的系统级段。GDT对整个系统有效，操作系统和所有的应用程序都可以根据GDT中的描述符来访问内存。每个处理器都有一个寄存器（GDTR）存储GDT的位置和大小。
>
> 局部描述符表（LDT）：LDT是为特定进程提供额外的段描述符表。它允许每个进程定义额外的、私有的内存段，这些段只对该进程可见。LDT是进程级的，每个进程可以有自己的LDT，用于存储特定于该进程的段信息。每个进程的任务状态段（TSS）中有一个指针指向其LDT。
>
> 操作系统负责创建和管理每个进程的LDT。每个进程的LDT都通过一个称为LDTR的特殊寄存器来访问。当进程被调度运行时，操作系统负责加载该进程的LDT地址到LDTR寄存器。这确保了CPU在执行该进程时使用正确的LDT。虽然LDT本身是独立于GDT的，每个LDT都需要在GDT中有一个对应的描述符。这个描述符不包含LDT的实际内容，而是包含了指向该LDT的基地址和界限的信息。这个描述符被称为“LDT描述符”。当操作系统或CPU需要访问特定进程的LDT时，它会首先查找GDT中对应的LDT描述符，通过这个描述符获取LDT的物理地址，然后通过LDTR寄存器来使用这个LDT。

分段机制会将虚拟地址分为代码段，数据段，堆段和栈段。内存分段使得程序无需关心物理地址，但主要存在2个问题：

**1. 内存碎片**
**2. 内存交换效率低**

### 内存碎片

**内存碎片分为内部内存碎片和外部内存碎片**。内部内存碎片就是操作系统分配给程序远大于其所需的内存空间时，会导致未被利用的那部分内存空间被浪费，由于内存分段可以做到按需分配内存，因此内部内存碎片在内存分段中很少出现。而外部内存碎片则是内存中有许多小的，无法利用的内存，也就是不连续的内存空间，**在内存分段中，由于每个段大小不一致，且动态加载和卸载，容易留下小的不连续的内存空间，造成外部内存碎片**。比如下图中，浏览器退出后内存虽然还剩余512MB，但不连续，不能分配200MB的内存空间。

<img src="https://cdn.xiaolincoding.com//mysql/other/6142bc3c917e4a6298bdb62936e0d332.png">

解决内存外部碎片可以通过内存交换，例如上图中，先将音乐占用的内存空间置换至硬盘中，再置换回来。

> Swap空间（交换空间）是计算机操作系统中用于扩展物理内存（RAM）的一种机制。当系统的RAM被占满时，操作系统可以使用硬盘上的一个特定区域（即swap空间）来存储暂时不活跃的内存页面。这样做可以释放RAM中的空间，使其可以用于当前更需要的任务或进程。Swap空间是虚拟内存系统的一部分，总的可用空间为物理内存大小+Swap空间大小，但swap毕竟在硬盘中，速度会慢很多（SSD会好些）。

### 内存交换效率低

内存分段极易产生外部内存碎片，可能会导致频繁的内存交换，而硬盘的速度很慢，如果交换一个占用空间很大的程序，整个机器可能都稍显卡顿。

## 内存分页

内存分段容易出现内存碎片和内存交换效率低的主要原因是因为段的大小不一，因此出现了内存分页。**内存分页将虚拟内存和物理内存分为一个个固定大小的页，Linux中页大小固定为4KB**。内存分页中，虚拟地址和物理地址的转换通过页表和MMU完成。**当进程访问的虚拟地址空间在页表中查询不到时，操作系统会产生一个缺页异常，并陷入内核空间中为其分配物理内存（可能是不存在，也可能是换出到硬盘了），更新页表，再返回用户内存空间，恢复进程运行**。

正因为内存分页中页的大小是固定的，页于页之间紧密排列，不会出现微小的空隙，因此可以解决内存外部碎片问题；而段的大小不一，按需分配，动态加载和卸载，容易产生不能被利用的内存外部碎片。**页分配的最小单位为1个页，因此页可能会产生内存内部碎片的问题**。此外，操作系统会将最近未被使用的页换出到硬盘中（LRU），有需要再置换回来。**相较于段，页的大小固定，程序每次写入的只有一个或几个页，因此内存交换效率更高**。此外由于局部性原理，我们不需要一次性将进程的虚拟地址空间都映射到物理内存中，只映射正在使用的页。

<img src="https://cdn.xiaolincoding.com//mysql/other/388a29f45fe947e5a49240e4eff13538-20230309234651917.png">

### 单级页表

<img src="https://cdn.xiaolincoding.com//mysql/other/7884f4d8db4949f7a5bb4bbd0f452609.png">

内存分页中虚拟地址由页号和页内偏移量组成，通过页号可以在页表中索引到唯一的页表项（PTE），页表项中保存了物理页号（还包括一些其他信息，比如是否可读写，是否在内存等），通过物理页号+页内偏移量可以得到唯一的物理地址。

单级页表虽然简单直观，但会导致页表存储占用大量的内存。

在32位的环境下，虚拟地址空间共有4GB（2^32），假设一个页的大小是4KB（2^12），那么就需要大约100万（2^20）个页，每个页表项需要4个字节大小来存储，那么整个4GB空间的映射就需要有4MB的内存来存储页表。这4MB大小的页表，看起来也不是很大。但是要知道每个进程都是有自己的虚拟地址空间的，也就说都有自己的页表。那么，100个进程的话，就需要400MB的内存来存储页表，这是非常大的内存了，更别说64位的环境了。

> 页大小4KB是经过综合考虑，比如内存利用率，页表大小，性能，软硬件兼容等。

- **段表中的段描述符项通常比页表项少，因为段的大小不固定**。
- x86架构中（32/64）使用CR3寄存器来保存进程页表的基地址，每次进行切换时，CR3都会刷新，此外CPU中的TLB也会被刷新。TLB是一个缓存，用于存储最近使用的虚拟地址到物理地址的映射，以加速地址解析过程。

### 多级页表

针对上述页表存储空间的问题，出现了多级页表。

<img src="https://cdn.xiaolincoding.com//mysql/other/19296e249b2240c29f9c52be70f611d5.png">

多级页表中将虚拟地址分为了10位的一级页号，10位的二级页号和12位的页内偏移。一级页号用于在页表中索引出唯一的页表项，从而确定二级页表的虚拟地址（一级页表总共包含2^10个二级页表），二级页号在二级页表中确定物理页号，最后再加上页内偏移确定物理地址。

**前面我们分析得到单级页表中保存单个进程32G的虚拟地址空间，需要4MB的页表大小；而上图却需要4KB+4MB（分别是1个一级页表+1024个二级页表）。但程序执行具有局部性原理，一级页表中已经包含了程序完整的虚拟地址空间，我们只需要创建需要用到的二级页表即可，比如只用到了20%的二级页表，总的内存空间占用为4KB+4MB*0.2。也就是说多级页表中节约的页表大小是暂用不到的二级页表，一级页表是需要全部创建的，因为页表需要覆盖进程的全部虚拟地址空间，因此单级页表需要创建完整的4MB页表大小**。总结来说就是页表一定要覆盖全部虚拟地址空间，不分级的页表就需要有100多万个页表项来映射，而二级分页则只需要1024个页表项（32位，此时一级页表覆盖到了全部虚拟地址空间，二级页表在需要时创建）。

对于64位系统，2层分页不够，变成4层分页

<img src="https://cdn.xiaolincoding.com/gh/xiaolincoder/ImageHost/%E6%93%8D%E4%BD%9C%E7%B3%BB%E7%BB%9F/%E5%86%85%E5%AD%98%E7%AE%A1%E7%90%86/%E5%9B%9B%E7%BA%A7%E5%88%86%E9%A1%B5.png">

### TLB

多级页表降低了进程页表存储的空间大小，但使得虚拟地址到物理地址的转换更加复杂，并且程序的执行具有局部性原理，因此CPU中有一个专门保存最近使用的虚拟地址到物理地址转换的页表项的cache，也就是TLB。CPU在寻址时，首先会查找TLB，如果未命中，再去查页表，一般来说TLB的命中率很高。

<img src="https://cdn.xiaolincoding.com//mysql/other/a3cdf27646b24614a64cfc5d7ccffa35.png">

## 段页式管理

段页式管理将内存分段和内存分页结合起来，先将程序分段，再将段分为固定大小的页，程序地址由段号，段内页号和页内偏移构成：

- 每个进程一个段表，段号索引到唯一的段描述符，包含了页表地址（也就是每个段有一个页表）
- 段内页号索引到唯一的页表项，页表项包含物理页号，加上页内偏移获取物理地址。

**段页式管理虽然增加了硬件成本和系统开销，但提高了内存利用率**。

## Linux内存布局

Intel的内存管理：逻辑地址（段前）->线性地址（页前）->物理地址

<img src="https://cdn.xiaolincoding.com//mysql/other/bc0aaaf379fc4bc8882efd94b9052b64.png">

Linux系统中的每个段都是从0地址开始的整个4GB虚拟空间（32 位环境下），也就是所有的段的起始地址都是一样的。这意味着，Linux系统中的代码，包括操作系统本身的代码和应用程序代码，所面对的地址空间都是线性地址空间（虚拟地址），这种做法相当于屏蔽了处理器中的逻辑地址概念，段只被用于访问控制和内存保护（**特权级，界限等**）。

**段提供了基于长度和特权级的保护，但页提供了更细粒度的保护，允许操作系统控制每个页的访问权限。在现代操作系统中，如Windows和Linux，通常使用页式管理作为主要的内存管理机制，而段式管理则更多地用于兼容性和特定的底层任务（如在x86架构中处理特权级）**。

<img src="https://cdn.xiaolincoding.com/gh/xiaolincoder/%E6%93%8D%E4%BD%9C%E7%B3%BB%E7%BB%9F/%E8%99%9A%E6%8B%9F%E5%86%85%E5%AD%98/32%E4%BD%8D%E8%99%9A%E6%8B%9F%E5%86%85%E5%AD%98%E5%B8%83%E5%B1%80.png">

用户内存空间如上：

- 代码段，包括二进制可执行代码；
- 数据段，包括已初始化的静态常量和全局变量；
- BSS 段，包括未初始化的静态变量和全局变量；
- 堆段，包括动态分配的内存，从低地址开始向上增长；
- 文件映射段，包括动态库、共享内存等，从低地址开始向上增长（跟硬件和内核版本有关 (opens new window)）；
- 栈段，包括局部变量和函数调用的上下文等。栈的大小是固定的，一般是8MB。当然系统也提供了参数，以便我们自定义大小（注意是从高地址到低地址，历史原因，空间利用效率，安全，区分堆）；

代码段下面还有一段内存空间的（灰色部分），这一块区域是「保留区」，之所以要有保留区这是因为在大多数的系统里，我们认为比较小数值的地址不是一个合法地址，例如，我们通常在C的代码里会将无效的指针赋值为NULL。因此，这里会出现一段不可访问的内存保留区，防止程序因为出现bug，导致读或写了一些小内存地址的数据，而使得程序跑飞。在这7个内存段中，堆和文件映射段的内存是动态分配的。比如说，使用C标准库的malloc()或者mmap()，就可以分别在堆和文件映射段动态分配内存。