# 并查集

## 基本介绍

并查集(Disjoint Set Union)是一种用于管理元素所属集合的数据结构，实现为一个森林，其中每棵树表示一个集合，树中的节点表示对应集合中的元素。并查集至少支持两种操作：

- 合并（Union）：合并两个元素所属集合（合并对应的树）。
- 查询（Find）：查询某个元素所属集合（查询对应的树的根节点），这可以用于判断两个元素是否属于同一集合。


<br/>


<br/>



## 模板代码

[**DSU.cpp**](/copypasta/Advanced_Data_Structure/DSU.cpp) 支持以下操作：
- **查询所在集合**：同时进行路径压缩
- **合并**：利用树的高度进行启发式合并
- **查询节点所在集合的大小**

[**DSU_2D.cpp**](/copypasta/Advanced_Data_Structure/DSU_2D.cpp) 实现了二维的并查集，但是仅支持 $n\times n$ 的方阵。对于一个二维或者多维的数组，更好的方法是将其扁平化之后，利用一维并查集进行处理。

<br/>


<br/>


## 相关题目

[2709. 最大公约数遍历](https://leetcode.cn/problems/greatest-common-divisor-traversal/)


---

<br/>


<br/>


<br/>


<br/>

# 树状数组

## 基本介绍

树状数组是一种支持 **单点修改** 和 **区间查询** 的，代码量小的数据结构。普通树状数组维护的信息及运算要满足 **结合律** 且 **可差分**，如，加法（和）、乘法（积）、异或等。

- 结合律： $\left( x\cdot y \right) \cdot z=x\cdot \left( y\cdot z \right)$ ，其中 $\cdot$ 是二元运算符。
- 可差分：已知 $\left ( x\cdot y \right)$  和  $x$ ，能够把 $y$ 求出来。 

树状数组能解决的问题是线段树能解决的问题的子集：树状数组能做的，线段树一定能做；线段树能做的，树状数组不一定可以。然而，树状数组的代码要远比线段树短，时间效率常数也更小，因此仍有学习价值。

<br/>

<br/>


## 模板代码

[**BIT.cpp**](/copypast/Advanced_Data_Structure/BIT.cpp) 以维护区间和为例，支持以下操作：

- **求 1 到 i 的区间和**：时间复杂度为 $log_2^n$ 。在此基础上进行修改可以实现求任意区间和，需要注意，树状数组的下标是从 1 开始的。
- **单点修改**：即修改当个点值。时间复杂度为 $log_2^n$ 。


[**BIT_Diff.cpp**](/copypasta/Advanced_Data_Structure/BIT_Diff.cpp) 以维护区间和为例，利用差分，实现了区间修改
- **区间和**：时间复杂度为 $log_2^n$ 。
- **区间加**：区间每一个数都加上同一个数。时间复杂度为 $log_2^n$ 。

<br/>

<br/>


## 参考资料

《挑战程序设计竞赛》P174-P183：简单易懂，适合入门

[OIWiki树状数组介绍](https://oi-wiki.org/ds/fenwick/)

[manim | 算法 | 数据结构](https://www.bilibili.com/video/BV1pE41197Qj/?spm_id_from=333.337.search-card.all.click&vd_source=a7d5a38480a5acb21de3325d1ec0cf14) ：差分树状数组原理讲得很好


<br/>

<br/>


## 相关例题

[2659. 将数组清空](https://leetcode.cn/problems/make-array-empty/)

---



<br/>


<br/>


<br/>


<br/>

# 线段数

## 基本介绍

线段树是算法竞赛中常用的用来维护 **区间信息** 的数据结构。线段树可以在 log N 的时间复杂度内实现单点修改、区间修改、区间查询等操作。

线段树能够维护的信息要能够满足 **结合律** 以及 **支持快速合并**，例如 GCD、区间求和，求区间最大值，求区间最小值等。


<br/>

<br/>


## 模板代码

  

以下以实现 **区间求和** 的线段树 为例，要实现其他区间查询操作进行需要进行少量改动即可。

  

#### **`SegTree`(**[点击访问代码](https://github.com/qxf-72/Codeforces-Cpp/blob/main/copypasta/Data_Structure/Segment_Tree/SegTree.cpp))：

  

- 单点修改

  

#### **`SegTree_LazyRangeAdd`**([点击访问代码](https://github.com/qxf-72/Codeforces-Cpp/blob/main/copypasta/Data_Structure/Segment_Tree/SegTree_LazyRangeAdd.cpp))：

  

- 单点修改

- 区间懒惰更新（区间所有数都加一个数）

  

#### **`SegTree_LazyRangeSet`**([点击访问代码](https://github.com/qxf-72/Codeforces-Cpp/blob/main/copypasta/Data_Structure/Segment_Tree/SegTree_LazyRangeSet.cpp))：

  

- 单点修改

- 区间懒惰更新（区间所有数修改为给定数值）



<br/>


<br/>

  
## 参考资料


[OIWiki的SegmentTree介绍](https://oi-wiki.org/ds/seg/)

  

<br/>

<br/>

  
  

## 相关题目

#### 区间(绝对)众数及其出现次数(摩尔投票法)

- [1157. 子数组中占绝大多数的元素](https://leetcode.cn/problems/online-majority-element-in-subarray/)

#### 最长连续相同子串问题

- [2213. 由单个字符重复的最长子字符串](https://leetcode.cn/problems/longest-substring-of-one-repeating-character/)

#### 关于区间01反转的懒惰更新问题

- [2569. 更新数组后处理求和查询](https://leetcode.cn/problems/handling-sum-queries-after-update/)

---