## 基本介绍

由于`C++`没有像`Java`那样提供大数类，当需要进行超大数字的计算时，需要自己实现高精度计算，基本思想是用数组存储数字的每一个数位(可能会进行压位操作)，模拟手算的过程编写代码实现大数之间的运算。

`C++`实现大数运算比较繁琐，**当需要进行高精度运算时，建议使用`Java`和`Python`**。

<br/>
<br/>



## 模板代码

**`BigIntTiny`**([点击访问代码](https://github.com/qxf-72/Codeforces-Cpp/blob/main/copypasta/math/BigIntTiny.cpp))

- `BigIntTiny`类利用`vector<int>`存储数位，同时实现了压位，将4位压缩为1位存储。
- 具体操作方面，实现了大数之间的`<,>,==,!=,<=,>=,*,/,%`的操作。


- 在具体测试时，发现**两个BIgIntTiny对象之间的除法操作时间消耗极高**，在条件允许的情况下，尽量使用大数和普通int的除法操作。


**`BigIntSimplest`**([点击访问代码](https://github.com/qxf-72/Codeforces-Cpp/blob/main/copypasta/math/BigIntSimplest.cpp))

- 利用数组`int []` 存储数位。

- 实现了大数和int的乘法，大数和int的除法，大数和int的<操作。

- **只能进行正数的运算**  。


<br/>
<br/>



## 相关题目
[P1080 [NOIP2012 提高组] 国王游戏](https://www.luogu.com.cn/problem/P1080)
