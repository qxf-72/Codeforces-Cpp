## 基本介绍

主要一些对于一个区间进行位运算的相关技巧。

<br/>

<br/>

## 按位或 按位与 的区间tick

模板来源：https://leetcode.cn/problems/smallest-subarrays-with-maximum-bitwise-or/solutions/1830911/by-endlesscheng-zai1/

该模板可以做到：

- 求出**所有**子数组的按位或的结果，以及值等于该结果的子数组的个数。
- 求按位或结果等于**任意给定数字**的子数组的最短长度/最长长度。

### [模板代码](./Interval_Add_Or.cpp)

按位或 按位与 在区间上进行连续操作得到的数字 具有单调性：按位或单调增加，按位与单调减小。所以可以倒序枚举区间的左端点，统计以其为左端点的区间 进行或运算/与运算 能够得到的值（同时还能记录该值对应的右端点），其中由于值具有单调性，可以进行去重的操作。

### 相关题目

按位或：

- [898. 子数组按位或操作](https://leetcode.cn/problems/bitwise-ors-of-subarrays/)

按位与：

- [1521. 找到最接近目标值的函数值](https://leetcode.cn/problems/find-a-value-of-a-mysterious-function-closest-to-target/)

最大公因数（GCD）：

- [Codeforces 475D. CGCDSSQ](https://leetcode.cn/link/?target=https%3A%2F%2Fcodeforces.com%2Fproblemset%2Fproblem%2F475%2FD)
- [Codeforces 1632D. New Year Concert](https://leetcode.cn/link/?target=https%3A%2F%2Fcodeforces.com%2Fproblemset%2Fproblem%2F1632%2FD)

乘法：

- [蓝桥杯2021年第十二届国赛真题-和与乘积](https://leetcode.cn/link/?target=https%3A%2F%2Fwww.dotcpp.com%2Foj%2Fproblem2622.html)