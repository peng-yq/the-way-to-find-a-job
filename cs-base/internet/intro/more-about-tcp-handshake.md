#### socket 编程核心代码

**server**

```c++
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    const char* hello = "Hello from server";

    // 创建 socket 文件描述符
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // 绑定 socket 到端口 8080
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // 监听这个端口
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // 接受连接
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    // 读取数据
    read(new_socket, buffer, 1024);
    std::cout << "Message from client: " << buffer << std::endl;

    // 发送数据
    send(new_socket, hello, strlen(hello), 0);
    std::cout << "Hello message sent\n";

    // 关闭 socket
    close(new_socket);
    close(server_fd);

    return 0;
}
```

**client**

```c++
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    const char* hello = "Hello from client";

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cout << "Socket creation error" << std::endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    // 将 IPv4 地址从文本转换为二进制形式
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cout << "Invalid address/ Address not supported" << std::endl;
        return -1;
    }

    // 连接到服务器
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cout << "Connection Failed" << std::endl;
        return -1;
    }

    // 发送数据
    send(sock, hello, strlen(hello), 0);
    std::cout << "Hello message sent\n";

    // 接收数据
    int valread = read(sock, buffer, 1024);
    std::cout << "Message from server: " << buffer << std::endl;

    // 关闭 socket
    close(sock);

    return 0;
}
```

#### TCP中的全连接队列和半连接队列

##### 半连接队列（SYN队列）

**半连接队列，也称为 SYN 队列，用于存储已经接收到 SYN 包但还没有完成三次握手的连接请求**。当一个客户端向服务器发送一个 SYN 包（第一次握手，请求建立连接）时，服务器回应一个 SYN-ACK 包（第二次握手，确认客户端的请求并附带自己的连接请求），然后这个连接就会被放入半连接队列中。此时连接还未完全建立，服务器正在等待客户端发送 ACK 包（第三次握手，确认服务器的连接请求）。

##### 全连接队列

**全连接队列用于存储已经完成三次握手的连接请求**。当服务器收到客户端的 ACK 包后，三次握手完成，连接从半连接队列移动到全连接队列。在全连接队列中的连接是已经完全建立的，服务器可以开始接收和发送数据。

如果半连接队列太小，那么在高流量条件下，新的连接请求可能会因为队列已满而被丢弃。类似地，全连接队列的大小也需要根据预期的并发连接数来合理配置。

在安全方面，**半连接队列可能会成为 SYN 洪水攻击的目标，攻击者通过发送大量的 SYN 包来尝试耗尽服务器的半连接队列资源，导致正常用户无法建立连接**。因此，操作系统和网络设备通常提供了一些机制（如 SYN cookies）来防护此类攻击，确保即使在攻击下也能有效管理连接请求。

#### 服务器为什么需要先listen

listen 最主要的工作就是**申请和初始化接收队列（计算长度，申请内存），包括全连接队列和半连接队列。其中全连接队列是一个链表，而半连接队列由于需要快速的查找，所以使用的是一个哈希表（其实半连接队列更准确的的叫法应该叫半连接哈希表）**。

<img src="https://mmbiz.qpic.cn/mmbiz_png/BBjAFF4hcwqA9nnEqmlc1uSHaJ0icrDjga11byftYALich517R4XbaZ6XVbrXPC5grLwoErFBSd4FbzJsgmQq1kA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1">

全/半两个队列是三次握手中很重要的两个数据结构，有了它们服务器才能正常响应来自客户端的三次握手。所以服务器端都需要 listen 一下才行。

除此之外我们还有额外收获，我们还知道了内核是如何确定全/半连接队列的长度的。

**1.全连接队列的长度**
对于全连接队列来说，其最大长度是 listen 时传入的 **backlog （传入的参数）和 net.core.somaxconn （系统级内核参数）之间较小的那个值。如果需要加大全连接队列长度，那么就是调整 backlog 和 somaxconn**。

**2.半连接队列的长度**
在 listen 的过程中，内核我们也看到了对于半连接队列来说，**其最大长度是 min(backlog, somaxconn, tcp_max_syn_backlog) + 1 再上取整到 2 的幂次，但最小不能小于16。如果需要加大半连接队列长度，那么需要一并考虑 backlog，somaxconn 和 tcp_max_syn_backlog 这三个参数**。网上任何告诉你修改某一个参数就能提高半连接队列长度的文章都是错的。

#### 客户端connect

**客户端在 connect 的时候，把本地 socket 状态设置成了 TCP_SYN_SENT，选了一个可用的端口，接着发出 SYN 握手请求并启动重传定时器，该定时器的作用是等到一定时间后收不到服务器的反馈的时候来开启重传。在 3.10 版本中首次超时时间是 1 s，一些老版本中是 3 s**。

客户端建立连接前需要确定一个端口，该端口会在两个位置进行确定。

第一个位置，也是最主要的确定时机是 connect 系统调用执行过程。**在 connect 的时候，会随机地从 ip_local_port_range 选择一个位置开始循环判断。找到可用端口后，发出 syn 握手包**。如果端口查找失败，会报错 “Cannot assign requested address”。这个时候你应该首先想到去检查一下服务器上的 net.ipv4.ip_local_port_range 参数，是不是可以再放的多一些。

**如果你因为某种原因不希望某些端口被使用到，那么就把它们写到 ip_local_reserved_ports 这个内核参数中就行了，内核在选择的时候会跳过这些端口**。

**另外注意即使是一个端口是可以被用于多条 TCP 连接的（四元组）。所以一台客户端机最大能建立的连接数并不是 65535。只要 server 足够多，单机发出百万条连接没有任何问题**。

<img src="https://mmbiz.qpic.cn/mmbiz_png/BBjAFF4hcwpTVmte5LxzIu4eJn2zuWvGE0f5unP3spic4aHQl4VMgpUfY13HClucicghJ4ks8K4I3F2rsY3teibgg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1">

截图中左边的 192 是客户端，右边的 119 是服务器的 ip。可以看到客户端的 10000 这个端口号是用在了多条连接上了的。

第二个位置，**如果在 connect 之前使用了 bind，将会使得 connect 时的端口选择方式无效。转而使用 bind 时确定的端口。bind 时如果传入了端口号，会尝试首先使用该端口号，如果传入了 0 ，也会自动选择一个。但默认情况下一个端口只会被使用一次。所以对于客户端角色的 socket，不建议使用 bind** ！

最后我再想多说一句，上面的选择端口的都是从 ip_local_port_range 范围中的某一个随机位置开始循环的。如果可用端口很充足，则能快一点找到可用端口，那循环很快就能退出。**假设实际中 ip_local_port_range 中的端口快被用光了，这时候内核就大概率得把循环多执行很多轮才能找到，这会导致 connect 系统调用的 CPU 开销的上涨。所以，最好不要等到端口不够用了才加大 ip_local_port_range 的范围，而是事先就应该保持一个充足的范围**。

#### 服务器响应SYN

**服务器响应 ack 是主要工作是判断下半连接队列是否满了，满的话可能会丢弃该请求，否则发出 synack。申请 request_sock 添加到半连接队列中，同时启动定时器（通常是重传定时器），确保如果客户端没有响应，服务器会在一定时间后重发 SYN-ACK。这也帮助服务器管理半连接队列中的条目，防止资源长时间被半开放连接占用**。

#### 客户端响应SYN ACK

**客户端响应来自服务器端的 synack 时清除了 connect 时设置的重传定时器（也就是SYN发送时设置的），把当前 socket 状态设置为 ESTABLISHED，开启保活计时器（如果配置了 TCP keepalive 选项，这个计时器用于定期发送保活包，以确保连接在长时间无数据交换时仍然保持活跃，并检测任何潜在的连接断开或故障）后发出第三次握手的 ack 确认。**

#### 服务器响应ACK

**服务器响应第三次握手 ack 所做的工作是把当前半连接对象删除，创建了新的 sock et后加入到全连接队列中，最后将新连接状态设置为 ESTABLISHED**。

#### 服务器accept

**accept 的重点工作就是从已经建立好的全连接队列中取出一个返回给用户进程。**

#### 总结

<img src="https://mmbiz.qpic.cn/mmbiz_png/BBjAFF4hcwooE10RtLDCLnrlFpxvicW0Uehl4yUU3o99cdjAn2s1UKSY2mmbNC2s9lrFKfcITiaR7hZRhpS7dSOg/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp">

- 服务器 listen 时，计算了全/半连接队列的长度，还申请了相关内存并初始化。
- 客户端 connect 时，把本地 socket 状态设置成了 TCP_SYN_SENT，选则一个可用的端口，发出 SYN 握手请求并启动重传定时器。
- 服务器响应 ack 时，会判断下接收队列是否满了，满的话可能会丢弃该请求。否则发出 synack，申请 request_sock 添加到半连接队列中，同时启动定时器。
- 客户端响应 synack 时，清除了 connect 时设置的重传定时器，把当前 socket 状态设置为 ESTABLISHED，开启保活计时器后发出第三次握手的 ack 确认。
- 服务器响应 ack 时，把对应半连接对象删除，创建了新的 sock 后加入到全连接队列中，最后将新连接状态设置为 ESTABLISHED。
- accept 从已经建立好的全连接队列中取出一个返回给用户进程。

另外要注意的是，如果握手过程中发生丢包（网络问题，或者是连接队列溢出），内核会等待定时器到期后重试，重试时间间隔在 3.10 版本里分别是 1s 2s 4s ...。在一些老版本里，比如 2.6 里，第一次重试时间是 3 秒。最大重试次数分别由 tcp_syn_retries 和 tcp_synack_retries 控制。

如果你的线上接口正常都是几十毫秒内返回，但偶尔出现了 1 s、或者 3 s 等这种偶发的响应耗时变长的问题，那么你就要去定位一下看看是不是出现了握手包的超时重传了。