## 基本介绍

树状数组是一种支持 **单点修改** 和 **区间查询** 的，代码量小的数据结构。普通树状数组维护的信息及运算要满足 **结合律** 且 **可差分**，如加法（和）、乘法（积）、异或等。

- 结合律：$\left( x\cdot y \right) \cdot z=x\cdot \left( y\cdot z \right)$ ，其中 $\cdot$ 是二元运算符。
- 可差分：已知 $\left( x\cdot y \right) $ 和 $x$ ，能够把 $y$ 求出来。 



树状数组能解决的问题是线段树能解决的问题的子集：树状数组能做的，线段树一定能做；线段树能做的，树状数组不一定可以。然而，树状数组的代码要远比线段树短，时间效率常数也更小，因此仍有学习价值。


<br/>
<br/>


## 模板代码

##### **`BIT`**([点击访问模板代码](https://github.com/qxf-72/Codeforces-Cpp/blob/main/copypasta/data_structure/binary_index_tree/BIT.cpp))：

- 求区间和
- 单点修改

##### **`BIT_Diff`**([点击访问模板代码](https://github.com/qxf-72/Codeforces-Cpp/blob/main/copypasta/data_structure/binary_index_tree/BIT_Diff.cpp))：差分

- 求区间和
- 区间加（区间每一个数都加上同一个数）

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
