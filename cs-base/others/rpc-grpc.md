### RPC

分布式计算中，**远程过程调用**（英语：Remote Procedure Call，RPC）**是一个计算机通信协议（也可以说是一种思想，一种框架）**。该协议允许**运行于一台计算机的程序调用另一个地址空间（通常为一个开放网络的一台计算机）的子程序，而程序员就像调用本地程序一样，无需额外地为这个交互作用编程（无需关注细节）**。RPC是一种**服务器-客户端（Client/Server）模式**，经典实现是一个通过发送请求-接受回应进行信息交互的系统。

RPC是一种进程间通信的模式，程序分布在不同的地址空间里。**如果在同一主机里，RPC可以通过不同的虚拟地址空间（即便使用相同的物理地址）进行通讯，而在不同的主机间，则通过不同的物理地址进行交互**。许多技术（通常是不兼容）都是基于这种概念而实现的。

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/202407091441266.png"/>

#### 为什么要RPC

解耦。本机主要运行的是A功能，但是A功能的过程中会需要B功能，但是B功能不太属于A功能范围之类的事情，那么就会借助RPC去请求实现B功能的机器。

#### HTTP和RPC

RPC是一种思想、框架。HTTP可以是实现RPC的一种方式，比如gRPC就是基于HTTP2实现的。

**HTTP与RPC的区别**

1. **通信模型**：
   - **HTTP**：是一种基于请求-响应模型的协议，主要用于客户端与服务器之间的通信。工作在应用层，是一种通用的协议，可以用于各种类型的通信（如浏览网页、RESTful API等）。**HTTP请求通常用于获取或提交资源，如网页、文件等**。
   - **RPC**：工作在更高的抽象层次，直接支持函数调用的语义，通常用于构建分布式系统和微服务架构。是一种**通过网络调用远程服务的方法，旨在使远程服务调用看起来就像本地调用一样。RPC隐藏了网络通信的细节，使开发者可以专注于业务逻辑**。
2. **数据格式**：
   - **HTTP**：**通常使用文本格式（如HTML、XML、JSON）**进行数据传输。**HTTP本身不规定数据格式，但在RESTful API中，JSON是最常用的数据格式**。
   - **RPC**：**通常使用二进制格式（如Protocol Buffers、Thrift）**进行数据传输，以提高效率和性能。
3. **性能**：
   - **HTTP**：由于其通用性和文本格式，可能会有较高的开销，特别是在频繁的短消息通信中。
   - **RPC**：通常使用**高效的二进制序列化格式，减少了网络传输的开销，性能更高**。
4. **协议复杂度**：
   - **HTTP**：相对简单，广泛使用，有成熟的生态系统和工具支持。
   - **RPC**：实现较为复杂，**需要处理序列化、反序列化、网络传输、错误处理**等多个方面。

#### 为什么在有了HTTP之后我们还需要RPC

1. **效率和性能**：RPC通常使用高效的二进制序列化格式，传输效率更高，适合高性能和低延迟的场景。
2. **开发便利性**：RPC使得远程调用像本地调用一样简单，隐藏了网络通信的复杂性，缩短了开发周期，减少了错误。
3. **协议和平台独立性**：RPC框架（如gRPC、Thrift）通常支持多种编程语言和平台，使得跨语言、跨平台的系统集成更加容易。
4. **功能丰富**：现代RPC框架提供了很多高级功能，如负载均衡、服务发现、错误重试、流式传输等，这些功能在HTTP协议中需要额外实现。
5. **微服务架构**：在微服务架构中，服务之间的通信频繁且复杂，RPC提供了更高效和灵活的方式来实现服务间的调用和协作。

#### 提高rpc的性能

1. 参数和结果传输，序列化和反序列化
2. 网络I/O传输

### gRPC

#### 概述

gRPC 是谷歌推出的一个开源、高性能的 RPC 框架。**默认情况下使用 protoBuf 进行序列化和反序列化，并基于 HTTP/2 传输报文，带来诸如多请求复用一个 TCP 连接(所谓的多路复用)、双向流、流控、头部压缩等特性。gRPC 目前提供 C、Go 和 JAVA 等语言版本，对应 gRPC、gRPC-Go 和 gRPC-JAVA 等开发框架**。

在 gRPC 中，**开发者可以像调用本地方法一样，通过 gRPC 的客户端调用远程机器上 gRPC 服务的方法，gRPC 客户端封装了 HTTP/2 协议数据帧的打包、以及网络层的通信细节，把复杂留给框架自己，把便捷提供给用户**。gRPC 基于这样的一个设计理念：**定义一个服务，及其被远程调用的方法(方法名称、入参、出参)。在 gRPC 服务端实现这个方法的业务逻辑，并在 gRPC 服务端处理远程客户端对这个 RPC 方法的调用。在 gRPC 客户端也拥有这个 RPC 方法的存根(stub)。gRPC 的客户端和服务端都可以用任何支持 gRPC 的语言来实现**，例如一个 gRPC 服务端可以是 C++语言编写的，以供 Ruby 语言的 gRPC 客户端和 JAVA 语言的 gRPC 客户端调用，如下图所示：

<img src="https://mmbiz.qpic.cn/mmbiz/j3gficicyOvavKkbzEXh8bBOTrlaYZEoZtOhjEJJB8LfMW2KvDRgvTdfYVhTf2HFaB2FemtsfsymPZdLNGt0wj7g/640?wx_fmt=other&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1">

**gRPC 默认使用 ProtoBuf 对请求/响应进行序列化和反序列化，这使得传输的请求体和响应体比 JSON 等序列化方式包体更小、更轻量**。gRPC 基于 HTTP/2 协议传输报文，HTTP/2 具有多路复用、头部压缩等特性，基于 HTTP/2 的帧设计，实现了多个请求复用一个 TCP 连接，基本解决了 HTTP/1.1 的队头阻塞问题，相对 HTTP/1.1 带来了巨大的性能提升。

#### HTTP2

**HTTP1.1存在的问题**

1. **队头阻塞：** HTTP 的队头阻塞等特性导致基于 HTTP 的应用程序性能有较大影响。**队头阻塞是指顺序请求的一个请求必须处理完才能处理后续的其他请求，当一个请求被阻塞时会给应用程序带来延迟**。虽然 HTTP/1.1 提供了流水线(request pipeline)的请求操作，但是由于受到 HTTP 自身协议的限制，无法消除 HTTP 的队头阻塞带来的延迟。**为了减少延迟，需要 HTTP 的客户端与服务器建立多个连接实现并发处理请求，降低延迟。然而，在高并发情况下，大量的网络连接可能耗尽系统资源，可以使用连接池模式只维持固定的连接数可以防止服务的资源耗尽**。连接池连接数的设置在对性能要求极高的应用程序也是一个挑战，需要根据实际机器配置的压测情况确定。
2. **头字段重复并且冗余：**HTTP 头字段重复且冗长，导致网络传输不必要的冗余报文，以及初始 TCP 拥塞窗口很快被填满。一个 TCP 连接处理大量请求是会导致较大的延迟。

HTTP/2 通过优化 HTTP 的报文定义，**允许同一个网络连接上并发交错的处理请求和响应，并通过减少 HTTP 头字段的重复传输、压缩 HTTP 头，提高了处理性能。HTTP 每次网络传输会携带通信的资源、浏览器属性等大量冗余头信息，为了减少这些重复传输的开销，HTTP/2 会压缩这些头部字段**：

1. 基于 HTTP/2 协议的客户端和服务器**使用"头部表"来跟踪与存储发送的键值对**，对于相同的键值对数据，不用每次请求和响应都发送；
2. 头部表在 HTTP/2 的连接有效期内一直存在，由客户端和服务器共同维护更新；
3. 每个新的 HTTP 头键值对要么追加，要么替换头部表原来的值。

举个例子，有两个请求，**在 HTTP/1.x 中，请求 1 和请求 2 都要发送全部的头数据；在 HTTP/2 中，请求 1 发送全部的头数据，请求 2 仅仅发送变更的头数据，这样就可以减少冗余的数据，降低网络开销**。如下图所示：

![图片](https://mmbiz.qpic.cn/mmbiz/j3gficicyOvavKkbzEXh8bBOTrlaYZEoZtAs9kyiblXlAUlKATmEKVpA5Rd4rB6MxrojfD2mGcuba2nibpyWKIyk2g/640?wx_fmt=other&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

这里再举个例子说明 HTTP/1.x 和 HTTP/2 处理请求的差异，浏览器打开网络要请求/index.html、styles.css 和/scripts.js 三个文件，**基于 HTTP/1.x 建立的连接只能先请求/index.html,得到响应后再请求 styles.css，得到响应后再获取/scripts.js。而基于 HTTP/2 一个网络连接在获取/index.html 后,可以同时获取 styles.css 和/scripts.js 文件，如下图所示**：

![图片](https://mmbiz.qpic.cn/mmbiz/j3gficicyOvavKkbzEXh8bBOTrlaYZEoZt4mia8JYicHXib9X5467J2nvR51Em6scUKeXVJPHOc6Ufriau1DrOibfDoAQ/640?wx_fmt=other&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

**HTTP/2 对服务资源和网络更友好，相对与 HTTP/1.x，处理同样量级的请求，HTTP/2 的需要建立的 TCP 连接数更少。这主要得益于 HTTP/2 使用二进制数据帧来传输数据，使得一个 TCP 连接可以同时处理多个请求而不用等待一个请求处理完成再处理下一个**。从而充分发掘了 TCP 的并发能力。

#### gRPC协议

gRPC 基于 **HTTP/2/协议进行通信，使用 ProtoBuf 组织二进制数据流**，gRPC 的协议格式如下图：

![图片](https://mmbiz.qpic.cn/mmbiz_png/j3gficicyOvavKkbzEXh8bBOTrlaYZEoZtXibqTP5VmmxZ4bqToibJ5HeNPl4OtC4Ez4DuQg8Im0AeBb904tqnBaPg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

从以上图可知，**gRPC 协议在 HTTP 协议的基础上，对 HTTP/2 的帧的有效包体(Frame Payload)做了进一步编码：gRPC 包头(5 字节)+gRPC 变长包头**，其中：

1. 5 字节的 gRPC 包头由：1 字节的压缩标志(compress flag)和 4 字节的 gRPC 包头长度组成；
2. **gRPC 包体长度是变长的，其是这样的一串二进制流：使用指定序列化方式(通常是 ProtoBuf)序列化成字节流，再使用指定的压缩算法对序列化的字节流压缩而成的。如果对序列化字节流进行了压缩，gRPC 包头的压缩标志为 1**。

### ProtoBuf

Proto Buffer 是一种语言中立的、平台中立的、可扩展的**序列化结构数据**的方法。**序列化指的是将一个数据结构或者对象转换为某种能被跨平台识别的字节格式，以便进行跨平台存储或者网络传输**。常见的序列化结果有JSON、Protobuf、XML、YAML等。

Protobuf 所具备的特性：

- **语言中立与平台中立**： Protobuf 不依赖于某一种特殊的编程语言或者操作系统的机制，意味着我们可以在多种编程环境中直接使用。（**大部分序列化机制其实都具有这个特性，但是某些编程语言提供了内置的序列化机制，这些机制可能只在该语言的生态系统内有效**，例如 Python 的 pickle 模块）
- **可拓展**：Protobuf 可以在不破坏现有代码的情况下，更新消息类型。具体表现为**向后兼容与向前兼容**。
- **更小更快：**序列化的目的之一是进行网络传输，在传输过程中数据流越小传输速度自然越快，可以整体提升系统性能。**Protobuf 利用字段编号与特殊的编码方法巧妙地减少了要传递的信息量，并且使用二进制格式，相比于 JSON 的文本格式，更节省空间**。

使用ProtoBuf的基本流程：

1.**定义数据结构**：首先，**开发者使用.proto文件来定义数据结构。这个文件是一种领域特定语言（DSL），用来描述数据消息的结构，包括字段名称、类型（如整数、字符串、布尔值等）、字段标识号等等**。

```protobuf
syntax = "proto3";
message Person {
  string name = 1;
  int32 id = 2;
  string email = 3;
}
```

> **为什么需要额外定义 proto 文件呢？**Proto Buffer 能够利用该文件中的定义，去做很多方面的事情，**例如生成多种编程语言的代码方便跨语言服务通信，例如借助字段编码与类型来压缩数据获得更小的字节流，再例如提供一个更加准确类型系统，为数据提供强类型保证。 听上去或许比较抽象，这里先用一个简单的例子来说明 proto 文件的好处之一：如果我们采用 JSON 进行序列化，由于 JSON 的类型比较宽松，比如数字类型不区分整数和浮点数，这可能会导致在不同的语言间交换数据时出现歧义，而 proto 中我们可以定义 float int32 等等更加具体的类型**。

2.**生成工具函数代码**：接下来，我们需要使用 protobuf 编译器（protoc）处理.proto文件，生成对应目标语言（如C++、Java、Python等）的源代码。这些代码包含了数据结构的类定义（称为消息类）以及用于**序列化和反序列化**的函数。 

3.**使用生成的代码进行网络传输**：当需要发送数据或者接收到消息对象时，我们就可以利用生成代码中所提供的序列化与反序列化函数对数据进行处理了。

值得注意的是，在利用 Protobuf 进行网络数据传输时，**确保通信双方拥有一致的** `.proto` **文件至关重要**。缺少了相应的 `.proto` 文件，通信任何一方都无法生成必要的工具函数代码，进而无法解析接收到的消息数据。与 JSON 这种文本格式不同，后者即便在没有 `JSON.parse` 反序列化函数的情况下，人们仍能大致推断出消息内容。相比之下，Protobuf 序列化后的数据是**二进制字节流**，它并不适合人类阅读，且必须通过特定的反序列化函数才能正确解读数据。Protobuf 的这种设计在提高数据安全性方面具有优势，因为缺少 `.proto` 文件就无法解读数据内容。然而，这也意味着在通信双方之间需要维护一致的 `.proto` 文件，随着项目的扩展，这可能会带来额外的维护成本。

#### ProtoBuf的语法

```protobuf
syntax = "proto3";  // 指定使用的语法版本, 默认情况下是 proto2

// 定义包含四个字段的消息 User
message User {
   uint32 id = 1; // 字段 id 的类型为 uint32，编号 1
   string name = 2; // 字段 name 的类型为 string，编号 2
   string email = 3; // ... 
   string password = 4;
}
```

- 需要注意的是` syntax = "proto3";` 必须是文件的**第一个非空的非注释行**。

在声明 protobuf 文件的语法版本之后，我们就可以开始定义消息结构。在定义字段时，必须指明**字段的类型，名称以及一个唯一的字段编号**。

- **类型**：proto 提供了丰富的类型系统，包括无符号整数 `uint32` 、有符号整数 `sint32`、浮点数 `float` 、字符串、布尔等等，你可以在[这个链接](https://protobuf.dev/programming-guides/proto3/#scalar)中查看完整的类型描述。当然，除了为字段指定基本的类型意外，你还可以为其指定 `enum` 或是自定义的消息类型。

- **字段编号**：**每个字段都需要一个唯一的数字标识符，也就是字段编号。这些编号在序列化和反序列化过程中至关重要，因为他们将替代字段名称出现在序列化后二进制数据流中。在使用 JSON 序列化数据时，其结果中往往包含人类刻度的字段名称，例如 `{ "id": "123456" }` ，但是在 protobuf 中，序列化后的结果中只会包含字段编号而非字段名称，例如在本例中， `id` 的编号为 1，那我序列化后的结果只会包含 1 而非 `id` 。这种方法有点类似于 HTTP 的头部压缩，可以显著减少传输过程中的数据流大小。 事实上字段编号的使用是 proto 中非常重要的一环，在使用中务必遵循以下原则**：

  - 字段编号一旦被分配后就不应更改，这是为了保持向后兼容性。
  - 编号在 `[1,15]` 范围内的字段编号在序列化时只占用一个字节。因此，为了优化性能，对于频繁使用的字段，尽可能使用该范围内的数字。同时也要为未来可能添加的常用字段预留一些编号（不要一股脑把 15 之内的编号都用了！）
  - 字段编号从 1 开始，最大值是 29 位，字段号 `19000,19999` 是为 Protocol Buffers 实现保留的。如果在消息定义中使用这些保留字段号之一，协议缓冲区编译器将报错提示。

- （可选）**字段标签**：除了上述三个必须设置的元素外，你还可以选择性设置字段标签：

  - `optional` : 之后字段被显式指定时，才会参与序列化的过程，否则该字段将保持默认值，并且不会参与序列化。在 proto3 中所有字段默认都是可选的，并不需要使用这个关键字来声明字段，除非在某些情况下我们需要区分字段是否被设置过。在 proto3 中，如果字段未被设置，它将不会包含在序列化的消息之中。在 JavaScript 中，如果一个字段被指定为 optional 并且没有设置值，在解析后的对象将不会包含该字段（如果没有指定 optional 将会包含该字段的默认值）。
  - `repeated`：以重复任意次数（包括零次）的字段。它们本质上是对应数据类型列表的动态数组。
  - `map`：成对的键/值字段类型，语法类似 Typescript 中的 `Record` 。

- **保留字段**：如果你通过完全删除字段或将其注释来更新消息类型，则未来其他开发者对类型进行自己的更新时就有可能重用字段编号。当旧版本的代码遇到新版本生成的消息时，由于字段编号的重新分配，可能会引发解析错误或不预期的行为。为了避免这种潜在的兼容性问题，protobuf 提供 `reserved` 关键字来明确标记不再使用的字段编号或标识符，如果将来的开发者尝试使用这些标识符，proto 编译器将会报错提醒。

  ```
  message Foo {
    reserved 2, 15, 9 to 11, 40 to max;
    // 9 to 11 表示区间 [9,11], 40 to max 表示区间 [40, 编号的最大值]
    reserved "foo", "bar";
  }
  ```

- **默认值**：在解析消息时，如果编码的消息中并不包含某个**不具有字段标签**的字段，那么解析后对象中的响应字段将设置为该字段的默认值。默认值的规则如下：

  - 对于 `string` ，默认值为空字符串

  - 对于 `byte` ， 默认值为空字节

  - 对于 `bool` ， 默认值为 `false`

  - 对于数字类型，默认值为 0

  - 对于 `enum` 类型，默认值为第一个定义的枚举值（编号为 0）

- 假设某个字段具有 `optional` 字段标签（或是其他什么的标签），那么在解析后的对象中将不会存在这些字段。

#### 编码原理

对于 protobuf 它的编码是很紧凑的，我们先看一下 message 的结构，举一个简单的例子：

```protobuf
message Student {
  string name = 1;
  int32 age = 2;
}
```

message 是一系列键值对，编码过之后实际上只有 tag 序列号和对应的值，这一点相比我们熟悉的 json 很不一样，所以对于 protobuf 来说没有 `.proto` 文件是无法解出来的：

![图片](https://mmbiz.qpic.cn/sz_mmbiz_png/j3gficicyOvau0QHupiamgDB8pl08lVYcVdjEu3zCO4rialhZ8pSNuGHXt1JUHQqdRukKaIBicibbk0ia3wk7IUK0hDicA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

对于 tag 来说，它保存了 message 字段的编号以及类型信息，我们可以做个实验，把 name 这个 tag 编码后的二进制打印出来：

```
func main() {
 student := student.Student{}
 student.Name = "t"
 marshal, _ := proto.Marshal(&student)
 fmt.Println(fmt.Sprintf("%08b", marshal)) // 00001010 00000001 01110100
}
```

打印出来的结果是这样：

![图片](https://mmbiz.qpic.cn/sz_mmbiz_png/j3gficicyOvau0QHupiamgDB8pl08lVYcVdkVOgtLZ5zribgibwv0K6DtF7ObH31ibXAx8YP2Il4EE52IhT73oR8ghVg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

上图中，由于 name 是 string 类型，**所以第一个 byte 是 tag，第二 byte 是 string 的长度，第三个 byte 是值，也就是我们上面设置的 “t”**。我们下面先看看 tag：

![图片](https://mmbiz.qpic.cn/sz_mmbiz_png/j3gficicyOvau0QHupiamgDB8pl08lVYcVdNL1vP1KqEThz2mNDHvta0Dv2sial2byUOMcjRwXiaHiaR4y02CMUMIeeg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

**tag 里面会包含两部分信息：字段序号，字段类型**，计算方式就是上图的公式。上图中将 name 这个字段序列化成二进制我们可以看到，第一个 bit 是标记位，表示是否字段结尾，这里是 0 表示 tag 已结尾，tag 占用 1byte；接下来 4 个 bit 表示的是字段序号，所以范围 1 到 15 中的字段编号只需要 1 bit 进行编码，我们可以做个实验看看，将 tag 改成 16：

![图片](https://mmbiz.qpic.cn/sz_mmbiz_png/j3gficicyOvau0QHupiamgDB8pl08lVYcVdInZvegdiauQ7ba7g2T81DO2wAOfaNhFP8ft6mnKkMDvA2KMDMII9pZg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

由上图所示，每个 byte 第一个 bit 表示是否结束，0 表示结束，所以上面 tag 用两个 byte 表示，并且 protobuf 是小端编码的，需要转成大端方便阅读，所以我们可以知道 tag 去掉每个 byte 第一个 bit 之后，后三位表示类型，是 3，其余位是编号表示 16。

所以从上面编码规则我们也可以知道，字段尽可能精简一些，字段尽量不要超过 16 个，这样就可以用一个 byte 表示了。

同时我们也可以知道，protobuf 序列化是不带字段名的，所以如果客户端的 proto 文件只修改了字段名，请求服务端是安全的，服务端继续用根据序列编号还是解出来原来的字段。但是需要注意的是不要修改字段类型。

接下来我们看看类型，protobuf 共定义了 6 种类型，其中两种是废弃的：

| ID   | Name   | Used For                                                 |
| :--- | :----- | :------------------------------------------------------- |
| 0    | VARINT | int32, int64, uint32, uint64, sint32, sint64, bool, enum |
| 1    | I64    | fixed64, sfixed64, double                                |
| 2    | LEN    | string, bytes, embedded messages, packed repeated fields |
| 3    | SGROUP | group start (deprecated)                                 |
| 4    | EGROUP | group end (deprecated)                                   |
| 5    | I32    | fixed32, sfixed32, float                                 |

上面的例子中，Name 是 string 类型所以上面 tag 类型解出来是 010 ，也就是 2。