## HTTP1.1如何优化

1. 尽可能避免发送HTTP请求：利用缓存技术，使用url做为key，响应内容做为value，响应头部会有一个过期时间；etag字段包含响应的摘要，客户端二次请求时，服务端校验这个摘要，如果没变化则返回304 Not modified响应。
2. 减少重定向请求次数：由代理服务器完成重定向
3. 合并请求（HTTP1.1 pipeline技术默认不启用，造成队头阻塞），这里的合并请求还是用一个TCP连接，只是我们把资源进行合并，比如把小内容打包成大文件。
4. 延迟获取内容，只要用户不请求就不需要全部获取过来。
5. 减少HTTP响应大小
   1. gzip无损压缩，http请求头部说明压缩算法
   2. 有损压缩，http请求头部说明质量因子

### 如何避免发送HTTP请求

避免发送 HTTP 请求的方法就是通过**缓存技术**，HTTP 协议的头部有不少是针对缓存的字段。**客户端会把第一次请求以及响应的数据保存在本地磁盘上，其中将请求的 URL 作为 key，而响应作为 value，两者形成映射关系**。这样当后续发起相同的请求时，就可以先在本地磁盘上通过 key 查到对应的 value，也就是响应，如果找到了，就直接从本地读取该响应。毋庸置疑，读取本地磁盘的速度肯定比网络请求快得多，如下图：

![img](https://cdn.xiaolincoding.com/gh/xiaolincoder/ImageHost4@main/%E7%BD%91%E7%BB%9C/http1.1%E4%BC%98%E5%8C%96/%E7%BC%93%E5%AD%98%E8%AE%BF%E9%97%AE.png)

万一缓存的响应不是最新的，而客户端并不知情，那么该怎么办呢？**服务器在发送 HTTP 响应时，会估算一个过期的时间，并把这个信息放到响应头部中，这样客户端在查看响应头部的信息时，一旦发现缓存的响应是过期的，则就会重新发送网络请求**。如果客户端从第一次请求得到的响应头部中发现该响应过期了，客户端重新发送请求，假设服务器上的资源并没有变更，还是老样子，那么你觉得还要在服务器的响应带上这个资源吗？

很显然不带的话，可以提高 HTTP 协议的性能，那具体如何做到呢？**只需要客户端在重新发送请求时，在请求的 `Etag` 头部带上第一次请求的响应头部中的摘要，这个摘要是唯一标识响应的资源，当服务器收到请求后，会将本地资源的摘要与请求中的摘要做个比较**。如果不同，那么说明客户端的缓存已经没有价值，服务器在响应中带上最新的资源。如果相同，说明客户端的缓存还是可以继续使用的，那么服务器**仅返回不含有包体的 `304 Not Modified` 响应**，告诉客户端仍然有效，这样就可以减少响应资源在网络中传输的延时，如下图：

![img](https://cdn.xiaolincoding.com/gh/xiaolincoder/ImageHost4@main/%E7%BD%91%E7%BB%9C/http1.1%E4%BC%98%E5%8C%96/%E7%BC%93%E5%AD%98etag.png)

### 如何减少 HTTP 请求次数？

#### 减少重定向请求次数

**重定向请求**：服务器上的一个资源可能由于迁移、维护等原因**从 url1 移至 url2 后，而客户端不知情，它还是继续请求 url1，这时服务器不能粗暴地返回错误，而是通过 `302` 响应码和 `Location` 头部，告诉客户端该资源已经迁移至 url2 了，于是客户端需要再发送 url2 请求以获得服务器的资源**。

那么，如果重定向请求越多，那么客户端就要多次发起 HTTP 请求，每一次的 HTTP 请求都得经过网络，这无疑会越降低网络性能。另外，服务端这一方往往不只有一台服务器，比如源服务器上一级是代理服务器，然后代理服务器才与客户端通信，这时客户端重定向就会导致客户端与代理服务器之间需要 2 次消息传递，如下图：

![img](https://cdn.xiaolincoding.com/gh/xiaolincoder/ImageHost4@main/%E7%BD%91%E7%BB%9C/http1.1%E4%BC%98%E5%8C%96/%E5%AE%A2%E6%88%B7%E7%AB%AF%E9%87%8D%E5%AE%9A%E5%90%91.png)

如果**重定向的工作交由代理服务器完成，就能减少 HTTP 请求次数了**，如下图：

![img](https://cdn.xiaolincoding.com/gh/xiaolincoder/ImageHost4@main/%E7%BD%91%E7%BB%9C/http1.1%E4%BC%98%E5%8C%96/%E4%BB%A3%E7%90%86%E6%9C%8D%E5%8A%A1%E5%99%A8%E9%87%8D%E5%AE%9A%E5%90%91.png)

而且当代理服务器知晓了重定向规则后，可以进一步减少消息传递次数，如下图：

![img](https://cdn.xiaolincoding.com/gh/xiaolincoder/ImageHost4@main/%E7%BD%91%E7%BB%9C/http1.1%E4%BC%98%E5%8C%96/%E4%BB%A3%E7%90%86%E6%9C%8D%E5%8A%A1%E5%99%A8%E9%87%8D%E5%AE%9A%E5%90%912.png)

除了 `302` 重定向响应码，还有其他一些重定向的响应码，你可以从下图看到：

![img](https://cdn.xiaolincoding.com/gh/xiaolincoder/ImageHost4@main/%E7%BD%91%E7%BB%9C/http1.1%E4%BC%98%E5%8C%96/%E9%87%8D%E5%AE%9A%E5%90%91%E5%93%8D%E5%BA%94%E7%A0%81.png)

#### 合并请求

如果把多个访问小文件的请求合并成一个大的请求，虽然传输的总资源还是一样，但是减少请求，也就意味着**减少了重复发送的 HTTP 头部**。另外由于 HTTP/1.1 是请求响应模型，如果第一个发送的请求，未收到对应的响应，那么后续的请求就不会发送（PS：**HTTP/1.1 管道模式是默认不使用的，所以讨论 HTTP/1.1 的队头阻塞问题，是不考虑管道模式的**），于是为了防止单个请求的阻塞，所以**一般浏览器会同时发起 5-6 个请求，每一个请求都是不同的 TCP 连接**，那么如果合并了请求，也就会**减少 TCP 连接的数量，因而省去了 TCP 握手和慢启动过程耗费的时间**。

这种方式就是**通过将多个小图片合并成一个大图片（再根据 CSS 数据把大图片切割成多张小图片）来减少 HTTP 请求的次数，以减少 HTTP 请求的次数，从而减少网络的开销**。

除了将小图片合并成大图片的方式，还有服务端使用 `webpack` 等打包工具将 js、css 等资源合并打包成大文件，也是能达到类似的效果。

另外，还可以将图片的二进制数据用 `base64` 编码后，以 URL 的形式嵌入到 HTML 文件，跟随 HTML 文件一并发送.

可以看到，**合并请求的方式就是合并资源，以一个大资源的请求替换多个小资源的请求**。但是这样的合并请求会带来新的问题，**当大资源中的某一个小资源发生变化后，客户端必须重新下载整个完整的大资源文件**，这显然带来了额外的网络消耗。

#### 延迟发送请求

不要一口气吃成大胖子，一般 HTML 里会含有很多 HTTP 的 URL，当前不需要的资源，我们没必要也获取过来，于是可以通过「**按需获取**」的方式，来减少第一时间的 HTTP 请求次数。请求网页的时候，没必要把全部资源都获取到，而是只获取当前用户所看到的页面资源，当用户向下滑动页面的时候，再向服务器获取接下来的资源，这样就达到了延迟发送请求的效果。

### 如何减少 HTTP 响应的数据大小？

对于 HTTP 的请求和响应，通常 HTTP 的响应的数据大小会比较大。我们可以考虑对响应的资源进行**压缩**，这样就可以减少响应的数据大小，从而提高网络传输的效率。

压缩的方式一般分为 2 种，分别是：

- *无损压缩*；
- *有损压缩*；

#### 无损压缩

**gzip 就是比较常见的无损压缩。客户端支持的压缩算法，会在 HTTP 请求中通过头部中的 `Accept-Encoding` 字段告诉服务器**：

```text
Accept-Encoding: gzip, deflate, br
```

服务器收到后，会从中选择一个服务器支持的或者合适的压缩算法，然后使用此压缩算法对响应资源进行压缩，最后通过响应头部中的 `Content-Encoding` 字段告诉客户端该资源使用的压缩算法。

```text
Content-Encoding: gzip
```

gzip 的压缩效率相比 Google 推出的 Brotli 算法还是差点意思，也就是上文中的 br，所以如果可以，服务器应该选择压缩效率更高的 br 压缩算法。

#### 有损压缩

有损压缩主要将次要的数据舍弃，**牺牲一些质量来减少数据量、提高压缩比，这种方法经常用于压缩多媒体数据，比如音频、视频、图片。可以通过 HTTP 请求头部中的 `Accept` 字段里的「 q 质量因子」，告诉服务器期望的资源质量**。

```text
Accept: audio/*; q=0.2, audio/basic
```