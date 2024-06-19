### 基础语法

#### `=` 和 `:=` 的区别

=是赋值变量，:=是定义并赋值变量。

#### 指针的作用

指向任意变量的地址，它所指向的地址在32位或64位机器上分别**固定**占4或8个字节。

- 获取变量的值（*ptr）
- 改变变量的值
- 使用指针代替值作为方法接收器（指定了方法绑定到的类型）
  - **值接收器** 使用结构体类型的副本调用方法。这意味着**对接收器的任何修改都不会影响原始结构体实例**。
  - **指针接收器** 使用指向结构体的指针，这样方法中**对接收器的任何修改都会反映到原始结构体实例上**。

#### Go 允许多个返回值吗

可以。通常函数除了一般返回值还会返回一个error。

#### Go 有异常类型吗？

Go使用`error`类型来处理错误，这与其他语言中的异常处理（如Java的`try...catch`）不同。Go的错误处理倾向于显式地检查错误，这样做可以增加代码的可读性和控制性，同时避免了异常处理可能引入的复杂性和性能开销。

可以通过`errors.New()`，用于创建一个简单的错误实例。

#### 什么是协程（Goroutine）

协程是**用户态轻量级线程**，由调度器对G、M、P进行调度实现高并发。通常在函数前加上go关键字就能实现并发。一个Goroutine会以一个很小的栈启动2KB或4KB，当遇到栈空间不足时，栈会**自动伸缩**， 因此可以轻易实现成千上万个goroutine同时启动。

#### 如何高效地拼接字符串

字符串拼接方法有：+ , fmt.Sprintf , strings.Builder, strings.Join, bytes.Buffer, 

1 "+"

使用`+`操作符进行拼接时，会**对字符串进行遍历，计算并开辟一个新的空间来存储原来的两个字符串**。

2 fmt.Sprintf

由于采用了接口参数，必须要用反射获取值，因此有性能损耗。

3 strings.Builder+WriteString()+String()

内部实现是指针+切片，同时String()返回拼接后的字符串，它是直接把[]byte转换为string，从而避免变量拷贝。

4 strings.join

`strings.join`也是基于`strings.builder`来实现的,并且可以自定义分隔符，会根据传入切片长度提前进行容量分配可以减少内存分配，很高效。

5 bytes.Buffer+Write()

`bytes.buffer`底层也是一个`[]byte`切片。

性能：strings.Join ≈ strings.Builder > bytes.Buffer > "+" > fmt.Sprintf

```go
func main(){
	a := []string{"a", "b", "c"}
	//方式1：+
	ret := a[0] + a[1] + a[2]
	//方式2：fmt.Sprintf
	ret := fmt.Sprintf("%s%s%s", a[0],a[1],a[2])
	//方式3：strings.Builder
	var sb strings.Builder
	sb.WriteString(a[0])
	sb.WriteString(a[1])
	sb.WriteString(a[2])
	ret := sb.String()
	//方式4：bytes.Buffer
	buf := new(bytes.Buffer)
	buf.Write(a[0])
	buf.Write(a[1])
	buf.Write(a[2])
	ret := buf.String()
	//方式5：strings.Join
	ret := strings.Join(a,"")
}
```

#### 什么是 rune 类型

rune是go中int32的别名，几乎在所有方面等同于int32，用来区分字符值和整数值。常规的英文字符是ascii码是通过一个字节( 2^8 其实还有一位是不用的 )来存储，中国文字、日本文字常用文字就有4000+，通过2^8肯定表达不了，于是有了Unicode字符。go语言的编码是按照UTF-8编码规则，UTF使用1至4个字节来表示一个字符，所以在go语言中引进了rune的概念。在我们对字符串进去处理的时候只需要将字符串通过range去遍历，会按照rune为单位自动去处理，极其便利。

#### 如何判断 map 中是否包含某个 key 

将map[key]赋值给匿名变量和ok，通过ok的值来判断。

```go
var sample map[int]int
if _, ok := sample[10]; ok {

} else {

}
```

#### Go 支持默认参数或可选参数吗

不支持，支持使用参数切片数组实现可变参数。

```go
// 这个函数可以传入任意数量的整型参数
func sum(nums ...int) {
    total := 0
    for _, num := range nums {
        total += num
    }
    fmt.Println(total)
}
```

#### defer 的执行顺序

defer在return之后，但在函数退出之前执行。多个defer语句会被添加到栈中，也就是后进先出（LIFO），后面写的defer语句会先执行。

```go
func test() int {
	i := 0
	defer func() {
		fmt.Println("defer1")
	}()
	defer func() {
		i += 1
		fmt.Println("defer2")
	}()
	return i
}

func main() {
	fmt.Println("return", test())
}
// defer2
// defer1
// return 0
// 对于无名返回，go会创建一个临时变量保存返回值，由于defer在return后执行，因此是0
```

对于有名返回，defer是有可能改变其值的。对于有名返回值，不会为其创建临时变量保存。

```go
func test() (i int) {
	i = 0
	defer func() {
		i += 1
		fmt.Println("defer2")
	}()
	return i
}

func main() {
	fmt.Println("return", test())
}
// defer2
// return 1
```

#### 如何交换 2 个变量的值

对于变量而言`a,b = b,a`； 对于指针而言`*a,*b = *b, *a`

#### Go 语言 tag 的用处

tag可以为结构体成员提供属性。常见的：

- json/toml序列化或反序列化时字段的名称
- db: sqlx模块中对应的数据库字段名

#### 如何获取一个结构体的所有tag

使用反射

```go
import reflect
type Author struct {
	Name         int      `json:Name`
	Publications []string `json:Publication,omitempty`
}

func main() {
	t := reflect.TypeOf(Author{})
	for i := 0; i < t.NumField(); i++ {
		name := t.Field(i).Name
		s, _ := t.FieldByName(name)
		fmt.Println(name, s.Tag)
	}
}
```

`reflect.TypeOf`方法获取对象的类型，之后`NumField()`获取结构体成员的数量。 通过`Field(i)`获取第i个成员的名字。 再通过其`Tag` 方法获得标签。

#### 如何判断 2 个字符串切片（slice) 是相等的

1. 自己手写遍历比较
2. 使用反射，`reflect.DeepEqual()` ， 但反射非常影响性能，并且会比较切片的底层数组是否相同，可能影响结果。

#### 结构体打印时，`%v` 和 `%+v` 的区别

下面是一个示例代码，演示了使用`%v`、`%+v`和`%#v`格式化输出结构体成员的值、名称和值的方法：

```go
package main

import "fmt"

type Person struct {
	Name    string
	Age     int
	Country string
}

func main() {
	p := Person{
		Name:    "Alice",
		Age:     30,
		Country: "USA",
	}

	// %v 输出结构体各成员的值
	fmt.Printf("Using %%v: %v\n", p)

	// %+v 输出结构体各成员的名称和值
	fmt.Printf("Using %%+v: %+v\n", p)

	// %#v 输出结构体名称和结构体各成员的名称和值
	fmt.Printf("Using %%#v: %#v\n", p)
}
```

在上面的示例中，结构体`Person`有三个成员：`Name`、`Age`和`Country`。我们创建了一个`Person`类型的实例`p`，并使用`%v`、`%+v`和`%#v`格式化输出不同类型的信息。

运行这段代码后，你会看到类似下面的输出：

```
Using %v: {Alice 30 USA}
Using %+v: {Name:Alice Age:30 Country:USA}
Using %#v: main.Person{Name:"Alice", Age:30, Country:"USA"}
```

- `%v`输出了结构体`Person`各成员的值
- `%+v`输出了结构体各成员的名称和值
- `%#v`输出了结构体名称和结构体各成员的名称和值。

#### Go 语言中如何表示枚举值(enums)

在Go语言中，没有内置的枚举类型，但是可以使用`const`常量和`iota`（从0开始）来模拟枚举值。

```go
// 定义一个枚举类型
type Color int

const (
    Red Color = iota
    Green
    Blue
)
```

#### 空 struct{} 的用途

- 用map模拟set，就要把值置为struct{}

```go
type Set map[string]struct{}

func main() {
	set := make(Set)

	for _, item := range []string{"A", "A", "B", "C"} {
		set[item] = struct{}{}
	}
	fmt.Println(len(set)) // 3
	if _, ok := set["A"]; ok {
		fmt.Println("A exists") // A exists
	}
```

- 仅有方法的结构体
- **空结构体可以用作通道的元素，用于实现某些特殊的通信模式，例如只关注通道是否关闭而不传输任何数据**。

#### **go里面的int和int32是同一个概念吗**

go语言中的int的大小是和操作系统位数相关的，如果是32位操作系统，int类型的大小就是4字节。如果是64位操作系统，int类型的大小就是8个字节。除此之外uint也与操作系统有关。

int8占1个字节，int16占2个字节，int32占4个字节，int64占8个字节。

#### channel

channel是一个数据类型，可以看作**管道**，主要用来**解决go协程的同步问题以及go协程之间数据共享**（数据传递）的问题。

<img src="https://cdn.nlark.com/yuque/0/2022/png/26269664/1650606672440-8838ebc8-89bd-48af-9481-3e402623a5da.png?x-oss-process=image%2Fwatermark%2Ctype_d3F5LW1pY3JvaGVp%2Csize_19%2Ctext_5YiY5Li55YawQWNlbGQ%3D%2Ccolor_FFFFFF%2Cshadow_50%2Ct_80%2Cg_se%2Cx_10%2Cy_10%2Fformat%2Cwebp%2Fresize%2Cw_662%2Climit_0">

创建channel：**chan**是创建channel所需使用的关键字。Type 代表指定channel收发数据的类型。

```go
make(chan Type)  //等价于make(chan Type, 0)
make(chan Type, capacity)
```

- 当参数capacity= 0 时，channel 是无缓冲阻塞读写的
- 当capacity > 0 时，channel 有缓冲、是非阻塞的，直到写满 capacity个元素才阻塞写入。

channel接收和发送数据：

```go
channel <- value      //发送value到channel
<-channel             //接收并将其丢弃
x := <-channel        //从channel中接收数据，并赋值给x
x, ok := <-channel    //功能同上，同时检查通道是否已关闭或者是否为空
```

默认情况下，channel接收和发送数据都是阻塞等待的，除非另一端已经准备好，这样就使得goroutine同步变的更加的简单，而**不需要显式的lock和条件变量**。

**无缓冲的channel**：在接收前没有能力保存任何数据值的通道。这种类型的通道**要求发送goroutine和接收goroutine同时准备好，才能完成发送和接收操作。否则，通道会导致先执行发送或接收操作的 goroutine 阻塞等待**。

**有缓冲的channel：**一种在被接收前能存储一个或者多个数据值的通道。这种类型的通道**并不强制要求 goroutine 之间必须同时完成发送和接收**。通道会阻塞发送和接收动作的条件也不同。**只有通道中没有要接收的值时，接收动作才会阻塞。只有通道没有可用缓冲区容纳被发送的值时，发送动作才会阻塞**。

**可以使用close去关闭channel**。

**单向channel**：单向 channel 可以是只发送或只接收：

- 只发送 channel 的类型为 `chan<- Type`，表示这个 channel 只能用来发送类型为 `Type` 的数据。
- 只接收 channel 的类型为 `<-chan Type`，表示这个 channel 只能用来接收类型为 `Type` 的数据。

```go
func produce(ch chan<- int) {
    for i := 0; i < 10; i++ {
        ch <- i // 发送数据
    }
    close(ch)
}

func consume(ch <-chan int) {
    for value := range ch {
        fmt.Println("Received:", value)
    }
}

func main() {
    ch := make(chan int)
    go produce(ch)
    consume(ch)
}
```

### 实现原理

#### init() 函数是什么时候执行的

init()在main()之前执行。

init()函数是go初始化的一部分，由**runtime初始化每个导入的包，初始化不是按照从上到下的导入顺序，而是按照解析的依赖关系，没有依赖的包最先初始化**。

- 每个包首先初始化包作用域的常量和变量（常量优先于变量），然后执行包的`init()`函数。
- 同一个包，甚至是同一个源文件可以有多个`init()`函数。
- `init()`函数没有入参和返回值，不能被其他函数调用，同一个包内多个`init()`函数的执行顺序不作保证。

执行顺序：import –> const –> var –>`init()`–>`main()` 

一个文件可以有多个`init()`函数！

#### 如何知道一个对象是分配在栈上还是堆上

**编译器自动决定一个对象是分配在栈上还是堆上，这主要基于逃逸分析（escape analysis）**。逃逸分析**在编译时进行**，目的是确定数据分配的位置（栈或堆）以优化内存使用和性能。

栈上分配

- **如果一个对象在函数内部创建，并且它不会在函数外部被引用，那么这个对象通常会被分配在栈上**。
- 栈上分配的对象在函数执行完毕后会自动被清理，这种方式的内存分配和回收效率非常高。

堆上分配

- **如果对象在函数外部仍然存在引用，或者因为其大小不确定或太大，它就可能被分配到堆上**。
- 堆上的对象需要通过垃圾回收器来管理，这可能会引入额外的性能开销。

总体来说就是一个变量离开其作用域没有被引用，则优先分配给栈，否则分配给堆。但是变量类型大小不确定等情况也可能发生逃逸。

**编译时标志**：使用`go build -gcflags='-m'`命令可以看到编译器的逃逸分析报告，其中会标明哪些对象逃逸到堆上。

#### 2 个 interface 可以比较吗

两个接口（interface）类型的值是可以比较的，但有特定的规则和限制。

1. **相同类型的动态值**：如果两个接口类型的动态值是相同类型，并且这个类型支持比较（例如基本类型如`int`、`string`等），那么可以将这两个接口值进行比较。比较的结果基于它们的动态值。
2. **不同类型的动态值**：如果两个接口的动态值类型不同，即使它们的实际值相同，比较的结果也是`false`。
3. **零接口值**：如果两个接口都是零值（即它们的动态类型和动态值都为`nil`），它们是相等的。
4. **一个接口值为nil**：如果一个接口值为`nil`而另一个不是，它们不相等。

#### 2 个 nil 可能不相等吗

**两个nil只有在类型相同时才相等**，比如一个变量是指针类型的nil，一个是接口类型的nil，那么他们不相等。

#### Go 语言GC(垃圾回收)的工作原理

1.3标记清除

1.5三色标记

1.7并行栈

1.8混合写屏障

1.9彻底移除暂停程序的重新扫描栈

#### 函数返回局部变量的指针是否安全

和c++不一样，在Go里面返回局部变量的指针是安全的。因为Go会进行**逃逸分析**，如果发现局部变量的作用域超过该函数则会**把指针分配到堆区**，避免内存泄漏。

#### 非接口的任意类型 T() 都能够调用 `*T` 的方法吗？反过来呢

如果T是可寻址的，可以调用*T的方法，反过来也可以，因为指针可以解引用。

#### go slice是怎么扩容的

一个切片在Go中是由三个部分组成的：

1. **指针**：指向底层数组的第一个元素。
2. **长度**（length）：切片中元素的数量。
3. **容量**（capacity）：从切片的起始元素开始，底层数组中可用的元素数量。

扩容的过程大致如下：

1. **新容量的计算**：
   1. 在Go 1.18之前，切片的扩容策略相对简单：
      - **当切片的容量小于1024时，新的容量通常是旧容量的两倍。**
      - **当切片的容量大于或等于1024时，新的容量会增加旧容量的25%（即增长因子为1.25）。**
   2. 从Go 1.18开始，扩容策略进行了调整，以更好地适应不同大小的切片：
      - **当切片的容量小于256时，新的容量仍然是旧容量的两倍。**
      - **当切片的容量大于或等于256时，新的容量计算方式变为 `newcap = oldcap + (oldcap + 3*256)/4`。这种方法相比以前更加复杂，其设计目的是在保持较快增长的同时，更加平滑地过渡到较大的容量**。
   3. 当然如果期望容量大于了当前容量的两倍，则会等于期望容量。
2. **分配新数组**：根据计算出的新容量，分配一个新的底层数组。
3. **复制旧元素**：将原切片中的元素复制到新的底层数组中。
4. **更新切片描述符**：更新切片的指针、长度和容量，使其指向新的底层数组。

扩容是昂贵的，如果预先知道切片的大小，应该在make的时候标明。

#### 无缓冲的 channel 和有缓冲的 channel 的区别

对于无缓冲区channel：发送的数据如果没有被接收方接收，那么**发送方阻塞；**如果一直接收不到发送方的数据，**接收方阻塞**；

有缓冲的channel：发送方在缓冲区满的时候阻塞，接收方不阻塞；接收方在缓冲区为空的时候阻塞，发送方不阻塞。

#### 为什么有协程泄露

协程泄漏是指协程创建之后没有得到释放。主要原因有：

1. 下面两个或三个都可以归结为无限期等待某事件
2. 缺少接收器，导致发送阻塞
3. 缺少发送器，导致接收阻塞
4. **死锁**：多个协程由于竞争资源导致死锁。
5. **资源未释放**：例如，协程打开的文件或网络连接没有关闭，可能导致资源长时间占用。

#### Go 可以限制运行时操作系统线程的数量吗？ 常见的goroutine操作函数有哪些

使用**runtime.GOMAXPROCS(num int)可以设置线程数目，但这个数目是同时执行go代码的线程数量，不包括被阻塞的线程**。该值默认为CPU逻辑核数，如果设的太大，会引起频繁的线程切换，降低性能。**对于 CPU 密集型的任务，若该值过大，例如设置为 CPU 逻辑核数的 2 倍，会增加线程切换的开销，降低性能。对于 I/O 密集型应用，适当地调大该值，可以提高 I/O 吞吐率**。

- **runtime.Gosched()，用于让出CPU时间片，让出当前goroutine的执行权限，调度器安排其它等待的任务运行，并在下次某个时候从该位置恢复执行**。
- **runtime.Goexit()，调用此函数会立即使当前的goroutine的运行终止（终止协程）**，而其它的goroutine并不会受此影响。**runtime.Goexit在终止当前goroutine前会先执行此goroutine的还未执行的defer语句。请注意千万别在主函数调用runtime.Goexit，因为会引发panic**。

#### 如何控制协程数目

可以使用带缓冲区的channel来控制：

```go
var wg sync.WaitGroup  // 等待一组协程执行完成
ch := make(chan struct{}, 1024)
for i:=0; i<20000; i++{
	wg.Add(1)		   // 增加waitGroup的计数器，表示有一个新的协程需要等待其完成
	ch<-struct{}{}
	go func(){
		defer wg.Done() // 减少waitGroup的计数器
		<-ch
	}
}
wg.Wait()				// 等待所有注册的协程完成
```

还可以用协程池，原理和上面的一样。

