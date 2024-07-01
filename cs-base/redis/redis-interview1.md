#### Redis数据结构及其底层数据结构详解

##### 简单动态字符串

简单动态字符串是redis基础数据结构string的底层实现，相较于C语言传统的字符串char *（不能包含空字符），不以'\0'来标识字符串的结束，可以存储任何二进制数据，包括空字符。

```c
struct sdshdr {
    // 记录buf数组中已使用字节的数量，等于sds所保存字符串的长度
    int len;
    
    // 记录buf数组中未使用字节的数量
    int free;
    
    // 字节数组，用于保存字符串
    char buf[];
}
```

优点：

1. 获取字符串长度的时间复杂度为O(1)
2. 避免缓冲区溢出
3. 二进制安全，传统的 C 字符串依赖于空字符 '\0' 来标记字符串的结束，这限制了字符串中不能包含空字符。与之相对，SDS 由于存储了字符串的实际长度，因此可以安全地包含任何二进制数据，包括空字符
4. 字符串扩展时预分配内存，减少内存分配的次数
5. C字符串函数兼容

##### 双向链表

双向链表是Redis基础数据结构列表list的底层实现，当列表元素较多或元素长度较长时，列表使用双向链表做为其底层实现。

```c
// 节点
typedef struct listNode {
    // 前置节点
    struct listNode *prev;
    // 后置节点
    struct listNode *next;
    // 节点的值
    void *value;
} listNode;

// list
typedef struct list {
    // 表头节点
    listNode *head;
    // 表尾节点
    listNode *tail;
    // 链表所包含的节点数量
    unsigned long len;
    // 节点值复制函数
    void *(*dup)(void *ptr);
    // 节点值释放函数
    void (*free)(void *ptr);
    // 节点值对比函数
    int（*match）(void *ptr, void *key);
} list;
```

1. list的表头节点和表尾节点都指向null，为无环链表
2. 通过函数指针，链表可以对不同类型的值进行操作

##### QuickList

在 Redis3.2 之前，List 底层采用了 ZipList 和 LinkedList 实现的，在 3.2 之后，List 底层采用了 QuickList。Redis3.2 之前，初始化的 List 使用的 ZipList，List 满足以下两个条件时则一直使用 ZipList 作为底层实现，当以下两个条件任一一个不满足时，则会被转换成 LinkedList。

- **List 中存储的每个元素的长度小于 64byte**
- **元素个数小于 512**

<img src="https://static001.geekbang.org/infoq/d1/d1ebb253e429665da1d360a541f07e3e.png">

Redis 集合采用了 QuickList 作为 List 的底层实现，QuickList 其实就是结合了 ZipList 和 LinkedList 的优点设计出来的。各部分作用说明：

- **每个 listNode 存储一个指向 ZipList 的指针，ZipList 用来真正存储元素的数据。**
- **ZipList 中存储的元素数据总大小超过 8kb（默认大小，通过 list-max-ziplist-size 参数可以进行配置）的时候，就会重新创建出来一个 ListNode 和 ZipList，然后将其通过指针关联起来。**

##### 哈希表

哈希表是Redis基础数据结构列表hash的底层实现，当哈希结构的大小或字段值长度超过一定阈值时，使用哈希表做为其底层实现。

1. redis的哈希表使用链地址法来解决哈希冲突，每个哈希表节点都有个next指针，多个哈希表节点可以用这个单向链表连接起来

##### 压缩链表

当列表、哈希、有序集合的长度较小并且元素长度较小时，使用压缩链表做为其底层实现。

<img src="https://static001.geekbang.org/infoq/7b/7b26ac2a2177f040ba9ea84e00896293.png">

ZipList 是由一块连续的存储空间组成，从图中可以看出 ZipList 没有前后指针。各部分作用说明：

- **zlbytes：表示当前 list 的存储元素的总长度。**
- **zllen：表示当前 list 存储的元素的个数。**
- **zltail：表示当前 list 的头结点的地址，通过 zltail 就是可以实现 list 的遍历。**
- **zlend：表示当前 list 的结束标识。**
- **entry：表示存储实际数据的节点，每个 entry 代表一个元素。**
  - **previours_entry_length: 表示当前节点元素的长度，通过其长度可以计算出下一个元素的位置。**
  - **encoding：表示元素的编码格式。**
  - **content：表示实际存储的元素内容。**

ZipList的优缺点：

- **优点：内存地址连续，省去了每个元素的头尾节点指针占用的内存。**
- **缺点：对于删除和插入操作比较可能会触发连锁更新反应，比如在 list 中间插入删除一个元素时，在插入或删除位置后面的元素可能都需要发生相应的移动操作。**

##### Set 的实现原理

Set 集合采用了整数集合和字典两种方式来实现的，当满足如下两个条件的时候，采用整数集合实现；一旦有一个条件不满足时则采用字典来实现。

- **Set 集合中的所有元素都为整数**
- **Set 集合中的元素个数不大于 512（默认 512，可以通过修改 set-max-intset-entries 配置调整集合大小）**



![img](https://static001.geekbang.org/infoq/6f/6ff4040d02b1225a282f6e656853c985.png)

整数集合实现原理图



![img](https://static001.geekbang.org/infoq/e2/e208f44d26f53822fada26a5c8e1730a.png)

字典实现原理图

##### Zset 的实现原理

Zset 底层同样采用了两种方式来实现，分别是 ZipList 和 SkipList。当同时满足以下两个条件时，采用 ZipList 实现；反之采用 SkipList 实现。

- **Zset 中保存的元素个数小于 128。（通过修改 zset-max-ziplist-entries 配置来修改）**
- **Zset 中保存的所有元素长度小于 64byte。（通过修改 zset-max-ziplist-values 配置来修改）**

##### 采用 ZipList 的实现原理



![img](https://static001.geekbang.org/infoq/cf/cf0e93bc2e78ba0a3fdf42c9ee5f6c96.png)



和 List 的底层实现有些相似，对于 Zset 不同的是，其存储是以键值对的方式依次排列，键存储的是实际 value，值存储的是 value 对应的分值。

##### 采用 SkipList 的实现原理



![img](https://static001.geekbang.org/infoq/ad/adb7ebdd1e51c2a8822b0cae281e1b50.png)



SkipList 分为两部分，dict 部分是由字典实现，Zset 部分使用跳跃表实现，从图中可以看出，dict 和跳跃表都存储的数据，实际上 dict 和跳跃表最终使用指针都指向了同一份数据，即数据是被两部分共享的，为了方便表达将同一份数据展示在两个地方。