<h1 align="center">程序设计竞赛模板库</h1>

<p align="center">面向 C++17 的算法竞赛笔记与可复用代码模板。</p>

<p align="center">
  <img src="https://img.shields.io/badge/C%2B%2B-17-blue.svg" alt="C++17">
  <a href="LICENSE"><img src="https://img.shields.io/github/license/qxf-72/Codeforces-Cpp" alt="MIT License"></a>
  <a href="https://github.com/qxf-72/Codeforces-Cpp/stargazers"><img src="https://img.shields.io/github/stars/qxf-72/Codeforces-Cpp" alt="GitHub stars"></a>
</p>

本仓库参考 [灵茶山艾府💭💡🎈的算法竞赛 Go 语言模板库](https://github.com/EndlessCheng/codeforces-go)，持续整理学习中的算法知识、竞赛技巧和 C++ 模板代码。

## 使用方式

- 从下方目录进入对应的知识笔记，了解算法思路、复杂度和适用场景。
- 可直接在 [`copypasta/`](copypasta) 中查找经过整理的独立 C++ 模板；使用前请结合题目约束验证复杂度、下标范围和数据类型。
- 本仓库使用 C++17；本地可使用 `g++ -std=c++17 -O2 -Wall source.cpp` 编译测试。

## 快速导航

- 数据结构：[并查集](copypasta/Advanced_Data_Structure/DSU.cpp) · [树状数组](copypasta/Advanced_Data_Structure/BIT.cpp) · [线段树](copypasta/Advanced_Data_Structure/SegTree.cpp) · [懒标记线段树](copypasta/Advanced_Data_Structure/SegTree_lazytag.cpp)
- 图论：[Dijkstra](copypasta/Graph_Theory/Dijkstra.cpp) · [Floyd](copypasta/Graph_Theory/Floyd.cpp) · [Kruskal](copypasta/Graph_Theory/Kruskal.cpp) · [Prim](copypasta/Graph_Theory/Prim.cpp)
- 字符串：[Trie](copypasta/String/Trie.cpp) · [字符串 Hash](copypasta/String/StringHash.cpp) · [Manacher](copypasta/String/Manacher.cpp)
- 基础工具：[Sparse Table](copypasta/Basic_Algorithm/SparseTable.cpp) · [高精度](copypasta/Basic_Algorithm/BigInt.cpp)

## 收录原则

每个主题力求包含：

- 对该算法的基本介绍（核心思想、复杂度等）
- 参考链接或书籍章节（讲的比较好的资料）
- 模板代码（可以包含一些注释、使用说明）
- 模板补充内容（常见题型中的额外代码、建模技巧等）
- 相关题目链接（模板题、经典题、思维转换题等）

欢迎通过 Issue 或 Pull Request 提交勘误、补充资料和经过测试的模板；请在提交中说明算法的复杂度、适用条件和测试样例。

## 算法目录

### [基础算法](Basic_Algorithm.md)

- 位运算
- 前缀和 与 差分
- 二分
- 排序
  - 快速选择
  - 逆序对
  - 离散化
  - 中位数
- 倍增
  - ST 表
- 贪心

### [基础数据结构](Basic_Data_Structure.md)

- 栈
  - 卡塔兰数
  - 表达式求值
  - 单调栈
- 队列
  - 单调队列
- 链表
  - Floyd 判圈算法
- Hash
- 堆
  - k 叉Huffman 树

### [搜索](Search_Algorithm.md)

- 拓扑排序
- 深度优先搜索
- 剪枝
- 迭代加深
  - 迭代加深
  - 双向搜索
- 广度优先搜索
- 广搜变形
  - 双端队列 BFS
  - 优先队列 BFS
  - 双向 BFS
- A*
- IDA*

### [字符串](String.md)

- KMP
- 字符串 Hash
- 前缀树 Trie
- Manacher 算法
- 最小表示法

### [数学](Math.md)

- 质数
  - 质数筛
  - 质因数分解
- 约数
  - 约数集合
  - 最大公约数 GCD
    - 更相减损法
    - 欧几里得算法
  - 欧拉函数
    - 积性函数
    - 欧拉函数与积性函数性质
- 同余
  - 欧拉定理
    - 剩余系
    - 费马小定理
    - 欧拉定理
    - 拓展欧拉定理
  - 拓展欧几里得算法
    - 裴蜀定理
    - 拓展欧几里得算法
    - 乘法逆元
  - 线性同余方程
    - 一次同余方程
    - 中国剩余定理
    - 拓展中国剩余定理
  - 高次同余方程
    - BSGS 算法
    - 拓展 BSGS 算法
- 矩阵快速幂应用
- 高斯消元和线性空间
  - 高斯-约旦消元法
  - 线性空间
    - 异或空间
- 组合计数
  - 组合数计算
    - 乘法逆元
    - 卢卡斯定理
  - 多重集计数
    - 多重集排列数
    - 多重集组合数
- 容斥原理 与 莫比乌斯函数
- 概率 与 数学期望
- 0/1 分数规划
- SG 函数

### [高级数据结构](Advanced_Data_Structure.md)

- 并查集
- 树状数组
- 线段树
- 分块
- 点分治
- 二叉查找树和平衡树

### [动态规划](Dynamic_Programming.md)

- 线性 DP
- 背包 DP
  - 0/1 背包
  - 完全背包
  - 多重背包
  - 分组背包
- 区间 DP
- 树形 DP
  - 背包类树形 DP
  - 换根 DP
- 环形 与 后效性处理
- 状态压缩 DP
- 倍增优化 DP
- 数据结构优化 DP
- 单调队列优化 DP
- 斜率优化
- 四边形不等式
- 计数类 DP
- 数位统计 DP

### [图论](Graph_Theory.md)

- 最短路
  - Dijkstra 算法
  - SPFA 算法
  - Floyd 算法
- 最小生成树
- 树的直径 和 最近公共祖先
  - 求树的直径
    - 树上 dp
    - 两次 bfs
  - 求 LCA
    - 倍增求 lca
    - 求 lca 的 Tarjan 算法
- 基环树
- 负环和差分约束
- Tarjan 算法与无向图连通性
- Tarjan 算法与有向图连通性
- 二分图匹配
- 二分图的覆盖和独立集
- 网络流
