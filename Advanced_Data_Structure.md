# 并查集

并查集(Disjoint Set Union)是一种用于管理元素所属集合的数据结构，实现为一个森林，其中每棵树表示一个集合，树中的节点表示对应集合中的元素。并查集至少支持两种操作：

- 合并（unite）：合并两个元素所属集合（合并对应的树）。
- 查询（find）：查询某个元素所属集合（查询对应的树的根节点），这可以用于判断两个元素是否属于同一集合。


**路径压缩和按秩合并**

路径压缩是指每次在执行 $find$ 操作时，把每个访问过的节点直接指向树根。

集合的秩可以定义为树的深度或者是集合的大小，按秩合并是指将秩较小的树合并到秩较大的树上。

通过这两个操作，可以将每次 $find$ 操作的时间复杂度均摊为阿克曼的反函数级别，在比赛的常用的数据范围内，可以视为 $O(1)$ 。

<br/>

**边带权的并查集**

并查集实际上是若干颗树够成的森林。可以在树上每条边记录一个权值，即维护一个数组 $d$ ，用 $d[x]$ 维数节点 $x$ 到 $fa[x]$ 的边权。每次路径压缩的同时更新 $d$ 的值。

```cpp
int find(int x)
{
	if (x == fa[x])
		return x;
	int root = find(fa[x]);
	d[x] += d[fa[x]];   // 以+为例，根据实际维护信息进行修改
	return fa[x] = root;
}
```



<br/>


**带拓展域的并查集**

带拓展域的并查集，即将每个节点拆分为多个域，每个域代表该节点的不同属性。

---


<br/>


<br/>



### 模板代码

[**DSU.cpp**](/copypasta/Advanced_Data_Structure/DSU.cpp) 支持以下操作

- **查询所在集合**：同时进行路径压缩
- **合并**：利用集合大小进行启发式合并

<br/>

[**DSU_simplified.cpp**](/copypasta/Advanced_Data_Structure/DSU_simplified.cpp) 

此模板更为简洁，适合比赛时使用。

---

<br/>


<br/>



### 例题

[**2709. 最大公约数遍历 - 力扣（LeetCode）**](https://leetcode.cn/problems/greatest-common-divisor-traversal/description/)


<br/>


[**237. 程序自动分析 - AcWing题库**](https://www.acwing.com/problem/content/239/)

简单题，属于并查集模板题。

本题的数据范围比较大，但是 $n$ 的范围可以接受，可以先进行离散化。


<br/>


[**145. 超市 - AcWing题库**](https://www.acwing.com/problem/content/147/)

简单题。并查集的应用。

本题也可以使用贪心的算法解决，将所有商品按照利润，从大到小排序，优先考虑利润大的商品，同时商品应该尽量晚点卖出。可以使用并查集优化，快速找到商品可以最晚卖出的时间。


<br/


[**238. 银河英雄传说 - AcWing题库**](https://www.acwing.com/problem/content/240/)

简单题，边带权的并查集的应用。

可以将每列战舰看作是一个集合，用 $d$ 维护每艘战舰之前的战舰数量。


<br/>


[**239. 奇偶游戏 - AcWing题库**](https://www.acwing.com/problem/content/241/)

中等偏难题，关系表示比较复杂。

假如使用 $sum$ 数组表示序列 $S$ 的前缀和，则在每一个回答中：
- 若 $S[l,r]$ 有偶数个 $1$ ，则等价于 $sum[l-1]$ 和 $sum[r]$ 奇偶性相同。
- 若 $S[l,r]$ 有奇数个 $1$  ，则等价于 $sum[l-1]$ 和 $sum[r]$ 奇偶性不同。

本题和 [237. 程序自动分析](https://www.acwing.com/problem/content/239/)类似，都是给定若干个变量和关系，判定这些关系可满足性的问题。但是本题的关系比较复杂，因为**存在 $x_1,x_2$ 奇偶性不同， $x_2,x_3$ 奇偶性不同，而 $x_1,x_3$ 奇偶性相同的情况**。

**解法一**

使用边带权的做法，可以发现，对 $x$ 到树根做异或运算，可以得到 $x$ 和树根的奇偶关系，所以可以维护一个数组 $d$ ， $d[x]$ 表示 $x$ 与 $fa[x]$ 的奇偶性关系。

```cpp
int find(int x)
{
	if (x == fa[x])
		return x;
	int root = find(fa[x]);
	d[x] ^= d[fa[x]];  
	return fa[x] = root;
}
```

**解法二**

使用带拓展域的并查集，把每个节点 $x$ 拆分为两个节点 $x_{odd}$ 和 $x_{even}$ 。

- 如果两个节点奇偶性相同，合并 $x_{odd},y_{odd}$ ，合并 $x_{even},y_{even}$
- 如果两个节点奇偶性不同，合并 $x_{even},y_{odd}$ ，合并 $x_{odd},y_{even}$


<br/>


[**240. 食物链 - AcWing题库**](https://www.acwing.com/problem/content/242/)

中等偏难题，关系表示比较复杂。

使用带拓展域的并查集解决。将每个节点 $x$ ，拆分为三个域——同类 $x_{self}$ ，捕食 $x_{eat}$ ，天敌（被捕食） $x_{enemy}$ 。

- 如果 $x,y$ 是同类，则三个域对应进行合并。
- 如果 $x$ 捕食 $y$ ，则合并 $x_{eat},y_{self}$ ， $x_{self},y_{enemy}$ ， $x_{enemy},y_{eat}$ 。

当然，在合并之间要进行检查是否冲突。


---

<br/>


<br/>


<br/>


<br/>



# 树状数组

树状数组是一种支持 **单点修改** 和 **区间查询** ，且代码量小的数据结构。普通树状数组维护的信息及运算要满足 **结合律** 且 **可差分**，如，加法（和）、乘法（积）、异或等。

- 结合律： $\left( x\cdot y \right) \cdot z=x\cdot \left( y\cdot z \right)$ ，其中 $\cdot$ 是二元运算符。
- 可差分：已知 $\left ( x\cdot y \right)$  和  $x$ ，能够把 $y$ 求出来。 

树状数组能解决的问题是线段树能解决的问题的子集——树状数组能做的，线段树一定能做，线段树能做的，树状数组不一定可以。然而，树状数组的代码要远比线段树短，时间效率常数也更小，因此仍有学习价值。


<br/>

**树状数组原理**

对一个整数总是可以表示为若干个 $2$ 的幂相加的形式，假设数字 $n$ 的二进制表示形式为 $01010110$ ，显然每个 $1$ 对应 $2$ 的幂。可以把一个长度为 $n$ 的数组划分为若干个长度为 $2$ 的幂的子数组。


<br/>


**树状数组与逆序对**

树状数组求解逆序对问题，在数组值域上建立一个树状数组，从数组 $a[i]$ 尾部倒序遍历数组，对于每个 $a[i]$ 求出有多个数比他小，然后在树状数组 $a[i]$ 位置上加一。

当数值范围比较大时，先进行离散化，然后再使用数组数组计算，但是这样求解逆序对不如归并排序方面。

从这也可以看出，树状数组可以<span style="background:#fff88f">**求出一个数组 $a$ 中 每个数 $a[i]$ 两侧，比他小或者大的数有多少个**</span>。



<br/>

**区间增加和单点查询**

普通树状数组擅单点修改和区间查询，可以对一个差分数组 $b[i]$ 建立树状数组。


<br/>


**区间增加和区间查询**

序列 $a$ 前缀和 $a[1-x]$ 整体增加的值为：

$$
\sum_{i=1}^x{\sum_{j=1}^i{b\left[ j \right]}=\sum_{i=1}^x{\left( x-i+1 \right) \times b\left[ i \right]}=\left( x+1 \right) \sum_{i=1}^x{b\left[ i \right]}-\sum_{i=1}^x{i\times b\left[ i \right]}}
$$

所以可以维护两个差分数组，实现区间查询的功能。


---


<br/>


<br/>



### 模板代码

[**BIT.cpp**](/copypasta/Advanced_Data_Structure/BIT.cpp) 以维护区间和为例，支持以下操作：

- **求 1 到 i 的区间和**：时间复杂度为 $log_2^n$ 。在此基础上进行修改可以实现求任意区间和，需要注意，树状数组的下标是从 1 开始的。
- **单点修改**：即修改当个点值。时间复杂度为 $log_2^n$ 。


<br/>


[**BIT_Diff.cpp**](/copypasta/Advanced_Data_Structure/BIT_Diff.cpp) 以维护区间和为例，利用差分，实现了区间修改
- **区间和**：时间复杂度为 $log_2^n$ 。
- **区间加**：区间每一个数都加上同一个数。时间复杂度为 $log_2^n$ 。


---


<br/>


<br/>


### 参考资料



- [OIwiki树状数组介绍](https://oi-wiki.org/ds/fenwick/)

- [manim | 算法 | 数据结构](https://www.bilibili.com/video/BV1pE41197Qj/?spm_id_from=333.337.search-card.all.click&vd_source=a7d5a38480a5acb21de3325d1ec0cf14) :差分树状数组原理讲解部分

---


<br/>


<br/>



### 例题

[**2659. 将数组清空**](https://leetcode.cn/problems/make-array-empty/)

困难题。思维题。


<br/>


[**241. 楼兰图腾 - AcWing题库**](https://www.acwing.com/problem/content/243/)

简单题。

树状数组的经典应用，求出一个数组中，每个元素两侧各有多少个数比他大或者小。


<br/>


[**242. 一个简单的整数问题 - AcWing题库**](https://www.acwing.com/problem/content/248/)

简单题。

使用树状数组维护一个差分数组。


<br/>


[**243. 一个简单的整数问题2 - AcWing题库**](https://www.acwing.com/problem/content/244/)

简单题。

使用数组数组维护两个差分数组。


<br/>


[**244. 谜一样的牛 - AcWing题库**](https://www.acwing.com/problem/content/description/245/)

维护一个 01 序列，从后往前遍历，第 $a[i]+1$ 个 $1$ 出现的位置就是身高。同时这个 $1$ 置为 $0$ 。

显然可以使用树状数组维护 01 序列，在查找第 $a[i]+1$ 个 $1$ 出现的位置时，有两种方法：
- 二分：时间复杂度为 $(log \ n)^2$
- **倍增**：由树状数组的原理可知，从大区间往小区间开始枚举。时间复杂度为 $O(log \ n)$ 。需要注意，在**进行条件判断时，使用 $<$ ，这样"差一步"，可以避免找到答案是 $1$ 后面那几个 $0$ 对应的位置** 。



---


<br/>


<br/>


<br/>


<br/>


# 线段树

## 普通线段树

线段树是基于分治思想的二叉树结构，是算法竞赛中常用的用来维护 **区间信息** 的数据结构。线段树可以在 $log \  N$ 的时间复杂度内实现单点修改、区间修改、区间查询等操作。

线段树能够维护的信息要能够满足 **结合律** 以及 **支持快速合并**：
- GCD
- 区间和
- 区间最大值
- 区间最小值


### 模板代码

[**SegTree.cpp**](/copypasta/Advanced_Data_Structure/SegTree.cpp)

以维护区间和为例。支持区间查询和单点修改。

---


<br/>


### 例题

[**246. 区间最大公约数 - AcWing题库**](https://www.acwing.com/problem/content/247/)

困难题。有<span style="background:#fff88f">**区间修改，查询区间 gcd**</span>。

区间 gcd 显然是可以使用线段树进行维护的，本题的难点在于需要进行区间更改。对于区间更改，一般是使用懒惰标记实现，但是本题很难实现 pushdown 操作，无法使用 lazy tag 的值，快速更新当前节点的值。

根据更相减损法，有 $gcd(a,b,c,d)=gcd(a,b-a,c-b,d-c)$ ，如果把 $b,c$ 同时加上 $x$ ，有 $gcd(a,b+x,c+x,d)=gcd(a,b-a+x,b-c,d-c-x)$ 。所以可以使用线段树维护差分数组的 gcd，使用树状数组维护差分数组。


---


<br/>


<br/>


<br/>



## 延迟标记

延迟标记也称为 lazy tag。给每一个节点增加一个延迟标记，标识**该节点曾经被修改过，但是其子节点还未更新**。

延迟标记一般用于实现线段树的区间修改，对于一个节点，要求其**能够根据 lazy tag 的值，更新当前节点的值**，然后把 lazy tag 的下放给子节点。

**当需要进行查询或者更改时，从根节点往下遍历时，先要下放当前节点的延迟标记**。


### 模板代码

[**SegTree_lazytag.cpp**](/copypasta/Advanced_Data_Structure/SegTree_lazytag.cpp)


带有延迟标记的线段树。以维护区间和为例，支持区间查询和区间修改（一个区间全部加上一个数）。

---

<br/>

### 例题


[**1157. 子数组中占绝大多数的元素**](https://leetcode.cn/problems/online-majority-element-in-subarray/)

统计**区间 <span style="background:#fff88f">绝对众数</span> 及其出现次数** 。众数本身并不满足区间快速合并。统计众数使用摩尔投票法，可以得出一个 $candidate$ 和 $cnt$ （并不是指出现次数）。根据摩尔投票法，这个是满足可加性的。

所以使用线段树维护区间的 $candidate$ 和 $cnt$ ，在查询时，可以快速得出该区间绝对众数的**可能值**。所以还需要进行验证，显然不能直接遍历数组。可以预处理出来每一个值对应的下标。在线段树求出绝对众数的可能值之后，进行二分可以得出其在该区间的出现次数。


<br/>

[**2213. 由单个字符重复的最长子字符串**](https://leetcode.cn/problems/longest-substring-of-one-repeating-character/)

**最长连续相同子串问题**。和连续子数组最大区间和问题一样，都是维护一个 $pre$ ， $suf$ 和 $max$ 。只是在合并区间都逻辑有些许不同。


<br/>

[**2569. 更新数组后处理求和查询**](https://leetcode.cn/problems/handling-sum-queries-after-update/)

关于区间 01 反转的懒惰更新问题。


---


<br/>


<br/>


<br/>


## 扫描线

扫描线是一种算法思想，对于二维平面上的一些矩形（边平行于坐标轴）。可以将矩形的边界用一个四元组 $<x,y_1,y_2,tag>$ 表示，其中 $tag$ 有特殊的含义，根据题目来确定。可以按照 $x$ 从小到排序，让一条与 $y$ 轴平行的直线，从左到右进行扫描。

扫描到一个 $<x,y_1,y_2,tag>$ 对区间 $[y_1,y_2]$ 进行对应的操作，这通常使用带延迟标记的线段树实现，另外如果有必要可以对 $y$ 进行离散化。


### 例题

[**247. 亚特兰蒂斯 - AcWing题库**](https://www.acwing.com/problem/content/249/)

困难题。

利用扫描线实现求解多个矩形的面积并。在实现时可以将矩形左边表示为 $<x_1,y_1,y_2,1>$ ，右边表示为 $<x_1,y_1,y_2,-1>$ 。用线段树维护 $y$ 小区间，只有区间和大于零的区间，才能乘以横坐标贡献面积。

在本题中，由于 $y$ 的范围比较大，并且不为整数，所以需要离散化。因此，线段树维护的是可以用的 $y$ 区间实际长度。没法利用，延迟标记快速更新当前节点的值。但是由于矩形的左右两条边是成对出现的，所以对线段树的区间修改也是成对出现的， 可以不下放延迟标记。

由此，不妨思考为什么通常情况下要下放延迟标记。因为通常情况下，要进行区间的查询，而在本题中仅仅查询根节点，另外在本题中，延迟标记永远不可能小于 0。


<br/>


[**248. 窗内的星星 - AcWing题库**](https://www.acwing.com/problem/content/250/)

困难题。

可以处理得出每一颗星星可以圈住其的矩形的右上角坐标范围，其必然是一个矩形区域。因此问题转化为求那个坐标重叠区域权值最大。


---


<br/>


<br/>


<br/>


## 动态开点线段树


在一些计数问题中，线段树用于维护值域，这样的线段树也被称为**权值线段树**。

为了降低空间复杂度，可以不建出整棵树的结构，而是最初只建立一个根节点，代表整个区间，当需要访问线段树子区间时，再建立这个子区间的节点。这就是**动态开点的线段树**，其抛弃了线段树完全二叉树父子节点二倍的编号规则，使用变量记录左右节点的编号，节点代表的区间在递归访问的过程中作为参数传递。


```cpp
const int N = 1e5;

struct SegTree {
    int lc, rc; // 左右子节点代表的编号
    int dat;
} tr[2 * N];
int root, tot;

// 建立新节点
int build()
{
    ++tot;
    tr[tot].lc = tr[tot].rc = tr[tot].dat = 0;
    return tot;
}

// 单点修改
void insert(int k, int l, int r, int idx, int delta)
{
    if (l == r) {
        tr[k].dat += delta;
        return;
    }
    int mid = (l + r) >> 1;
    if (idx <= mid) {
        if (!tr[k].lc)
            tr[k].lc = build();
        insert(tr[k].lc, l, mid, idx, delta);
    }
    if (idx > mid) {
        if (!tr[k].rc)
            tr[k].rc = build();
        insert(tr[k].rc, mid + 1, r, idx, delta);
    }
    tr[k].dat = max(tr[tr[k].lc].dat, tr[tr[k].rc].dat);
}
```


如果有若干颗线段树，都维护相同的值域，那么他们对应各个子区间的划分显然是一样的，可以使用线段树合并算法，依次合并两颗树。
```cpp
int merge(int p, int q, int l, int r)
{
    if (!p)
        return q;
    if (!q)
        return p;
    if (l == r) {
        // 在此进行两个叶子节点合并操作
        return p;
    }
    int mid = (l + r) >> 1;
    tr[p].lc = merge(tr[p].lc, tr[q].lc, l, mid);
    tr[p].rc = merge(tr[p].rc, tr[q].rc, mid + 1, r);

    // 自下而上合并信息
    // tr[p].dat=.......

    return p;
}
```



---


<br/>


<br/>


<br/>


## 可持久化线段树

可持久化线段树又称为主席树，是一种使用函数式编程思想的线段树，支持查询历史版本，并且利用历史版本之间的共用数据减少时间和空间消耗。


一个普通的动态开点线段树的空间大小为 $2*N-1$ ，而一次修改会改变 $log\ N+1$ 个节点，所有保存经过 $m$ 次修改的可持久化线段树的空间消耗为 $2\times N+M\times (log\ N+1)$ 。

```cpp
const int N = 1e5 + 1, M = 1e4 + 1;
struct SegTree
{
	int lc, rc;
	int dat;
} tree[32 * N];

int tot, root[N]; // 当时节点总数 和 每次历史版本的根节点

int build(int l, int r)
{
	int p = ++tot;
	tree[p].dat = 0;
	if (l == r)
		return p;
	int mid = (l + r) >> 1;
	tree[p].lc = build(l, mid);
	tree[p].rc = build(mid + 1, r);
	return  p;
}

int insert(int now,int l,int r,int x,int delta)
{
	// 新建一个节点
	int p=++tot;
	tree[p]=tree[now]; // 利用上一次的共同节点
	if(l==r)
	{
		tree[p].dat+=delta;
		return p;
	}
	int mid=(l+r)>>1;
	if(x<=mid)
		tree[p].lc=insert(tree[now].lc,l,mid,x,delta);
	else
		tree[p].rc=insert(tree[now].rc,mid+1,r,x,delta);
	tree[p].dat=tree[tree[p].lc].dat+tree[tree[p].rc].dat;
	return p;
}
```





### 例题


[**255. 第K小数 - AcWing题库**](https://www.acwing.com/problem/content/257/)


首先不考虑 $l_i,r_i$ ，在线段树上维护有多少个数落在值域区间 $[L,R]$ 上面，所以可以建立一个权值线段树，每个节点维护落在值落在 $[L,R]$ 的元素个数，对于一个查询，只需要比较 $cnt_{L,mid}$ 和 $k$ 之间的关系，就能知道第 $k$ 个数是落在该节点维护的左子区间还有有子区间。

考虑 $l_i,r_i$ ，已知两个不同的历史版本的线段树相减后得到的是变化的部分，不妨对于序列 $A$ 每个元素，插入之后都建立一个历史版本，将 $r_i$ 和 $l_i-1$ 代表的两个版本相减，得到区间 $l_i,r_i$ 中有多少个数落在值域 $[L,R]$ 中。


---



<br/>


<br/>


<br/>


<br/>


# 分块

分块算法基本思想是通过适当的划分，预处理一部分信息并保存下来，用空间换时间。分块的效率往往比不上树状数组和线段树，但是更加通用，更容易实现。大部分分块算法都是基于"**大段维护、小段朴素**"的思想。


<br/>


### 例题

[**249. 蒲公英 - AcWing题库**](https://www.acwing.com/problem/content/description/251/)

**在线求区间众数**，因为众数不具有区间可加性。可以分块进行处理。由于本题 $a[i]$ 的数值范围比较大，所以先进行离散化。

预处理出所以以段边界为端点的区间的众数，另外对离散化之后的每一个数值建立一个 vector 保存其出现的下标，便于后面二分判断。



----

<br/>


<br/>


<br/>


<br/>





