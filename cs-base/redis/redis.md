#### Redis和Memcache的区别

1. redis支持丰富的数据结构（基础数据结构：string、hash、list、set和zset；高级数据结构：位图、位域、消息队列、地理索引、超级日志）
2. memcache只支持key-value的存储
3. redis应用场景更丰富，数据库、消息队列、缓存等；memcache应用场景更局限，用于缓存
4. redis原生支持集群，memcache没有原生的集群模式

#### redis单线程处理请求

redis采用IO多路复用机制来处理请求，采用reactor IO模型， 处理流程如下:

1. 首先接收到客户端的socket请求，多路复用器将socket转给连接应答处理器；
2. 连接应答处理器将AE_READABLE事件与命令请求处理器关联(这里是把socket事件放入一个队列)；
3. 命令请求处理器从socket中读到指令，再内存中执行，并将AE_WRITEABLE事件与命令回复处理器关联；
4. 命令回复处理器将结果返回给socket，并解除关联。

<img src="https://mmbiz.qpic.cn/mmbiz_jpg/j3gficicyOvavHkNR2OB5uHbdDnsEIah8ic3ricm9JbmY3LicuRvmCw4LDiag3Bxm7ts9YNX2iavQSsaajlfoqgiaia4sicg/640?wx_fmt=jpeg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1">

#### redis 单线程效率高的原因

1. I/O多路复用
2. 纯内存操作效率高
3. 单线程避免了多线程的切换和互斥同步开销

#### redis key过期策略

对于设置了过期时间的key，redis的删除策略：定期删除+惰性删除。

1. 定期删除：redis默认每100ms随机抽取了一些设置了过期时间的key，如果过期就进行删除。如果redis设置了10万个key都设置了过期时间，每隔几百毫秒就要检查10 万个key那CPU 负载就很高了，所以redis并不会每隔100ms就检查所有的key，而是随机抽取一些key来检查。
2. 惰性删除：定期删除会导致有些 key 过期了并没有被删除，因此在获取某个 key 的时候发现过期了，如果 key 过期了就删除掉不会返回。

这两个策略结合起来保证过期的 key 一定会被删除。

#### redis内存淘汰

redis内存占用过大，就会进行内存淘汰：

1. 新写入操作直接报错
2. LRU（最常用）
3. 随机移除几个key
4. 在设置了过期时间的key中，LRU
5. 在设置了过期时间的key中，随机移除几个

#### redis主从模式保证高并发和高可用

**读写分离**：读写分离保证高并发(10W+ QPS)：对于缓存来说一般都是支撑高并发读，写请求都是比较少的。采用读写分离的架构(一主多从)，master 负责接收写请求，数据同步到 slave 上提供读服务，如果遇到瓶颈只需要增加 slave 机器就可以水平扩容。

**主从复制**：

1. redis异步复制到slave节点
2. slave节点做复制时不会阻塞，而是使用旧的数据集提供服务。复制完成后，删除旧的数据集，加载新的数据集（加载过程中会暂停服务）
3. 开启主从复制，master必须开启**持久化（rdb和aof）**，否则master宕机重启后数据是空的，slave一同步就把数据抹除了

**同步流程**：

1. slave启动给master发送psync命令
2. 如果是重新连接，matser会复制给slave缺少的那部分数据
3. 如果是第一次连接master，会触发全量复制，master生成一份rdb快照，期间客户端的命令都缓存在内存中。rdb生成完成后，发送给slave，**slave先写入磁盘再加载到内存**，然后master将缓存的命令发送给slave。

<img src="https://mmbiz.qpic.cn/mmbiz_jpg/j3gficicyOvavHkNR2OB5uHbdDnsEIah8icfFbuRC4qsfeICSrw6KeIficfS4h5YjNiarRak1g3SSv2zCgbwicE87osQ/640?wx_fmt=jpeg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1">

#### Redis哨兵模式

哨兵功能：

1. 集群监控：监控master和slave是否正常工作
2. 消息通知：如果某个redis实例有问题，哨兵将发消息通知管理员
3. 故障转移：如果master实例发生故障，会选举出新的master
4. 配置中心：如果故障转移完成，会通知客户端新的master地址

哨兵的注意事项：

1. 哨兵至少三个，保证自己的高可用；
2. 哨兵+主从的部署架构是用来保证 redis 集群高可用的，并非保证数据不丢失；
3. 哨兵(Sentinel)需要通过不断的测试和观察才能保证高可用。
4. 哨兵检测master宕机分为主观宕机和客观宕机：
   1. 主观：一个哨兵觉得 master 宕机了，达成条件是如果一个哨兵 ping master 超过了 is-master-down-after-milliseconds 指定的毫秒数后就认为主观宕机；
   2. 客观：一个哨兵在指定时间内收到了 majority(大多数) 数量的哨兵也认为那个 master 宕机了，就是客观宕机。
5. 哨兵之间的互相发现：哨兵是通过 redis 的 pub/sub 实现的。

为什么2个哨兵不能执行：因为要满足大多数哨兵存活，2的大多数是2，此时master宕机，其节点上的哨兵也宕机，就不能满足大多数，从而无法实现故障转移。

三哨兵集群：

<img src="https://mmbiz.qpic.cn/mmbiz_jpg/j3gficicyOvavHkNR2OB5uHbdDnsEIah8icb0W7IucPZX6b0MGzySgc7fu8NL2marXhGAfOfrp3OoGTcq3Q1WmdZg/640?wx_fmt=jpeg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1">

#### Redis持久化——RDB

RDB（Redis DataBase）是将某一个时刻的内存快照（Snapshot），以二进制的方式写入磁盘的过程。RDB 有两种方式 save 和 bgsave:

- save: 执行就会触发 Redis 的持久化，但同时也是使 Redis 处于阻塞状态，直到 RDB 持久化完成，才会响应其他客户端发来的命令；
- bgsave: bgsave 会 fork() 一个子进程来执行持久化，整个过程中只有在 fork() 子进程时有短暂的阻塞，当子进程被创建之后，Redis 的主进程就可以响应其他客户端的请求了。

除了使用 save 和 bgsave 命令触发之外， RDB 支持自动触发。自动触发策略可配置 Redis 在指定的时间内，数据发生了多少次变化时，会自动执行 bgsave 命令。在 redis 配置文件中配置:

```shell	
在时间 m 秒内，如果 Redis 数据至少发生了 n 次变化，那么就自动执行BGSAVE命令。
save m n
```

RDB 的优点:

- RDB 会定时生成多个数据文件，**每个数据文件都代表了某个时刻的 redis 全量数据，适合做冷备**，可以将这个文件上传到一个远程的安全存储中，以预定好的策略来定期备份 redis 中的数据；
- RDB 对 redis **对外提供读写服务的影响非常小，redis 是通过 fork 主进程**的一个子进程操作磁盘 IO 来进行持久化的；
- **相对于 AOF，直接基于 RDB 来恢复 reids 数据更快**。

RDB 的缺点:

- 如果使用 RDB 来恢复数据，**会丢失一部分数据，因为 RDB 是定时生成的快照文件**；
- RDB 每次来 **fork 出子进程的时候，如果数据文件特别大，可能会影响对外提供服务**，暂停数秒(主进程需要拷贝自己的内存表给子进程， 实例很大的时候这个拷贝过程会很长)。latest_fork_usec 代表 fork 导致的延时；Redis 上执行 INFO 命令查看 latest_fork_usec；**当 RDB 比较大的时候， 应该在 slave 节点执行备份， 并在低峰期执行**。

#### Redis持久化——AOF

redis 对每条写入命令进行日志记录，以 append-only 的方式写入一个日志文件（文本），redis 重启的时候通过重放日志文件来恢复数据集。(**由于运行久了 AOF 文件会越来越大，redis 提供一种 rewrite 机制，基于当前内存中的数据集，来构建一个更小的 AOF 文件，将旧的庞大的 AOF 文件删除)。rewrite 即把日志文件压缩， 通过 bgrewriteaof 触发重写**。AOF rewrite 后台执行的方式和 RDB 有类似的地方，fork 一个子进程，主进程仍进行服务，子进程执行 AOF 持久化，数据被 dump 到磁盘上。**与 RDB 不同的是，后台子进程持久化过程中，主进程会记录期间的所有数据变更（主进程还在服务），并存储在 server.aof_rewrite_buf_blocks 中；后台子进程结束后，Redis 更新缓存追加到 AOF 文件中，是 RDB 持久化所不具备的**。

AOF 的工作流程如下:

1. Redis 执行写命令后，把这个命令写入到 AOF 文件内存中（write 系统调用）；
2. Redis 根据配置的 AOF 刷盘策略，把 AOF 内存数据刷到磁盘上（fsync 系统调用）；
3. 根据 rewrite 相关的配置触发 rewrite 流程。

appendfsync: 刷盘的机制：

- always：**主线程每次执行写操作后立即刷盘，此方案会占用比较大的磁盘 IO 资源，但数据安全性最高**；
- everysec：**主线程每次写操作只写内存就返回，然后由后台线程每隔 1 秒执行一次刷盘操作（触发 fsync 系统调用），此方案对性能影响相对较小，但当 Redis 宕机时会丢失 1 秒的数据（常用）**；
- no：**主线程每次写操作只写内存就返回，内存数据什么时候刷到磁盘，交由操作系统决定，此方案对性能影响最小，但数据安全性也最低，Redis 宕机时丢失的数据取决于操作系统刷盘时机**。

AOF还有rewrite策略：

1. 相较于上一版aof文件大小百分比达到多少时重写
2. 最小容忍aof文件大小

AOF 的优点:

- 可以更好的保证数据不丢失，一般 AOF 每隔 1s 通过一个后台线程来执行 fsync(强制刷新磁盘页缓存)，**最多丢失 1s 的数据**；
- AOF 以 append-only 的方式写入(顺序追加)，没有磁盘寻址开销，性能很高；
- AOF 即使文件很大， 触发后台 rewrite 的操作的时候一般也不会影响客户端的读写，(rewrite 的时候会对其中指令进行压缩，创建出一份恢复需要的最小日志出来)。
- 通过文本记录，适合做灾难性的误操作的紧急恢复，比如不小心使用 flushall 清空了所有数据，只要 rewrite 没有发生，就可以立即拷贝 AOF，将最后一条 flushall 命令删除，再回放 AOF 恢复数据。

AOF 的缺点：

- 同一份数据，因为 AOF 记录的命令会比 RDB 快照文件更大；
- AOF 开启后，支持写的 QPS 会比 RDB 支持写的 QPS 要低，毕竟 AOF 有写磁盘的操作。

#### 结合使用AOF和RDB

两者综合使用，将 AOF 配置成每秒 fsync 一次。RDB 作为冷备，**AOF 用来保证数据不丢失的恢复第一选择，当 AOF 文件损坏或不可用的时候还可以使用 RDB 来快速恢复**。

数据恢复过程

1. **启动Redis服务**：当Redis启动时，它会检查配置文件中的持久化设置。
2. **检测AOF文件**：
   - 如果`appendonly`配置设置为`yes`，Redis会首先查找AOF文件。
   - 如果AOF文件存在且有效，Redis将使用AOF文件来恢复数据。这是因为AOF文件通常包含自最后一次RDB快照以来的所有写操作，能够重构出最完整的数据状态。
3. **AOF文件缺失或损坏时使用RDB**：
   - 如果AOF文件不存在或损坏，Redis将回退到使用RDB文件。
   - Redis将加载RDB文件中的数据快照，这通常代表了在某个时间点的完整数据状态。
4. **处理AOF中的新增记录**：
   - 如果在RDB文件被加载后，还存在有效的AOF文件，Redis将处理AOF文件中自最后一次RDB快照之后记录的所有命令。
   - 这意味着Redis首先通过RDB文件快速恢复到一个较早的状态，然后通过执行AOF文件中记录的命令来更新这些数据，从而达到最新状态。
5. **数据完整性验证**：
   - 一旦数据通过RDB和AOF文件恢复完成，建议进行数据的完整性验证，确保所有数据都已正确加载且无损坏。

#### Redis集群

redis主从复制、读写分离实现了一定程度的高并发、并保证高可用，但有如下限制：

1. master 数据和 slave 数据一模一样，master 的数据量就是集群的限制瓶颈；
2. redis 集群的写能力也受到了 master 节点的单机限制。

Redis Cluster 支持 N 个 master node ，每个 master node 可以挂载多个 slave node：

1. 自动将数据切片，每个 master 上放一部分数据；
2. 提供内置的高可用支持，部分 master 不可用时还是能够工作；
3. redis cluster 模式下，每个 redis 要开放两个端口：6379 和 10000+以后的端口(如 16379)。16379 是用来节点之间通信的，使用的是 cluster bus 集群总线。cluster bus 用来做故障检测，配置更新，故障转移授权。

redis集群负载均衡：redis cluster 采用 一致性 hash+虚拟节点 来负载均衡。redis cluster 有固定的 16384 个 slot (2^14)，对每个 key 做 CRC16 值计算，然后对 16384 mod。可以获取每个 key 的 slot。redis cluster 每个 master 都会持有部分 slot，比如 三个 master 那么 每个 master 就会持有 5000 多个 slot。hash slot 让 node 的添加和删除变得很简单，增加一个 master，就将其他 master 的 slot 移动部分过去，减少一个就分给其他 master，这样让集群扩容的成本变得很低。

redis集群通信：与集中式不同(如使用 zookeeper 进行分布式协调注册)，redis cluster 使用的是 gossip 协议进行通信。并不是将集群元数据存储在某个节点上，而是不断的互相通信，保持整个集群的元数据是完整的。gossip 协议所有节点都持有一份元数据，不同节点的元数据发生了变更，就不断的将元数据发送给其他节点，让其他节点也进行元数据的变更。

#### redis cluster 主备切换与高可用

1. 判断节点宕机：如果有一个节点认为另外一个节点宕机，那就是主观宕机。如果多个节点认为一个节点宕机，那就是客观宕机。跟哨兵的原理一样；

2. 对宕机的 master，**从其所有的 slave 中选取一个切换成 master node，再此之前会进行一次过滤，检查每个 slave 与 master 的断开时间，如果超过了 cluster-node-timeout * cluster-slave-validity-factor 就没有资格切换成 master**；

3. 从节点选取：**每个从节点都会根据从 master 复制数据的 offset，来设置一个选举时间，offset 越大的从节点，选举时间越靠前，master node 开始给 slave 选举投票，如果大部分 master(n/2+1)都投给了某个 slave，那么选举通过(与 zk 有点像，选举时间类似于 epochid)**；

4. 整个流程与哨兵类似，可以说 redis cluster 集成了哨兵的功能，更加的强大；

5. Redis 集群部署相关问题 redis 机器的配置，多少台机器，能达到多少 qps?

   - 机器标准:8 核+32G
   - 集群: 5 主+5 从(每个 master 都挂一个 slave)
   - 效果: 每台机器最高峰每秒大概 5W，5 台机器最多就是 25W，每个 master 都有一个从节点，任何一个节点挂了都有备份可切换成主节点进行故障转移

#### 脑裂问题哨兵模式下

   - **master 下 挂载了 3 个 slave，如果 master 由于网络抖动被哨兵认为宕机了，执行了故障转移，从 slave 里面选取了一个作为新的 master，这个时候老的 master 又恢复了，刚好又有 client 连的还是老的 master，就会产生脑裂，数据也会不一致，比如 incr 全局 id 也会重复**。

##### 1. 解决脑裂问题的配置策略

在Redis中，`min-slaves-to-write` 和 `min-slaves-max-lag` 这两个配置参数可以帮助防止脑裂问题，尤其是在主从复制的环境中。这两个参数的作用如下：

- **`min-slaves-to-write`**: 这个参数设置了一个阈值，**指定了必须有至少多少个从节点与主节点保持在连接状态，主节点才接受写操作**。例如，如果设置为1，那么至少需要有一个从节点连接到主节点，主节点才会接受写请求。
- **`min-slaves-max-lag`**: 这个参数用来**设置从节点与主节点之间的最大允许复制延迟时间（以秒为单位）。如果从节点复制主节点的数据延迟超过了这个时间，即使从节点的数量满足`min-slaves-to-write`的要求，主节点也会拒绝写操作**。

这两个参数联合使用时，可以防止在主节点数据未能及时同步到从节点的情况下发生数据写入，从而减少因脑裂导致的数据不一致问题。

##### 2. 客户端连接到Redis的TCP连接考量

Redis虽然是单线程处理命令请求，但它使用IO多路复用技术来同时处理多个网络连接。关于使用单个TCP连接还是多个TCP连接的性能考量，以下是一些关键点：

- **多个TCP连接**：使用多个TCP连接可以在一个IO周期内处理更多的就绪IO事件，这通常会提高处理效率，因为Redis可以并行地从多个连接读取数据并响应。
- **单个TCP连接与Pipeline**：如果使用单个TCP连接，并配合pipeline技术（即一次发送多个命令并批量接收响应），这种方式可以减少TCP连接的建立和关闭的开销，同时减少网络延迟。然而，如果单次pipeline的请求过多，也可能会导致在单个IO周期内处理的命令数量过多，从而影响性能。
- **连接数的选择**：在Redis Cluster环境中，通常建议控制每个节点的连接数在100个以内。这是因为过多的连接可能会增加Redis服务器的负担，尤其是在处理大量小请求时。