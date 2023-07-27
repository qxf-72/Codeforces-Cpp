## 基本介绍

线段树是算法竞赛中常用的用来维护 **区间信息** 的数据结构。线段树可以在 log N 的时间复杂度内实现单点修改、区间修改、区间查询等操作。

线段树能够维护的信息要能够满足 结合律 以及支持快速合并，例如`gcd`、区间求和，求区间最大值，求区间最小值等。

<br/>
<br/>

## 模板代码

以下以实现 **区间求和** 的线段树 为例，要实现其他区间查询操作进行需要进行少量改动即可。

#### **`SegTree`(**[点击访问代码](https://github.com/qxf-72/Codeforces-Cpp/blob/main/copypasta/data_structure/segment_tree/SegTree.cpp))：

- 单点修改

#### **`SegTree_LazyRangeAdd`**([点击访问代码](https://github.com/qxf-72/Codeforces-Cpp/blob/main/copypasta/data_structure/segment_tree/SegTree_LazyRangeAdd.cpp))：

- 单点修改
- 区间懒惰更新（区间所有数都加一个数）

#### **`SegTree_LazyRangeSet`**([点击访问代码](https://github.com/qxf-72/Codeforces-Cpp/blob/main/copypasta/data_structure/segment_tree/SegTree_LazyRangeSet.cpp))：

- 单点修改
- 区间懒惰更新（区间所有数修改为给定数值）

<br/>
<br/>


## 参考资料

[OIWiki的SegmentTree介绍](https://oi-wiki.org/ds/seg/)


<br/>
<br/>


## 相关题目

###### 区间(绝对)众数及其出现次数(摩尔投票法)

- [1157. 子数组中占绝大多数的元素](https://leetcode.cn/problems/online-majority-element-in-subarray/)

###### 最长连续相同子串问题

- [2213. 由单个字符重复的最长子字符串](https://leetcode.cn/problems/longest-substring-of-one-repeating-character/)

###### 关于区间01反转的懒惰更新问题

- [2569. 更新数组后处理求和查询](https://leetcode.cn/problems/handling-sum-queries-after-update/)    



