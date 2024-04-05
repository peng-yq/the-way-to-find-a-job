## 文件系统

> 相对来说比较简单，因为用过go的file库

文件系统库（`std::filesystem`）在C++17中被引入，提供了一套用于操作文件系统的高级接口。它允许开发人员以跨平台的方式执行文件和目录的创建、查询和管理等操作。这个库最初是基于Boost.Filesystem库开发的，后来经过标准化过程被纳入C++标准库中。

### 8.1 文档与链接

- **C++官方文档**：[cppreference.com](https://en.cppreference.com/w/cpp/filesystem) 提供了关于`std::filesystem`库的详细文档，包括各种功能的使用方法、示例代码和接口说明。
- **Boost.Filesystem文档**：虽然`std::filesystem`已经是C++标准的一部分，但了解其来源的[Boost.Filesystem库](https://www.boost.org/doc/libs/release/libs/filesystem/)仍然非常有用，特别是对于使用旧版本C++标准的项目。

### 8.2 std::filesystem

`std::filesystem`库提供了一系列操作文件系统的功能，包括文件和目录的创建、复制、删除，文件大小查询，路径操作等。下面是一些主要组件和功能的概述：

- **路径（`std::filesystem::path`）**：表示文件系统中的路径，可以是文件或目录。`path`类提供了丰富的接口来操作和查询路径。

- **文件状态和属性**：`std::filesystem`提供了函数来查询文件的状态（如是否存在、是否为目录）和属性（如文件大小、最后修改时间）。

- **文件和目录的操作**：包括创建、复制、移动、删除文件和目录的函数。这些操作对于文件管理和维护非常重要。

- **目录遍历**：`std::filesystem`支持递归和非递归地遍历目录，让开发者可以轻松地处理目录中的所有文件。

- **文件系统错误处理**：通过`std::filesystem::filesystem_error`异常和错误代码，库提供了一套错误处理机制。

### 示例代码

下面是一个简单的示例，展示了如何使用`std::filesystem`库来查询一个文件的大小并打印出来：

```cpp
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

int main() {
    fs::path filePath = "/path/to/your/file.txt";
    if (fs::exists(filePath) && fs::is_regular_file(filePath)) {
        auto fileSize = fs::file_size(filePath);
        std::cout << "File size: " << fileSize << " bytes" << std::endl;
    } else {
        std::cout << "File does not exist or is not a regular file." << std::endl;
    }
    return 0;
}
```

这段代码首先检查指定路径的文件是否存在且为普通文件，如果是，则查询并打印其大小。

