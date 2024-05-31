# 最短路

## 单源最短路径

$V$ 为顶点集， $E$ 为边集， $|V|=n$ ， $|E|=m$ 。单源最短路问题就是求从一个出发点到其余各个出发点的最短路径长度的问题。

### Dijkstra 算法

Dijkstra 算法能解决<span style="background:#fff88f">**边权非负**</span>的有向图（无向图）的单起点最短路径问题。Dijkstra 算法基于贪心思想，每次选出当前距离起点最近的节点进行松弛，当变长都是非负数时，全局最小值不可能再被其他节点更新。


- [**Dijkstra.cpp**](/copypasta/Graph_Theory/Dijkstra.cpp)

	模板代码使用一个优先队列维护距离起点距离最小的节点，应该主义在使用 `priority_queue` 时，在**重载节点的  <  运算符时，不要直接使用全局的  dis[]  直接进行比较**，dis[ ]  数组随时会被更新，可能会让堆失去有序性。一般将距离 d 也作为一个变量放入 NODE 中。

算法时间复杂度为 $O(m\times log n)$ 。

---

<br/>


<br/>



### 无环有权图最短路

Dijkstra 算法不能处理边权为负数的情况。当<span style="background:#fff88f">**图中不含环**</span>时，即使边权为负数，存在时间复杂度为 $O(m+n)$ 的最短路径算法：
- 拓扑排序得到拓扑序列
- 按照拓扑序列进行节点的拓展

算法的正确性很直观，按照拓扑序列拓展节点，当一个节点被拓展时，在它之间的全部节点不可能会被更新了。

---

<br/>


<br/>


### Bellman-Ford 算法

当图中存在边权为负的情况，可能会为了经过负数权值的边而暂时绕更远的路。

朴素 Bellman-Ford 算法，会重复进行 $|V|=n$ 轮的拓展，每一轮中会对所有节点进行拓展，并且不会规定拓展的顺序。时间复杂度为 $O(n\times m)$ 。

朴素 Bellman-Ford 效率较低的根本原因是，在一轮拓展中，许多节点没有必要进行拓展，**只有在上一轮被更新的节点，进行拓展才有意义**。因此，可以维护一个队列，只有被更新的节点才会放入队列中等待拓展。队列优化的 bellman-Ford 算法又被称为 **SPFA** 。

- [**SPFA.cpp**](/copypasta/Graph_Theory/SPFA.cpp)

	算法在实现时，需要注意使用一个数组标记节点是否在队列中，如果在队列中待拓展，就不再重复入队，节点出队时，需要更新数组。**SPFA 在稀疏图上运行效率较高**，时间复杂度为 $O(k\times |E|)$ 级别。在稠密图上，算法可能退化为朴素 Bellman-Ford 。

	以上 SPFA 模板代码时检测队列是否为空来确定是否结束循环，**如果图中存在负环（环上权值之和为负），则算法会陷入死循环**。

Bellman-Ford 最多只会拓展 $|V|=n$ 轮，可以**利用 Bellman-Ford 检测负环**——如果进行了 $n$ 轮拓展之后，队列不为空（还需要进行拓展），则图中存在负环。

---


<br/>


<br/>



### 例题


[**340. 通信线路 - AcWing题库**](https://www.acwing.com/problem/content/342/)

本题是要在无向图上求出一条 $1$ 到 $N$ 的路径，使路径第 $K+1$ 大的边权尽量小。

- 解法一：分层图动态规划

	按照动态规划的思想，设 $d[x,p]$ 为从 $1$ 号点到基站 $x$ ，途中使用了 $p$ 条免费电缆，进过的最贵电缆花费。动态规划本质上是在有向无环图上进行状态转移，在本题中，可能存在有环的情况。一种解决方案是利用迭代思想，借助 $spfa$ 算法进行动态规划，直到所有状态收敛。

	从最短路径的角度考虑，一个状态 $(x,p)$ 就可以视为一个节点，可以转化为最短路问题。

- 解法二：二分答案，双端队列 BFS

	可以对答案进行二分，对 $mid$ 进行判定，是否存在合法方案使得花费不超过 $mid$ 。

	可以把价格超过 $mid$ 的边看作长度为 $0$ ，不超过 $mid$ 的边视为长度为 $0$ 。求 $1$ 到 $N$ 的最短路，判断是否超过 $K$ 。由于边的取值只有 $0$ 和 $1$ ，可以不使用 $dijktra$ ，而是使用双端队列 BFS。


<br/>


[**341. 最优贸易 - AcWing题库**](https://www.acwing.com/problem/content/343/)

本题是在在有向图上找到一条从 $1$ 到 $n$ 的路径，使路径上两个点 $p,q$ （先经过 $p$ ）的权值之差 $W_q-W_p$ 最大。

在图上进行 $spfa$ 求出从 $1$ 出发到其余所有点的路径上能进过的权值最小的节点的权值。同理，在反向图求出从 $n$ 出发到其余所有点的路径上能进过的权值最大的节点的权值。


<br/>

[**342. 道路与航线 - AcWing题库**](https://www.acwing.com/problem/content/344/)

单源最短路问题。**局部 Dijsktra+整体拓扑**。

图中带有负边，所以不能使用 Dijkstra 算法，而本题的数据经过特殊构造，使用 spfa 算法会 TLE。所以不妨思考本题的特殊之处：双向边都是非负的，单向边可能是负的。

把单向边去掉，图会变成多个连通块，每个连通块内部显然可以使用 Dijkstra 算法。而对于每个块，将每个连通块视为一个节点，使用有向无环图的最短路算法：按照拓扑序进行拓展。

在代码实现时，在对一个连通块使用 Dijkstra 算法，初始要把块中所有节点入堆中，以便于能对航线（连接连通块的单向边）进行拓展，让拓扑排序进行下去。

---


<br/>


<br/>


<br/>


## 任意两点之间最短路径

### Floyd 算法

对于图中任意两点的最短路问题，使用求解 $n$ 次的单源最短路问题，这样最好的时间复杂度为 $O(n\times m\times logn)$ 或 $O(n\times m\times k)$ 。当图很**稠密**时（ $m$ 太大 ）时，使用 Floyd 算法可以在 $O(n^3)$ 时间内完成求解。

Floyd 算法的本质是动态规划， $f(k,i,j)$ 表示节点 $i$ 和 $j$ 之间经过**<span style="background:#fff88f">若干个节点编号不超过 $k$</span>** 的节点 的最短路长度。

$$
f\left( k,i,j \right) =\min \left\{ \begin{array}{l}
	f\left( k-1,i,j \right) \ ,\ \text{不经过节点}k\\
	f\left( k-1,i,k \right) +f\left( k-1,k,j \right) \ ,\ \text{经过节点}k\\
\end{array} \right. 
$$


- [**Floyd.cpp**](/copypasta/Graph_Theory/Floyd.cpp)

	需要注意<span style="background:#fff88f">**平行边**</span>的情况，在初始化 dis 数组时，要进行比较。


---


<br/>


<br/>


### 传递闭包


在交际网络中，给定若干个元素和若干对二元关系，且关系具有传递性。传递闭包就是通过传递性推导出尽量多元素之间的关系。


---


<br/>


<br/>

### 例题

[**343. 排序 - AcWing题库**](https://www.acwing.com/problem/content/345/)

有向关系的传递闭包。


<br/>


[**344. 观光之旅 - AcWing题库**](https://www.acwing.com/problem/content/346/)

该问题称为<span style="background:#fff88f">**无向图的最小环问题**</span>。

**使用 Floyd 算法解决**。考虑 Floyd 算法的过程，在外层循环 $k$ 刚开始时， $d[i][j]$ 保存则经过若干个节点编号不超过 $k-1$ 从 $i$ 到 $j$ 的最短路。则 $\underset{1\le i<j<k}{\min}\left\{ d\left[ i \right] \left[ j \right] +a\left[ j,k \right] +a\left[ k,i \right] \right\}$ 表示有节点编号不超过 $k$ ，且经过 节点 $k$ 的最小环。

本题在代码实现时，需要注意，使用邻接矩阵表示边， $inf=0x3f3f3f3f$ 表示没有边界。由于存在三个变量相加的情况，有可能会溢出，所以需要强制类型转换为 long long，注意不能直接使用 `#define int long long`，因为使用了 `memset(d,0x3f,sizeof d)`。

**对于最小环问题，还可以使用 Dijkstra 算法**，枚举每个节点作为起点的情况。假设以 $s$ 作为起点，当 $s$ 第二次从堆中取出时， $d[s]$ 就是经过点 $s$ 的最小环长度。


<br/>


[**345. 牛站 - AcWing题库**](https://www.acwing.com/problem/content/347/)

<span style="background:#fff88f">**恰好经过 $k$ 条边的最短路问题**</span>。

使用邻接矩阵 $A[i,j]$ 存储边，此时可以视 $A[i,j]$ 为进过一条边从 $i$ 到 $j$ 的最短路。则 $A^m$ 表示恰好经过 $m$ 条边的最短路。有

$$
A^{p+q}\left[ i,j \right] =\underset{1\le p\le q}{\min}\left\{ A^p\left[ i,k \right] +A^q\left[ k,j \right] \right\} 
$$

可以看出这是一个广义的矩阵乘法——使用 $min$ 代替原来的乘法，使用 $+$ 代替原来的乘法。所以可以使用矩阵快速幂来加速递推，求出 $A^k$ 。





---


<br/>


<br/>


<br/>


<br/>


# 最小生成树


## Kruskal 算法

Kruskal 算法将所有边按照权值从小到大排序，每一次取出一条边，直到取出 $|V|-1$ 条边，对于每一条加入的边，需要保证和已经加入的边不会构成环。


- [**Kruskal.cpp**](/copypasta/Graph_Theory/Kruskal.cpp)

	算法的主要时间代价在于对边集的排序，时间复杂度为 $O(m\times log m)$ 。


### 例题

[**346. 走廊泼水节 - AcWing题库**](https://www.acwing.com/problem/content/348/)

本题是要对一棵无根树进行添加边的操作，直到变成完全图，同时要求该完全图的最小生成树是原来的无根树（唯一），求添加到边的权值之和最小是多少。

考虑 Kruskal 算法的流程：边按照权值从小到排序，选出一条权值为 $w$ 边然后连接边两端的集合（连通块），假设两端的连通块的大小分别为 $x,y$ 则还可以添加 $x\times y-1$ 条边，添加到边的权值最小为 $w+1$ 。本题得解。


<br/>

[**347. 野餐规划 - AcWing题库**](https://www.acwing.com/problem/content/description/349/)

本题本质上是求无向图的最小生成树，同时使得中心节点（停车场）的度数不超过给定的 $S$ 。




---


<br/>


<br/>

## Prim 算法

Prim 算法总是维护 MST 的一部分，设已经确定属于 MST 的集合为 $T$ ，剩余节点集合为 $S$ ，Prim 算法找到 $\min _{x\in S, y\in T}\left\{ Z \right\}$ ，即两端分别属于集合 $S$ 和 $T$ 的权值最小的边，然后把 $x$ 从集合 $S$ 中删除，然后加入 $T$ 。

可以使用一个数组 dis 维护节点与集合 $T$ 中节点之间权值最小的边的权值。

- [**Prim.cpp**](/copypasta/Graph_Theory/Prim.cpp)

	算法时间复杂度为 $O(n^2)$ ，可以使用二叉堆优化为 $O(m\times logn)$ ，但是使用二叉堆优化还不如使用 Krusal 方便。因此，**Prim 算法主要用于稠密图**。


---



<br/>


<br/>


<br/>


<br/>


# 树的直径 &  LCA

## 树的直径

树的直径是树上最远的两个节点之间的距离，连接这两个点的路径也被称为最长链。

树的直径有两种求法，时间复杂度都是 $O(n)$ 。

**树形 DP 求直径**

以任意一个节点为根。 $D[x]$ 为从节点 $x$ 出发，走向其子树能到达的最远距离，有 $D\left[ x \right] =\underset{1\le i\le t}{\max}\left\{ D\left[ y_i \right] +edge\left[ x, y_i \right] \right\}$ 。

令 $F[x]$ 为经过节点 $x$ 的最长链的长度。则，

$$
F\left[ x \right] =\underset{1\le j<i\le t}{\max}\left\{ D\left[ y_i \right] +D\left[ y_j \right] +edge\left( x,y_i \right) +edge\left( x,y_j \right) \right\} 
$$

在代码实现时，不需要枚举 $i,j$ 。

```cpp
void dp(int pre, int x)
{
	for (auto [y, w] : g[x])
	{
		if (y != pre)
		{
			dp(y);
			ans = max(ans, d[x] + w);
			d[x] = max(d[x], d[y] + w);
		}
	}
}
```



<br/>


**两次 BFS 求直径**

该方法**只适用于<span style="background:#fff88f">边权非负</span>** 的情况。两次 BFS，更容易计算出直径上具体点。
- 从任意一个节点出发，通过 BFS 或者 DFS，求出距离出发点最远的节点 $p$ 。
- 从节点 $p$ 出发，通过 BFS 或者 DFS，求出与 $p$ 距离最远的节点 $q$ 。从 $p$ 到 $q$ 的路径就是树的最长链。


---


<br/>


<br/>


<br/>


## 最近公共祖先


求 LCA（Lowest Common Ancestor） 主要有三种方法。

### 朴素算法

从 $x$ 向上走到根节点，标记走过所有节点。从 $y$ 向上走到根节点，当第一次遇到已经标记的节点，就找到了 LCA 。

---

<br/>

<br/>


### 树上倍增法

设 $F[x,k]$ 表示 $x$ 的 $2^k$ 辈祖先，即， 从 $x$ 向上走 $2^k$ 步到达的节点。求 $lca(x,y)$ ，不妨设 $d[x]>=d[y]$ ，步骤如下：
- 通过二进制拆分的方式将 $x$ 向上调整到和 $y$ 同一深度，如果 $x==y$ ，返回答案.
- 通过二进制拆分，将 $x,y$ 同时向上调整。注意这里使用"**差一步**"的方式，避免找到的是 lca 之上的节点。

```cpp
int lca(int x, int y)
{
	if (d[x] < d[y])
		swap(x, y);
	int t = log2(n);
	// 将x向上调整到和y同一深度
	for (int i = t; i >= 0; --i)
		if (d[f[x][i]] >= d[y])
			x = f[x][i];

	if (x == y)
		return x;

	for (int i = t; i >= 0; --i)
		if (f[x][i] != f[y][i])
			x = f[x][i], y = f[y][i];
	return f[x][0]; //最后向上走一步
}
```

---


<br/>

<br/>



### LCA 的 Tarjna 算法

Tarjan 算法本质上是使用并查集对向上标记法的优化，是一个离线算法，需要把询问统一读入，统一处理。

当正在访问一个节点 $x$ 时（或者其子树中的节点），以 $x$ 为根节点的子树的所有节点 $y_i$ （包括 $x$ 本身 ）都有 $fa[y_i]=x$ 。在完成 $x$ 的访问，回溯到其父节点 $z$ 后，令 $fa[x]=z$ 。

可以看出，当求 $lca(x,y)$ 且 ** $x$ 已经被访问过**，正在访问 $y$ ，则有 $lca(x,y)=find(x)$ 。

---


<br/>


<br/>


<br/>


## 树上差分

