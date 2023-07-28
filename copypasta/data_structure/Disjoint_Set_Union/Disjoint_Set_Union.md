## 基本介绍

并查集(Disjoint Set Union)是一种用于管理元素所属集合的数据结构，实现为一个森林，其中每棵树表示一个集合，树中的节点表示对应集合中的元素。

顾名思义，并查集支持两种操作：

- 合并（Union）：合并两个元素所属集合（合并对应的树）。
- 查询（Find）：查询某个元素所属集合（查询对应的树的根节点），这可以用于判断两个元素是否属于同一集合。

<br/>
<br/>

## 模板代码

#### `DSU`([点击访问代码](https://github.com/qxf-72/Codeforces-Cpp/blob/main/copypasta/data_structure/Disjoint_Set_Union/DSU.cpp))

- 查找（路径压缩）
- 合并（启发式合并）

<br/>
<br/>

## 相关题目

[2709. 最大公约数遍历](https://leetcode.cn/problems/greatest-common-divisor-traversal/)

