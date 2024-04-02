## 正则表达式

一般使用正则表达式主要是实现下面三个需求：

- 检查一个串是否包含某种形式的子串；
- 将匹配的子串替换；
- 从某个串中取出符合条件的子串。

正则表达式是由普通字符（例如a到z）以及特殊字符组成的文字模式。模式描述在搜索文本时要匹配的一个或多个字符串。正则表达式作为一个模板，将某个字符模式与所搜索的字符串进行匹配。

#### 特殊字符

特殊字符是正则表达式里有特殊含义的字符，也是正则表达式的核心匹配语法。参见下表：

| 特别字符 | 描述                                                         |
| -------- | ------------------------------------------------------------ |
| `$`      | 匹配输入字符串的结尾位置。                                   |
| `(`,`)`  | 标记一个子表达式的开始和结束位置。子表达式可以获取供以后使用。 |
| `*`      | 匹配前面的子表达式零次或多次。                               |
| `+`      | 匹配前面的子表达式一次或多次。                               |
| `.`      | 匹配除换行符 `\n` 之外的任何单字符。                         |
| `[`      | 标记一个中括号表达式的开始。                                 |
| `?`      | 匹配前面的子表达式零次或一次，或指明一个非贪婪限定符。       |
| `\`      | 将下一个字符标记为或特殊字符、或原义字符、或向后引用、或八进制转义符。例如， `n` 匹配字符 `n`。`\n` 匹配换行符。序列 `\\` 匹配 `'\'` 字符，而 `\(` 则匹配 `'('` 字符。 |
| `^`      | 匹配输入字符串的开始位置，除非在方括号表达式中使用，此时它表示不接受该字符集合。 |
| `{`      | 标记限定符表达式的开始。                                     |
| `|`      | 指明两项之间的一个选择。                                     |

#### 限定符

限定符用来指定正则表达式的一个给定的组件必须要出现多少次才能满足匹配。见下表：

| 字符    | 描述                                                         |
| :------ | :----------------------------------------------------------- |
| `*`     | 匹配前面的子表达式零次或多次。例如，`foo*` 能匹配 `fo` 以及 `foooo`。`*` 等价于`{0,}`。 |
| `+`     | 匹配前面的子表达式一次或多次。例如，`foo+` 能匹配 `foo` 以及 `foooo`，但不能匹配 `fo`。`+` 等价于 `{1,}`。 |
| `?`     | 匹配前面的子表达式零次或一次。例如，`Your(s)?` 可以匹配 `Your` 或 `Yours` 中的`Your` 。`?` 等价于 `{0,1}`。 |
| `{n}`   | `n` 是一个非负整数。匹配确定的 `n` 次。例如，`o{2}` 不能匹配 `for` 中的 `o`，但是能匹配 `foo` 中的两个 `o`。 |
| `{n,}`  | `n` 是一个非负整数。至少匹配 `n` 次。例如，`o{2,}` 不能匹配 `for` 中的 `o`，但能匹配 `foooooo` 中的所有 `o`。`o{1,}` 等价于 `o+`。`o{0,}` 则等价于 `o*`。 |
| `{n,m}` | `m` 和 `n` 均为非负整数，其中 `n` 小于等于 `m`。最少匹配 `n` 次且最多匹配 `m` 次。例如，`o{1,3}` 将匹配 `foooooo` 中的前三个 `o`。`o{0,1}` 等价于 `o?`。注意，在逗号和两个数之间不能有空格。 |

### std::regex及其相关

C++作为一门高性能语言，**在后台服务的开发中，对URL资源链接进行判断时， 使用正则表达式也是工业界最为成熟的普遍做法**。一般的解决方案就是使用boost的正则表达式库。 而C++11正式将正则表达式的的处理方法纳入标准库的行列，从语言级上提供了标准的支持， 不再依赖第三方。**C++11提供的正则表达式库操作std::string对象， 模式std::regex (本质是 std::basic_regex) 进行初始化，通过std::regex_match进行匹配， 从而产生std::smatch（本质是std::match_results对象）**。

例如：[a-z]+\\.txt: 在这个正则表达式中, [a-z] 表示匹配一个小写字母, + 可以使前面的表达式匹配多次， 因此 [a-z]+ 能够匹配一个小写字母组成的字符串。 在正则表达式中一个 . 表示匹配任意字符，而 \\. 则表示匹配字符 .， 最后的 txt 表示严格匹配 txt 则三个字母。因此这个正则表达式的所要匹配的内容就是由纯小写字母组成的文本文件。

std::regex_match用于匹配字符串和正则表达式，有很多不同的重载形式。 最简单的一个形式就是传入std::string以及一个std::regex进行匹配， 当匹配成功时，会返回true，否则返回false。

另一种常用的形式就是依次传入 std::string/std::smatch/std::regex 三个参数， 其中 std::smatch 的本质其实是 std::match_results。 故而在标准库的实现中， std::smatch 被定义为了 std::match_results<std::string::const_iterator>， 也就是一个子串迭代器类型的 match_results。 使用 std::smatch 可以方便的对匹配的结果进行获取。

```c++
#include <iostream>
#include <string>
#include <regex>

int main() {
    std::string fnames[] = {"foo.txt", "bar.txt", "test", "a0.txt", "AAA.txt"};
    // 在 C++ 中 \ 会被作为字符串内的转义符，
    // 为使 \. 作为正则表达式传递进去生效，需要对 \ 进行二次转义，从而有 \\.
    std::regex txt_regex("[a-z]+\\.txt");
    for (const auto &fname: fnames)
        std::cout << fname << ": " << std::regex_match(fname, txt_regex) << std::endl;
}

std::regex base_regex("([a-z]+)\\.txt");
std::smatch base_match;
for(const auto &fname: fnames) {
    if (std::regex_match(fname, base_match, base_regex)) {
        // std::smatch 的第一个元素匹配整个字符串
        // std::smatch 的第二个元素匹配了第一个括号表达式
        if (base_match.size() == 2) {
            std::string base = base_match[1].str();
            std::cout << "sub-match[0]: " << base_match[0].str() << std::endl;
            std::cout << fname << " sub-match[1]: " << base << std::endl;
        }
    }
}
```