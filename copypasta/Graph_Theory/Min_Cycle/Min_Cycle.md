## 基本介绍

最小环问题：给定一个图，问由其中n个节点构成的边权和最小的环（n>3）是多大。

<br/>

<br/>

## 模板代码

#### 无权图([点击访问代码](./Unweighted_Graph.cpp))

当图为无权图时，可以对每一个顶点进行BFS，目的是枚举经过该顶点的最小环。具体BFS过程为，从选定的顶点出发时，记录当前顶点到出发顶点的距离，如果一定顶点被记录了两次，说明遇到了环，此时可以得到环的长度。

<br/>

枚举起点跑BFS解析（[点击访问网页](https://leetcode.cn/problems/shortest-cycle-in-a-graph/solutions/2203585/yi-tu-miao-dong-mei-ju-qi-dian-pao-bfspy-ntck/)）

