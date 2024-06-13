## 键入网址到网页显示，期间发生了什么？

### 解析URL

<img src="https://cdn.xiaolincoding.com/gh/xiaolincoder/ImageHost/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/%E9%94%AE%E5%85%A5%E7%BD%91%E5%9D%80%E8%BF%87%E7%A8%8B/3.jpg">

如果请求的文件名省略，默认访问根目录下的默认文件，例如`index.html`。

解析`URL`后，浏览器会根据信息构造`HTTP Request`，请求行中包括请求的资源路径，消息头中包含请求的服务器名，消息头（比如`POST`）中包含具体的数据。

<img src="https://cdn.xiaolincoding.com/gh/xiaolincoder/ImageHost/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/%E9%94%AE%E5%85%A5%E7%BD%91%E5%9D%80%E8%BF%87%E7%A8%8B/4.jpg">

### DNS域名解析

将`HTTP Request`发送至目标服务器前，需要对目标服务器的域名进行域名解析。对于域名，越靠右的层级越高，例如`www.server.com`，完整的是`www.server.com.`，`.`是根域名，`com`是顶级域名。

每个`dns`服务器都保存有根域名服务器的地址，域名解析的过程是一层一层去解析的。

<img src="https://cdn.xiaolincoding.com/gh/xiaolincoder/ImageHost/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/%E9%94%AE%E5%85%A5%E7%BD%91%E5%9D%80%E8%BF%87%E7%A8%8B/6.jpg">

当然为了节约时间，会先去查`DNS`缓存（先浏览器查看存储的缓存，找不到`OS`再去查，找不到再去找`hosts`文件），不行再去找设置的`dns`服务器。

### 协议栈

<img src="https://cdn.xiaolincoding.com/gh/xiaolincoder/ImageHost/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/%E9%94%AE%E5%85%A5%E7%BD%91%E5%9D%80%E8%BF%87%E7%A8%8B/7.jpg">

完成`dns`解析后，浏览器会通过`socket`库向目标服务器监听套接字发送`connect`请求。`HTTP/HTTPS`的传输层协议是`TCP`，再通过`TCP`三次握手后，与服务器完成连接建立，并在连接套接字中完成数据的发送和读取。由`IP`协议控制网络包的收发操作，网卡驱动程序和网卡完成网络包的实际发送。

`IP`协议包括`ICMP`协议和`ARP`协议，前者用于传送网络通信产生的错误和各种控制信息；后者用于将`IP`地址转换为`MAC`地址。

### TCP

<img src="https://cdn.xiaolincoding.com/gh/xiaolincoder/ImageHost/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/%E9%94%AE%E5%85%A5%E7%BD%91%E5%9D%80%E8%BF%87%E7%A8%8B/8.jpg">

`TCP`报文中的一些重要内容：

- 源端口号和目的端口号
- 序号：确保包的发送有序
- 确认序号：确保包发送去对方有收到，没收到就继续发送，解决丢包问题
- 状态位：`SYN`建立连接，`ACK`为回复，`RST`为重新连接，`FIN`为结束连接
- 窗口大小：用于流量控制，标识当前能够处理的能力也就是缓存大小
- 拥塞控制，控制发送速度

`TCP`三次握手：

- 如果只有两次握手：客户端发送`SYN`，服务端回复`SYN+ACK`，此时服务端准备好接受和发送数据，但是客户端已经崩溃，就会造成资源浪费；另外加入客户端的`SYN`因为网络延时延迟发送到了服务端，如果只有两次握手就会建立不必要的连接
- 三次握手可以解决上述问题，并保证了双方都有收发数据的能力
- 注意握手过程中的序列号变化，ACK是SYN的序列号+1

<img src="https://cdn.xiaolincoding.com/gh/xiaolincoder/ImageHost4/%E7%BD%91%E7%BB%9C/TCP%E4%B8%89%E6%AC%A1%E6%8F%A1%E6%89%8B.drawio.png">

如果`TCP`传输的数据太大（超过了`MSS`），会将其进行划分，并加上`TCP`头；而`IP`包划分是`IP`头+`TCP`头+数据超过了`MTU`会进行划分。

<img src="https://cdn.xiaolincoding.com/gh/xiaolincoder/ImageHost/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/%E9%94%AE%E5%85%A5%E7%BD%91%E5%9D%80%E8%BF%87%E7%A8%8B/11.jpg">

`TCP`报文：

<img src="https://cdn.xiaolincoding.com/gh/xiaolincoder/ImageHost/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/%E9%94%AE%E5%85%A5%E7%BD%91%E5%9D%80%E8%BF%87%E7%A8%8B/13.jpg">

### IP

`IP`包中主要包括：

- 源`IP`地址：如果有多个网卡和`IP`地址，会根据路由表选择一个网卡作为源`IP`地址
- 目的`IP`地址：`DNS`解析出的服务器的`IP`地址
- 协议号：这里是`TCP`，为`16`进制

### MAC

`MAC`包头中包括：

- 发送方`MAC`地址，发送方`MAC`地址是网卡生产时烧录到`ROM`中，读出即可
- 源`MAC`地址是下一跳的`MAC`地址，比如下一跳是路由器，源`MAC`地址就是路由器的`MAC`地址
- 协议：`TCP/IP`通信中，`MAC`包头的协议类型只只使用`IP`协议和`ARP`协议

`MAC`地址的查找会先去找`ARP`缓存，查找不到再使用`ARP`协议进行广播。

### 网卡

封装成`IP`包后，网卡驱动程序会将内存中的`IP`包复制到其网卡内的缓冲区中，并加上报头和起始帧分界符，末尾加上校验错误的帧检测序列。再转换为电信号，发送出去。

<img src="https://cdn.xiaolincoding.com/gh/xiaolincoder/ImageHost4/%E7%BD%91%E7%BB%9C/%E6%95%B0%E6%8D%AE%E5%8C%85.drawio.png">

### 交换机

交换机是二层网络设备，工作在`MAC`层。交换机本身没有`MAC`地址，网络包到达交换机后，交换机会查`MAC`地址表将网络包转发到对应的端口。如果`MAC`地址表中没有，则会广播到除源端口外的其他端口。

### 路由器

路由器是三层网络设备，每个端口都有`MAC`地址和`IP`地址。路由器会检查网络包中的`MAC`地址是否发送给自己的，不是则丢弃。路由器根据路由表确定需要转发的端口。查询路由表的过程中，如果网关是`IP`地址，说明目标地址不在同一个子网，则需要进一步转发；如果为空，说明目标地址处于同一个子网，通过`ARP`协议得到`MAC`地址，直接发送。

### 服务器解包

<img src="https://cdn.xiaolincoding.com/gh/xiaolincoder/ImageHost/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/%E9%94%AE%E5%85%A5%E7%BD%91%E5%9D%80%E8%BF%87%E7%A8%8B/25.jpg">

一层层的去掉头部，实际是写入到连接套接字的缓冲区中，由服务器进行读取处理。

### 四次挥手

<img src="https://cdn.xiaolincoding.com//mysql/other/format,png-20230309230614791.png">