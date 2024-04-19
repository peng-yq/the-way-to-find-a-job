## kernel和操作系统

kernel时操作系统中最核心的部分，提供了软件应用和硬件之间交互的接口，kernel的主要功能包括：

- 进程管理
- 内存管理
- 文件系统
- 设备管理
- 系统调用和安全

操作系统除了内核外，还包括支持系统运行的其他基本软件，比如：

- CLI/GUI
- 系统工具（文本编辑器，文件资源管理器）
- 服务（网络等）
- 标准库和API（提供给应用开发者）
- 应用软件

<img src="https://cdn.xiaolincoding.com/gh/xiaolincoder/ImageHost4@main/%E6%93%8D%E4%BD%9C%E7%B3%BB%E7%BB%9F/%E5%86%85%E6%A0%B8/systemcall.png">

<img src="https://cdn.xiaolincoding.com/gh/xiaolincoder/ImageHost4@main/%E6%93%8D%E4%BD%9C%E7%B3%BB%E7%BB%9F/%E5%86%85%E6%A0%B8/OS-structure2.png">

1. 宏内核，包含多个模块，整个内核像一个完整的程序；
2. 微内核，有一个最小版本的内核，一些模块和服务则由用户态管理；
3. 混合内核，是宏内核和微内核的结合体，内核中抽象出了微内核的概念，也就是内核中会有一个小型的内核，其他模块就在这个基础上搭建，整个内核是个完整的程序；

Linux的内核设计是采用了宏内核，Window的内核设计则是采用了混合内核。这两个操作系统的可执行文件格式也不一样， Linux可执行文件格式叫作ELF，Windows可执行文件格式叫作PE。