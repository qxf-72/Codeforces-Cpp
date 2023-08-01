## 基本介绍

单调栈即满足单调性的栈结构。

单调栈适合用于寻找序列中**下一个更大或更小的元素**。单调栈就是在遍历序列的同时，根据当前遍历的点元素的大小选择是否将目前栈顶元素弹出，有两种选择策略：

- 当前元素的值大于栈顶元素的值就将栈顶元素弹出：**当前遍历到的元素对于被弹出的元素，就是下一个更大元素**。
- 当前元素的值小于栈顶元素的值就将栈顶元素弹出：**当前遍历到的元素对于被弹出的元素，就是下一个更小元素。**

可以一直弹出直到不满足条件或者栈为空，然后将当前元素入栈。当遍历完序列之后，栈中的元素必然是单调的，其栈中元素在原序列中不存在下一个更小或更小的元素（**具有下一个更大或更小元素 的元素已经在上述遍历过程被弹出栈**）。

<br/><br/>

## 求下一个更大(小)元素

### [模板代码](./Monotonic_Stack.cpp)

模板的代码以下一个更小的元素为例，可以求出该元素之后和该元素之前第一个更小元素的下标。此时可以得到**以该元素为最小值的最大区间边界**。通常与贡献法结合。

模板代码以求下一个更小元素为例，但是如果将数组中的元素取反，此时求的就是下一个更大元素。

### 相关题目

- [907. 子数组的最小值之和](https://leetcode.cn/problems/sum-of-subarray-minimums/)
- [1856. 子数组最小乘积的最大值](https://leetcode.cn/problems/maximum-subarray-min-product/)
- [2104. 子数组范围和](https://leetcode.cn/problems/sum-of-subarray-ranges/)
- [2281. 巫师的总力量和](https://leetcode.cn/problems/sum-of-total-strength-of-wizards/)

<br/><br/>

## 求最长区间

从基本介绍中可以看到，单调栈可以求下一个符合要求的元素，即**最近或者是距离最短**的元素。

单调栈还可以求，序列中满足要求的最长的区间的长度，参考 [Leetcode 1124题 的题解](https://leetcode.cn/problems/longest-well-performing-interval/solutions/2110211/liang-chong-zuo-fa-liang-zhang-tu-miao-d-hysl/) 。

### [模板代码](./Find_Longest_Interval.cpp)

### 相关题目

- [1124. 表现良好的最长时间段](https://leetcode.cn/problems/longest-well-performing-interval/)
