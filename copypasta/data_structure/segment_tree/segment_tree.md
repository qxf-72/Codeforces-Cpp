## 基本介绍

线段树是算法竞赛中常用的用来维护 **区间信息** 的数据结构。线段树可以在 log N 的时间复杂度内实现单点修改、区间修改、区间查询（区间求和，求区间最大值，求区间最小值)等操作。



## 模板代码

以下以实现 区间求和 的线段树 为例，要实现其他区间查询操作进行需要进行少量改动即可。

|                    | 区间求和                                                     |
| ------------------ | ------------------------------------------------------------ |
| 单点修改           | [`SegTree`](https://github.com/qxf-72/Codeforces-Cpp/blob/main/copypasta/data_structure/segment_tree/SegTree.cpp) |
| 单点修改、区间加   | [`SegTree_LazyRangeAdd`](https://github.com/qxf-72/Codeforces-Cpp/blob/main/copypasta/data_structure/segment_tree/SegTree_LazyRangeAdd.cpp) |
| 单点修改、区间修改 | [`SegTree_LazyRangeSet`](https://github.com/qxf-72/Codeforces-Cpp/blob/main/copypasta/data_structure/segment_tree/SegTree_LazyRangeSet.cpp) |



## 相关题目

