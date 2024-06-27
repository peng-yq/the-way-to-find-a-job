## 为什么使用主从复制、读写分离

主从复制、读写分离一般是一起使用的，为了提高数据库的并发性能。比如我们使用一台mysql作为master负责写操作，另外两台slave负责读操作。如果是单机部署的mysql，随着并发量的增多，I/O频率过高，会导致性能下降。

## 主从复制的原理

### SQL语句的分类

1. **DDL（Data Definition Languages）语句：**数据定义语言，这些语句定义了不同的数据段、数据库、表、列、索引等数据库对象的定义。常用的语句关键字主要包括 create、drop、alter等。
2. **DML（Data Manipulation Language）语句：**数据操纵语句，用于添加、删除、更新和查询数据库记录，并检查数据完整性，常用的语句关键字主要包括 insert、delete、udpate 和select 等。
3. **DCL（Data Control Language）语句：**数据控制语句，用于控制不同数据段直接的许可和访问级别的语句。这些语句定义了数据库、表、字段、用户的访问权限和安全级别。主要的语句关键字包括 grant、revoke 等。

### Bin Log、Relay Log、Redo Log和Undo Log

**Bin Log**：二进制日志，记录了所有修改数据库数据的语句（INSERT、UPDATE、DELETE）等，以及DDL语句，Bin Log是顺序写入的，可以配置自动过期删除旧的日志文件。

**Relay Log**：中继日志，是从服务器（slave）上的一个关键组件，它在主从复制过程中起到了桥梁的作用。中继日志主要用于记录从主服务器接收到的所有二进制日志（binlog）事件，然后从服务器的SQL线程会读取这些记录，应用到本地数据库中以保持与主服务器的数据一致性。

**Redo Log**：重做日志，InnoDB的Redo Log用于发生故障时确保事务的持久性，通过先写redo log，然后异步写入数据到磁盘，InnoDB可以提高写入性能。redo log是固定大小的，通常配置为一组文件，循环写入。

**Undo Log**：撤销日志，InnoDB的撤销日志用于存储在事务执行过程中如何撤销已执行的操作，这是事务原子性的关键。如果事务失败或被回滚，撤销日志可以用来撤销进行中的修改。撤销日志不是预设固定大小，会根据需要动态增长，并在事务完成后进行清理。

### 原理

1. master节点进行写操作时，会按顺序写入binlog中
2. slave节点连接master节点，有多少个slave，master就会创建多少个binlog dump（转存、导出、保存）线程
3. master节点上的binlog发生变化时，binlog dump线程会通知所有的slave节点，并将对应的binlog内容推送给slave节点
4. I/O线程收到binlog内容后，将内容写入到本地的relay log
5. sql线程读取relay log，并根据内容对数据库进行操作

<img src="https://segmentfault.com/img/remote/1460000023775516">

## 读写分离

如何实现master写入数据，slave读取数据呢，可以通过AOP方式，根据方法名去判断连接master还是slave。尽管主从复制、读写分离能很大程度保证MySQL服务的高可用和提高整体性能，但是问题也不少：

- **从机是通过binlog日志从master同步数据的，如果在网络延迟的情况，从机就会出现数据延迟。那么就有可能出现master写入数据后，slave读取数据不一定能马上读出来**。

这个问题可以让同一线程且同一数据库连接，如果有写入操作，读操作均从主库读取，保证数据一致性。