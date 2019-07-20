# Essay-CXX-Strcrypt

C++ string constant (const char*) code protection using template/constexpr compile-time computation and basic caesar cipher

## Question & Answer

### 它是什么东西？

辣鸡可怜愚蠢的 duangsuse 花了足足一天的时间也要强行写完的 C++ 『代码字符串保护』实现。

### 有用的代码

+ `*.pro` 是 QMake 的工程文件，里面指定了语言版本和头文件、实现代码什么的
+ `literal_str.hpp` 是静态字符串拼接的帮助程序
+ `mess.h` 是混淆的头文件
+ `main.cpp` 是测试


### 什么是 `constexpr`

是 C++ 的编译期计算实现，它可以把编译期能够确定的东西拿来计算，产生的东西运行期编译期都可以用，比如可以 `static_assert`

```c++
constexpr int fib(int n) {
  if (n == 0 || n == 1) return n;
  return fib(n - 1) + fib(n - 2);
}

static_assert(fib(0) == 0);
static_assert(fib(1) == 1);
static_assert(fib(2) == 1);
static_assert(fib(3) == 2);

#include <iostream>
using namespace std;
int main() {
  for (unsigned i = 0; i < 100; ++i)
    cout << fib(i) << endl;
  return 0; 
}

```

### 这个东西有什么用？

当我们使用 C++ 编程并且编译源代码到 object 文件的时候，会发现 object 里依然有很多（可能是常量段 `.rodata` 的）字符串是果存的

这些字符串灰肠容易被某些图谋不轨♂的幼稚园黑客 hack。
即便我不理解程序分析，连模式匹配都没有用过，
像我如此擅长逆向工程的人，对 Kotlin Intrinsics 对象方法暴露了一些命名什么的都能够轻易发现，所以我饶不了这些 raw string literal

于是我设计出了一种高智商的手段，可以在编译期把字符串加密，然后再在运行期解密，并且为自己的奇思妙想而自豪，就是用 Base64 预先编码，然后让搜索字符串的辣鸡人吃 no matching found。（逃跑，我没有！

问题是我发现很多字符串都需要保护，我不能手动把他们给编码了，那样会让我的代码根本没法看，怎么办呢？

于是我想到了这种方法，利用 C++ 的 constructor implicit conversation, `constexpr`, value `template` 做一个这样的辅助头文件。

刚开始是打算顺便练习一下 C++ 的 template 和 constexpr 特性，想到了这么一种方法也是多亏某 Android 开发的大佬的点子。

加密方式非常简单，就是 naive 的凯撒密码（每个字符加一个偏移 _k_），也没有循环块加密和加盐什么的...

> 以上是我玩一个个人的梗啦... 不要弄个大新闻说我要谦虚一点又把我给批判一番

## 向大佬致谢

作者在完成这个项目的时候，得到了（世界互联）网上一些大佬发表文章的帮助（注意，都不是 StackOverflow 上的）

在此特别予以感谢：

+ [C++11 Compile-time String Concatenation with constexpr | DaniWeb](https://www.daniweb.com/programming/software-development/code/482276/c-11-compile-time-string-concatenation-with-constexpr)
+ [USTC 隆晋威（Spring 2018）： C++17 实现类型安全的 printf ](https://lug.ustc.edu.cn/wiki/lug/events/weeklyparty)

## 许可证相关

~~因为许可证是具有“污染性”的 Apache，而且这是『靠代码内部保护代码』，所以，想真正实锤代码保护的话，失望喽。~~

此项目为实验性质，而且保护目前来看好像是无效的，代码使用 Apache 2.0 发布，想使用的话直接用就可以了，不需要开源使用项目代码的作品。


