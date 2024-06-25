#### new和make的区别

- new只用于分配内存，返回一个指向地址的**指针**。它为每个新类型分配一片内存，初始化为0且返回类型*T的内存地址，它相当于&T{}
- make**只可用于slice,map,channel**的初始化,返回的是**引用**。

#### 请你讲一下Go面向对象是如何实现的？

go的面向对象不同于传统的C++和java语言，go没有对象的概念。通过struct和interface来实现面向对象。

1. 封装：
   - 如果一个结构体的字段名或者方法名以大写字母开头，那么它是公开的（可以被其他包访问）。
   - 如果以小写字母开头，则是私有的（只能在同一包内访问）。
2. 继承：通过嵌入结构体来实现类似继承的功能，或者说组合。
3. 多态：通过interface，interface定义了一组方法签名，任何实现了这些方法的类型都被认为实现了该接口。这样，你可以通过接口类型引用具体的实例，实现运行时的多态性。

#### uint型变量值分别为 1，2，它们相减的结果是多少？

会溢出，从最大可能的数开始回绕。如果是32位系统就是2^32-1， 如果是64位系统，结果2^64-1.

#### 讲一下go有没有函数在main之前执行？怎么用？

init函数：

- 不能被其他函数调用
- 没有入参和返回
- 程序运行前执行注册、初始化变量等
- 每个源文件可能有多个init函数，执行顺序不确定
- 不同包的init函数按照导入顺序决定执行顺序

#### 下面这句代码是什么作用，为什么要定义一个空值

```go
type GobCodec struct{
	conn io.ReadWriteCloser
	buf *bufio.Writer
	dec *gob.Decoder
	enc *gob.Encoder
}

type Codec interface {
	io.Closer
	ReadHeader(*Header) error
	ReadBody(interface{})  error
	Write(*Header, interface{}) error
}

var _ Codec = (*GobCodec)(nil)
```

先把nil转换为*GobCodec类型，然后再转换为Codec接口类型，如果转换失败则说明GobCodec没有实现Codec中的所有方法。

#### golang的内存管理的原理清楚吗？简述go内存管理机制。

go内存管理本质上是一个内存池，使用了一个“tcmalloc”（Thread-Caching Malloc）风格的内存分配器，但内部做了很多优化：自动伸缩内存池大小，合理的切割内存块。

>页Page：Go向操作系统申请和释放内存都是以页为单位的。
>span : 内存块，**一个或多个连续的 page 组成一个 span** 。
>sizeclass : 空间规格，**每个 span 都带有一个 sizeclass ，标记着该 span 中的  page 应该如何使用**。
>object : **对象，用来存储一个变量数据内存空间，一个 span 在初始化时，会被切割成一堆等大的 object 。所谓内存分配，就是分配一个 object 出去**。

该分配器将内存分为多个大小的类别，以适应不同大小的对象：

- **小对象**：使用固定大小的内存块进行分配，这些内存块从预分配的页中获得。
- **大对象**：直接从堆中分配，绕过固定大小的内存块机制。

每个 Goroutine 拥有自己的缓存（mcache），用于小对象的快速分配，而较大的对象分配则可能需要锁定和更多的协调。

GC：并发，三色标记清楚、混合写屏障。

#### mutex有几种模式？

在正常模式中，**等待者按照 FIFO 的顺序排队获取锁，但是一个被唤醒的等待者有时候并不能获取 mutex， 它还需要和新到来的 goroutine 们竞争 mutex 的使用权。 新到来的 goroutine 存在一个优势，它们已经在 CPU 上运行且它们数量很多， 因此一个被唤醒的等待者有很大的概率获取不到锁，在这种情况下它处在等待队列的前面。 如果一个 goroutine 等待 mutex 释放的时间超过 1ms，它就会将 mutex 切换到饥饿模式。公平性：否**。

在饥饿模式中，**mutex 的所有权直接从解锁的 goroutine 递交到等待队列中排在最前方的 goroutine。 新到达的 goroutine 们不要尝试去获取 mutex，即使它看起来是在解锁状态，也不要试图自旋， 而是排到等待队列的尾部。公平性：是**。

正常模式下的性能会更好，因为一个 goroutine 能在即使有很多阻塞的等待者时多次连续的获得一个 mutex，饥饿模式的重要性则在于避免了病态情况下的尾部延迟。

#### go如何进行调度的。GMP中状态流转。

GMP。

go进行调度过程：

- 某个线程尝试创建一个新的G，那么这个G就会被安排到这个线程的G本地队列LRQ中，如果LRQ满了，就会分配到全局队列GRQ中；
- 尝试获取当前线程的M，如果无法获取，就会从空闲的M列表中找一个，如果空闲列表也没有，那么就创建一个M，然后绑定M与P运行。
- 进入调度循环：
  - G0进行调度
  - 找到一个合适的G
  - 执行G，完成以后退出

#### Go什么时候发生阻塞？阻塞时，调度器会怎么做

比如系统调用，channel阻塞。

如果是系统调用阻塞，G和M会脱离P，然后P去找一个空闲的M进行绑定，执行P列表中的G或者全局列表的G或者work stealing。

如果是channel阻塞，G会脱离M，然后重新调度新的G放入M。

#### Go中GMP有哪些状态

G的状态：可简化为等待中（系统调用、阻塞），可运行，运行中，暂停（GC）

- **_Gidle**：刚刚被分配并且还没有被初始化，值为0，为创建goroutine后的默认值
- **_Grunnable**： 没有执行代码，没有栈的所有权，存储在运行队列中，可能在某个P的本地队列或全局队列中(如上图)。
- **_Grunning**： 正在执行代码的goroutine，拥有栈的所有权(如上图)。
- **_Gsyscall**：正在执行系统调用，拥有栈的所有权，与P脱离，但是与某个M绑定，会在调用结束后被分配到运行队列(如上图)。
- **_Gwaiting**：被阻塞的goroutine，阻塞在某个channel的发送或者接收队列(如上图)。
- **_Gdead**： 当前goroutine未被使用，没有执行代码，可能有分配的栈，分布在空闲列表gFree，可能是一个刚刚初始化的goroutine，也可能是执行了goexit退出的goroutine(如上图)。
- **_Gcopystac**：栈正在被拷贝，没有执行代码，不在运行队列上，执行权在
- **_Gscan** ： GC 正在扫描栈空间，没有执行代码，可以与其他状态同时存在。

P的状态：空闲，运行中，处于GC被停止，不在使用

- **_Pidle** ：处理器没有运行用户代码或者调度器，被空闲队列或者改变其状态的结构持有，运行队列为空
- **_Prunning** ：被线程 M 持有，并且正在执行用户代码或者调度器(如上图)
- **_Psyscall**：没有执行用户代码，当前线程陷入系统调用(如上图)
- **_Pgcstop** ：被线程 M 持有，当前处理器由于垃圾回收被停止
- **_Pdead** ：当前处理器已经不被使用

M的状态：

- **自旋线程**：处于运行状态但是没有可执行goroutine的线程，数量最多为GOMAXPROC，若是数量大于GOMAXPROC就会进入休眠。
- **非自旋线程**：处于运行状态有可执行goroutine的线程。

#### GMP能不能去掉P层？会怎么样？

不能，如果没有P，那么会依赖全局队列，就会开销很大，比如锁和同步，P的队列是CAS的。此外，如果直接把G放到M，那么要是阻塞，那其他G也不能执行了，就浪费CPU资源了。

#### 如果有一个G一直占用资源怎么办？什么是work stealing算法

GMP调度器采用基于协作的抢占机制，每个G执行10ms，就换其他G执行；但也可能出现其它情况，比如长时间的for循环或垃圾回收时间太长，GO1.14后引入了基于信号的抢占和基于函数调用的抢占机制

work stealing就是假如有个线程空闲，并且持有P，那么就会去全局队列中拿G，大小是队列的一半和队列/GOMAXPROC +1的小的那个。如果没有则会去其他P队列中偷G过来，一般取后面一半。

#### goroutine什么情况会发生内存泄漏？如何避免。

1. **长生命周期的 Goroutine 未能正确退出**：当 Goroutine 因为**阻塞在通道操作、锁等待或其他同步原语上而无法退出时，它们可能会持续占用内存**。
2. **Goroutine 持有的资源未被释放**：**如果 Goroutine 持有对某些资源的引用（如大型数据结构、文件句柄等），并且这些资源在 Goroutine 结束前未被释放或解引用，那么这些资源可能永远不会被垃圾回收**。
3. **使用不当的定时器和 Ticker**：
   如果使用 `time.After` 或 `time.Tick` 并且返回的通道没有被适当处理，可能会导致 Goroutine 泄漏。

如何避免：

1. **确保 Goroutine 可以正确退出**
2. **合理管理 Goroutine 的生命周期**
3. **避免 Goroutine 对资源的无限制持有**
4. **正确使用定时器和 Ticker**
5. **利用工具进行监控和检测**：使用 Go 的 pprof 工具来监控 Goroutine 的数量和状态，帮助识别潜在的内存泄漏。

#### Go GC有几个阶段

目前的go GC采用**三色标记法**和**混合写屏障**技术。

 Go GC有**四**个阶段:

- STW，开启混合写屏障，扫描栈对象；
- 将所有对象加入白色集合，从根对象开始，将其放入灰色集合。每次从灰色集合取出一个对象标记为黑色，然后遍历其子对象，标记为灰色，放入灰色集合；
- 如此循环直到灰色集合为空。剩余的白色对象就是需要清理的对象。
- STW，关闭混合写屏障；
- 在后台进行GC（并发）。

#### go竞态条件了解吗

所谓竞态竞争，就是当**两个或以上的goroutine访问相同资源时候，对资源进行读/写。**比如`var a int = 0`，有两个协程分别对a+=1，我们发现最后a不一定为2.这就是竞态竞争。

我们可以用`go run -race xx.go`来进行检测。通过对临界区加锁或原子操作来解决。

#### 如果若干个goroutine，有一个panic会怎么做

**有一个panic，那么剩余goroutine也会退出，程序退出**。如果**不想程序退出，那么必须通过调用 recover() 方法来捕获 panic 并恢复将要崩掉的程序**。

#### defer可以捕获goroutine的子goroutine吗？

**每个 Goroutine拥有自己的执行堆栈，而 `defer` 只能作用于它被声明的同一函数或方法中。这意味着 `defer` 不能跨 Goroutine 工作，也无法影响或处理从一个 Goroutine 内部启动的其他 Goroutine**。

#### channel 死锁的场景

channel中没数据去读

channel中数据满了去写

往关闭的channel中写数据

解决办法通过select

#### 对已经关闭的chan进行读写会怎么样？

写会panic

读已经关闭的chan能一直读到东西，但是读到的内容根据通道内关闭前是否有元素而不同。

-  如果chan关闭前，**buffer内有元素还未读,会正确读到chan内的值，且返回的第二个bool值（是否读成功）为true**。
- 如果chan关闭前，**buffer内有元素已经被读完，chan内无值，接下来所有接收的值都会非阻塞直接成功，返回 channel 元素的零值，但是第二个bool值一直为false**。

#### channel底层实现？是否线程安全。

channel内部是一个循环链表。内部包含buf, sendx, recvx, lock ,recvq, sendq几个部分。

buf是有缓冲的channel所特有的结构，用来存储缓存数据，是一个循环数组。

- sendx和recvx：这两个索引用于管理 `buf` 数组中的位置。`sendx` 指向下一个数据应该存放的位置，而 `recvx` 指向下一个数据应该被接收的位置。
- lock是个互斥锁；
- recvq和sendq分别是这些是等待接收和等待发送的 goroutine 队列。当一个 goroutine 尝试从空的非缓冲 channel 接收数据，或者尝试向满的非缓冲 channel 发送数据时，它将会被放入相应的队列中阻塞等待。

channel是**线程安全**的。

#### map的底层实现

`map` 是一种基于哈希表的关联数组实现，用于存储键值对。它的核心组件包括：

1. **哈希函数**：用于将键转换成数组索引，确保键值对分布均匀。
2. **数组**：这是哈希表的主体，存储指向键值对的桶（bucket）。
3. **桶（bucket）**：每个桶可以存储多个键值对，以处理哈希冲突。当多个键经过哈希函数处理后落在同一个桶中时，通过链表或者开放寻址法解决冲突。
4. **扩容机制**：当 map 中的元素数量达到一定阈值时，系统会自动进行扩容操作，即创建一个更大的哈希表并重新分配现有的元素，以保持操作的效率。

Go 的 `map` 是非线程安全的，如果在多个 goroutine 中并发读写，需要使用锁（如 `sync.Mutex` 或 `sync.RWMutex`）来保证安全。

#### select的实现原理

在 Go 语言中，`select` 语句允许同时处理多个通道（channel）的发送和接收操作。其工作原理如下：

1. **检查通道状态**：`select` 检查每个 case 语句中的通道是否准备好进行操作（发送或接收）。
2. **随机选择**：如果多个通道同时准备好，`select` 会随机选择一个执行，以保证公平性。
3. **阻塞行为**：如果没有通道准备好，`select` 将阻塞当前 goroutine，直到至少一个通道可用。

这种机制使得 `select` 成为处理并发通道操作的有效工具，特别是在需要对多个通道进行监听和响应时。

#### go的interface怎么实现的

`interface`规定了一组方法签名，但不实现这些方法。任何实现了这些方法的具体类型都可以被视为该接口类型的实例。Go 的接口提供了一种方式来实现多态性，即不同类型的对象可以以相同的方式被处理。

具体实现是通过一个类型指针和数据指针：

1. **类型指针（`type`）**：这是一个指向表示接口具体类型的数据结构的指针。这个数据结构包含了类型的元数据（如类型的名称和包路径）以及与类型相关的方法集合。
2. **数据指针（`data`）**：这是一个指向具体数据的指针。对于值类型（如结构体），它直接指向值的内存地址；对于引用类型（如指针、切片、映射等），它指向实际数据结构的指针。

#### go的reflect 底层实现

`reflect.Type` 和 `reflect.Value`。

1. **reflect.Type**：提供了关于 Go 值的类型信息，包括类型的名称、种类（如 int、slice、struct 等）和可以执行的操作。这个接口通过内部的类型描述符来实现，这些描述符包含了类型的详细元数据。
2. **reflect.Value**：代表一个 Go 值的运行时表示。它持有一个值的实际数据，并可以用来修改值、获取值或调用关联的方法。`reflect.Value` 通过内部存储实际的值（使用空接口 `interface{}`）和类型信息来实现其功能。

#### go的调试/分析工具用过哪些。

go的自带工具链相当丰富，

- go cover : 测试代码覆盖率；
- godoc: 用于生成go文档；
- pprof：用于性能调优，针对cpu，内存和并发；
- race：用于竞争检测；

#### 进程被kill，如何保证所有goroutine顺利退出

在Go语言中，确保一个进程被kill时所有goroutine顺利退出，需要设计一种优雅的退出机制。这通常涉及到信号处理和goroutine之间的协调。以下是一种实现方法：

1. **信号监听**：首先，需要监听操作系统发送的终止信号（如SIGINT或SIGTERM）。可以使用`os/signal`包来监听系统信号。

2. **同步机制**：使用`sync.WaitGroup`或类似机制来跟踪所有正在运行的goroutine。每个goroutine在开始时调用`WaitGroup.Add(1)`，完成时调用`WaitGroup.Done()`。

3. **通知机制**：使用`context.Context`来传递取消信号给所有goroutine。当接收到终止信号时，可以通过调用`cancel()`函数来广播取消事件。

具体实现步骤如下：

```go
package main

import (
    "context"
    "fmt"
    "os"
    "os/signal"
    "sync"
    "syscall"
    "time"
)

func main() {
    // 创建一个监听系统终止信号的channel
    sigs := make(chan os.Signal, 1)
    // 注册要接收的信号，syscall.SIGINT是Ctrl+C，syscall.SIGTERM是kill发送的默认信号
    signal.Notify(sigs, syscall.SIGINT, syscall.SIGTERM)

    // 创建一个context，用来通知goroutine退出
    ctx, cancel := context.WithCancel(context.Background())
    defer cancel() // 确保所有路径上都调用cancel

    // 使用WaitGroup等待所有goroutine完成
    var wg sync.WaitGroup

    // 启动goroutine
    wg.Add(1)
    go func() {
        defer wg.Done()
        doWork(ctx)
    }()

    // 等待信号
    sig := <-sigs
    fmt.Printf("Received signal: %s\n", sig)
    cancel() // 收到信号后取消context

    // 等待所有goroutine清理完毕
    wg.Wait()
    fmt.Println("All goroutines have finished.")
}

func doWork(ctx context.Context) {
    for {
        select {
        case <-ctx.Done():
            fmt.Println("Goroutine exiting...")
            return
        default:
            // 模拟一些工作
            fmt.Println("Goroutine working...")
            time.Sleep(1 * time.Second)
        }
    }
}
```

在这个例子中：
- 当接收到SIGINT或SIGTERM信号时，`main`函数中的`cancel()`被调用，这会使得通过`ctx`传递给`doWork`函数的`ctx.Done()`通道被关闭。
- `doWork`函数中的`select`语句会响应`ctx.Done()`的关闭，从而退出循环并返回，这样goroutine就优雅地结束了。
- `main`函数中的`wg.Wait()`确保主程序等待所有goroutine完成后才继续向下执行，最终输出“All goroutines have finished.”表示所有goroutine已经正确清理并退出。

这种方法可以确保在程序需要强制退出时，所有的资源都能被正确释放，goroutine也能有序地关闭。

#### 说说context包的作用？

Go语言的`context`包主要用于管理和传递取消信号、超时通知和其他请求范围的值。其主要用途包括：

1. **取消信号**：在多个goroutine之间传递取消信号，用于停止操作和释放资源。
2. **超时控制**：设定操作的超时时间，超时后自动发送取消信号。
3. **传递请求相关的数据**：在API的调用链中传递请求特定的数据，如用户身份信息、追踪ID等。

#### defer、panic和recover

1. defer：预定一个函数调用，这个函数会在包含他的函数结束时执行，不管是正常退出还是panic，常用于资源清理，比如关闭文件和数据库连接。如果一个函数中有多个defer，执行顺序为后进先出（栈，以及资源依赖）。
2. panic：触发一个运行时错误，会立刻停止当前函数的运行，逐层向上执行defer语句，除非被recover捕获，用于处理不可恢复的错误。
3. recover：用于捕获或恢复一个pannic，只有在defer中调用panic才有用，会终止panic的连锁反应，返回panic时传递的错误值。

```go
package main

import "fmt"

func riskyFunction() {
    defer func() {
        if r := recover(); r != nil {
            fmt.Println("Recovered from panic:", r)
        }
    }()
    fmt.Println("Performing some task")
    if true {
        panic("something bad happened")
    }
    fmt.Println("This will not be printed")
}

func main() {
    riskyFunction()
    fmt.Println("Program continues after recovery")
}
```

#### go中的slice和数组有什么区别，slice的底层是什么

1. 数组大小在声明时就确定了，并且不能改变
2. 切片可以根据需要动态扩展或收缩
3. 数组是值类型，赋值给新变量，会进行整个数组的改变；切片是引用类型，赋值时不会拷贝数据本身，而是拷贝对底层数据的引用

切片的底层是一个数组，切片结构体包括三个元素：

1. 指针：指向底层数组的第一个元素的位置
2. 容量：当前底层数组所能包含的最大元素数量
3. 长度：当前底层数组中的元素数量

切片的动态扩展是通过创建一个更大的数组并复制现有元素来实现的。这个过程通常由`append`函数自动管理。当切片的元素超过其容量时，Go运行时会分配一个新的数组，一般是当前容量的两倍，然后将原有数据复制到新数组中，从而实现切片的扩容。

```go
package main

import "fmt"

func main() {
    arr := [5]int{1, 2, 3, 4, 5} // 数组
    slc := []int{1, 2, 3, 4, 5} // 切片

    arrSlc := arr[:] // 从数组创建切片
    slc2 := slc[:] // 创建切片的另一个视图

    fmt.Println(arr) // 输出数组
    fmt.Println(slc) // 输出切片
    fmt.Println(arrSlc) // 输出从数组创建的切片
    fmt.Println(slc2) // 输出切片的另一个视图
}
```

