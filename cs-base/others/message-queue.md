### 消息队列的常用场景

<img src="https://mmbiz.qpic.cn/mmbiz_jpg/j3gficicyOvasViao5BlOC2ia2wcPT1vCHU8LHu9uDaeDK3SNd8xaeWV6q5OJHkFvBOwa8siagnKuxXNTpZiaRIhSV0Q/640?wx_fmt=jpeg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1">

解耦：多个服务监听、处理同一条消息，避免多次 rpc 调用。

<img src="https://mmbiz.qpic.cn/mmbiz_jpg/j3gficicyOvasViao5BlOC2ia2wcPT1vCHU8ezruVRtRwslcJANUNvFAwf6ImeiaNBhvyiamdDdKqalGQCuvG7icWK0Dw/640?wx_fmt=jpeg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1">

异步消息：消息发布者不用等待消息处理的的结果。

<img src="https://mmbiz.qpic.cn/mmbiz_jpg/j3gficicyOvasViao5BlOC2ia2wcPT1vCHU8JaVCoHibSyd6T0UmNy6GK5yf88thiaMF9uzsBCWVIia32ibumbjv841BRQ/640?wx_fmt=jpeg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1">

削峰填谷：较大流量、写入场景，为下游 I/O 服务抗流量。当然大流量下就需要使用其他方案了。

<img src="https://mmbiz.qpic.cn/mmbiz_jpg/j3gficicyOvasViao5BlOC2ia2wcPT1vCHU8UcPvrSgqQguM7IFibHHSnY1RRApgKILPP4ThHzwOaTXKo2ic3toMSnqg/640?wx_fmt=jpeg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1">

消息驱动框架：在事件总线中，服务通过监听事件消息驱动服务完成相应动作。

### 消息队列模式

#### 点对点模式，不可重复消费

多个生产者可以向同一个消息队列发送消息，一个消息在被一个消息者消费成功后，这条消息会被移除，其他消费者无法处理该消息。如果消费者处理一个消息失败了，那么这条消息会重新被消费。

![图片](https://mmbiz.qpic.cn/mmbiz_jpg/j3gficicyOvasViao5BlOC2ia2wcPT1vCHU8BS5SDO8HSOgSGWmFv6LaxGHLiazryfgyh8eKj1TDNE7gOUhkQWgqPoQ/640?wx_fmt=jpeg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

#### 发布/订阅模式

发布订阅模式需要进行注册、订阅，根据注册消费对应的消息。多个生产者可以将消息写到同一个 Topic 中，多种消息可以被同一个消费者消费。一个生产者生产的消息，同样也可以被多个消费者消费，只要他们进行过消息订阅。

![图片](https://mmbiz.qpic.cn/mmbiz_jpg/j3gficicyOvasViao5BlOC2ia2wcPT1vCHU8L9ibCAOwnicBu3CBzoMq0nAwmTJtib415HP1Ze1ib9aItHFgDUuOG1GibQw/640?wx_fmt=jpeg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

### **选型参考**

- 消息顺序：**发送到队列的消息，消费时是否可以保证消费的顺序**；
- 伸缩：当消息队列性能有问题，**比如消费太慢，是否可以快速支持扩容；当消费队列过多，浪费系统资源，是否可以支持缩容**。
- 消息留存：**消息消费成功后，是否还会继续保留在消息队列**；
- 容错性：**当一条消息消费失败后，是否有一些机制，保证这条消息一定能成功，比如异步第三方退款消息，需要保证这条消息消费掉，才能确定给用户退款成功，所以必须保证这条消息消费成功的准确性**；
- 消息可靠性：**是否会存在丢消息的情况**，比如有 A/B 两个消息，最后只有 B 消息能消费，A 消息丢失；
- 消息时序：主要包括“消息存活时间”和“延迟消息”；
- 吞吐量：支持的最高并发数；
- 消息路由：**根据路由规则，只订阅匹配路由规则的消息，比如有 A/B 两者规则的消息，消费者可以只订阅 A 消息，B 消息不会消费**。

#### Kafka

Kafka 是由 Apache 软件基金会开发的一个开源流处理平台，由 Scala 和 Java 编写。该项目的目标是为处理实时数据提供一个统一、高吞吐、低延迟的平台。其持久化层本质上是一个“按照分布式事务日志架构的大规模**发布/订阅消息队列**”，这使它作为企业级基础设施来处理流式数据非常有价值。

##### **基本术语**

1. **Producer**：消息生产者。一般情况下，**一条消息会被发送到特定的主题上。通常情况下，写入的消息会通过轮询将消息写入各分区。生产者也可以通过设定消息 key 值将消息写入指定分区。写入分区的数据越均匀 Kafka 的性能才能更好发挥**。
2. **Topic**：Topic 是个抽象的虚拟概念，**一个集群可以有多个 Topic，作为一类消息的标识。一个生产者将消息发送到 topic，消费者通过订阅 Topic 获取分区消息**。
3. **Partition**：Partition 是个物理概念，**一个 Topic 对应一个或多个 Partition。新消息会以追加的方式写入分区里，在同一个 Partition 里消息是有序的。Kafka 通过分区，实现消息的冗余和伸缩性，以及支持物理上的并发读、写，大大提高了吞吐量**。
4. **Replicas**：**一个 Partition 有多个 Replicas 副本。这些副本保存在 broker，每个 broker 存储着成百上千个不同主题和分区的副本，存储的内容分为两种：master 副本，每个 Partition 都有一个 master 副本，所有内容的写入和消费都会经过 master 副本；follower 副本不处理任何客户端的请求，只同步 master 的内容进行复制。如果 master 发生了异常，很快会有一个 follower 成为新的 master**。
5. **Consumer**：消息读取者。**消费者订阅主题，并按照一定顺序读取消息。Kafka 保证每个分区只能被一个消费者使用**。
6. **Offset**：偏移量是一种元数据，是不断递增的整数。在消息写入时 Kafka 会把它添加到消息里。**在分区内偏移量是唯一的。消费过程中，会将最后读取的偏移量存储在 Kafka 中，消费者关闭偏移量不会丢失，重启会继续从上次位置开始消费**。
7. **Broker**：独立的 Kafka 服务器。一个 Topic 有 N 个 Partition，一个集群有 N 个 Broker，那么每个 Broker 都会存储一个这个 Topic 的 Partition。如果某 topic 有 N 个 partition，集群有(N+M)个 broker，那么其中有 N 个 broker 存储该 topic 的一个 partition，剩下的 M 个 broker 不存储该 topic 的 partition 数据。如果某 topic 有 N 个 partition，集群中 broker 数目少于 N 个，那么一个 broker 存储该 topic 的一个或多个 partition。在实际生产环境中，尽量避免这种情况的发生，这种情况容易导致 Kafka 集群数据不均衡。

##### **系统框架**

![图片](https://mmbiz.qpic.cn/mmbiz_jpg/j3gficicyOvasViao5BlOC2ia2wcPT1vCHU8OycSG8GEhZGVgGRhOmlv6BVdFVzgicuc7iavgxjgSTL2xKlu5EW2YeBQ/640?wx_fmt=jpeg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

##### 工作流程

1. 第一个 topic 有两个生产者，新消息被写入到 partition 1 或者 partition 3，两个分区在 broker1、broker2 都有备份。
2. 有新消息写入后，两个 follower 分区会从两个 master 分区同步变更。
3. 对应的 consumer 会从两个 master 分区根据现在 offset 获取消息，并更新 offset。
4. 第二个 topic 只有一个生产者，同样对应两个 partition，分散在 Kafka 集群的两个 broker 上。
5. 有新消息写入，两个 follower 分区会同步 master 变更。
6. 两个 Consumer 分别从不同的 master 分区获取消息。

##### **优点**

1. **高吞吐量、低延迟**：kafka 每秒可以处理几十万条消息，它的延迟最低只有几毫秒；
2. **可扩展性**：kafka 集群支持热扩展；
3. **持久性、可靠性**：消息被持久化到本地磁盘，并且支持数据备份防止数据丢失；
4. **容错性**：允许集群中节点故障，一个数据多个副本，少数机器宕机，不会丢失数据；
5. **高并发**：支持数千个客户端同时读写。

##### **缺点**

1. **分区有序**：仅在同一分区内保证有序，无法实现全局有序；
2. **无延时消息**：消费顺序是按照写入时的顺序，不支持延时消息
3. **重复消费**：消费系统宕机、重启导致 offset 未提交；
4. **Rebalance**：Rebalance 的过程中 consumer group 下的所有消费者实例都会停止工作，等待 Rebalance 过程完成。

注意**kafka本身不支持延迟消息，消费顺序按照写入时的顺序，从偏移量位置开始消费**。

**6.如果要让 Kafka 支持延迟消息你会怎么做？你有几种方案？各有什么优缺点？**

Apache Kafka 本身并不直接支持延迟消息队列的功能，但我们可以通过一些策略来实现类似的效果。以下是一些可能的方案：

1. 使用定时任务

**在生产者端，将消息和预定的发送时间一同存储在数据库或其他存储系统中。然后，使用定时任务（比如 Quartz 或者 Spring Scheduler）定期扫描数据库，将达到预定发送时间的消息发送到 Kafka**。

优点：实现简单，不需要修改 Kafka 或消费者的代码。

缺点：可能会产生大量的数据库操作，对数据库性能有一定影响。并且，**消息的发送时间可能不够精确**，比如如果定时任务每分钟运行一次，那么消息的发送延迟可能会达到一分钟。

1. 在消费者端实现延迟

**在消费者端，首先立即消费消息，然后检查消息的预定处理时间。如果预定处理时间还未到，那么将消息存储起来，并在预定处理时间到达时再处理消息**。

优点：不需要修改 Kafka 或生产者的代码。

缺点：**增加了消费者的复杂性**。并且，如果消费者重启，那么可能会丢失那些还未处理的消息。

##### **使用场景**

1. **日志收集**：大量的日志消息先写入 kafka，数据服务通过消费 kafka 消息将数据落地；
2. **消息系统**：解耦生产者和消费者、缓存消息等；
3. **用户活动跟踪**：kafka 经常被用来记录 web 用户或者 app 用户的各种活动，如浏览网页、搜索、点击等活动，这些活动信息被各个服务器发布到 kafka 的 topic 中，然后消费者通过订阅这些 topic 来做实时的监控分析，亦可保存到数据库；
4. **运营指标**：记录运营、监控数据，包括收集各种分布式应用的数据，生产各种操作的集中反馈，比如报警和报告；
5. **流式处理**：比如 spark streaming。

### 其它的消息队列中间件

#### RabbitMQ

##### **优点**

- 基于 AMQP 协议：除了 Qpid，RabbitMQ 是唯一一个实现了 AMQP 标准的消息服务器；
- 健壮、稳定、易用；
- 社区活跃，文档完善；
- 支持定时消息；
- 可插入的身份验证，授权，支持 TLS 和 LDAP；
- 支持根据消息标识查询消息，也支持根据消息内容查询消息。

##### **缺点**

- erlang 开发源码难懂，不利于做二次开发和维护；
- 接口和协议复杂，学习和维护成本较高。

##### **总结**

- erlang 有并发优势，性能较好。虽然源码复杂，但是社区活跃度高，可以解决开发中遇到的问题；
- 业务流量不大的话可以选择功能比较完备的 RabbitMQ。

#### Pulsar

##### **优点**

- 灵活扩容
- 无缝故障恢复
- 支持延时消息
- 内置的复制功能，用于跨地域复制如灾备
- 支持两种消费模型：流（独享模式）、队列（共享模式）

#### RocketMQ

##### **优点**

支持发布/订阅（Pub/Sub）和点对点（P2P）消息模型：

- 顺序队列：在一个队列中可靠的先进先出（FIFO）和严格的顺序传递；支持拉（pull）和推（push）两种消息模式；
- 单一队列百万消息的堆积能力；
- 支持多种消息协议，如 JMS、MQTT 等；
- 分布式横向扩展架构；
- 满足至少一次消息传递语义；
- 提供丰富的 Dashboard，包含配置、指标和监控等；
- 支持的客户端，目前是 java、c++及 golang

##### **缺点**

- 社区活跃度一般；
- 延时消息：开源版不支持任意时间精度，仅支持特定的 level。

##### **使用场景**

- 为金融互联网领域而生，对于可靠性要求很高的场景。
