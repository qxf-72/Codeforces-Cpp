# 栈

栈是一种先进后出的线性数据结构。C++STL 中有栈的实现 `stack<>`。以下讨论栈的应用。


## 包含 Min 函数的栈

即入栈、出栈、查询栈中最小值，这三个操作时间复杂度皆为 O (1) 的栈。

首先考虑堆来实现，将元素和下标值存入堆中，这样可以出栈和入栈时更新，但是查询时间复杂度为 log (N)。如果仅仅使用一个变量来记录最小值，这样出栈操作之后，无法得知最小值是否被出栈。

可以使用另一个栈，同步更新历史最小值。

```cpp
class MinStack
{
	stack<int> stk, stk_min;
 public:
	MinStack(){ }

	void push(int x)
	{
		stk.push(x);
		if (stk_min.empty())
			stk_min.push(x);
		else
			stk_min.push(min(stk_min.top(), x));
	}

	void pop()
	{
		if(!stk.empty())
		{
			stk.pop();
			stk_min.pop();
		}
	}

	int top()
	{
		return stk.top();
	}

	int getMin()
	{
		return stk_min.top();
	}
};
```

### 相关题目

[**41. 包含min函数的栈 - AcWing题库**](https://www.acwing.com/problem/content/90/)


---

<br/>


<br/>


<br/>



## 出栈序列问题

n 个数字依次进栈，进栈之后可以随时出栈，问有多少种出栈序列。

当不仅仅求序列数量，还需列出序列时，使用 dfs 进行搜索，每一次可以选择将数字入栈，或者将栈顶数字出栈，复杂度 O (2^N)。

如果仅仅序列的数量，等价于求 第 N 项 **Catalan 数**

$$
\frac{C_{2n}^{n}}{n+1}
$$

当 N 很大时，需要结合高精度运算，因为是求组合数，并且不存在分母有质因数 k 而分子没有的情况，所以将卡塔兰数进行质因数分解，然后再计算。


### 相关题目

[**130. 火车进出栈问题 - AcWing题库**](https://www.acwing.com/problem/content/132/)

结合**压位高精度**求解和质因数分解求卡塔兰数。

---

<br/>


<br/>


<br/>



## 表达式计算

表达式计算是栈的经典应用，表达式分为三类：
- 中缀表达式：常见的表达式
- 前缀表达式：波兰式，`op A B`
- 后缀表达式：逆波兰式，`A B op`

**后缀表达式求值**
- 遇到一个数，先入栈
- 遇到运算符，将栈顶两个数出栈进行计算，将结果入栈

**中缀表达式转后缀表达式**
- 遇到一个数，直接输出
- 遇到左括号，入栈
- 遇到右括号，不断取栈顶出栈，直到遇到左括号
- 遇到运算符，只要栈顶运算符优先级**大于等于**新运算符（在具体实现时，可以将左括号优先级最低），不断取栈顶出栈，最后新运算符入栈（**优先级高的先出栈计算**）。
- 最后将栈中剩余运算符一一弹出。

---

<br/>


<br/>


<br/>


## 单调栈

单调栈即满足单调性的栈结构。

单调栈适合用于寻找序列中**下一个更大**、**下一个更小**的元素。单调栈就是在遍历序列的同时，根据当前遍历的点元素的大小选择是否将目前栈顶元素弹出，有两种选择策略：
- 当前元素 > 栈顶元素，将栈顶元素弹出：当前元素对于被弹出的元素，就是下一个更大元素。
- 当前元素 < 栈顶元素，将栈顶元素弹出：当前元素对于被弹出的元素，就是下一个更小元素。

可以一直弹出直到不满足条件或者栈为空，然后将当前元素入栈。当遍历完序列之后，栈中的元素必然是单调的，其栈中元素在原序列中不存在下一个更大（更小）的元素（具有 下一个更大（更小元素） 的元素已经在上述遍历过程被弹出栈）。

单调栈常常与**贡献法**结合，贡献法就是考虑每个元素对于答案的贡献，通常结合单调栈寻找元素的作用边界。

### 模板代码

[**Monotonic_Stack.cpp**](/copypasta/Basic_Data_Structure/Monotonic_Stack.cpp)

模板的代码以下一个更小的元素为例，可以求出该元素前后 第一个更小元素的下标。此时可以得到**以该元素为最小值的最大区间边界**。将数组中的元素取反，此时求的就是下一个更大元素。

通常与贡献法结合，此外还可以求柱状图的最大矩形面积。

### 相关题目

[**131. 直方图中最大的矩形 - AcWing题库**](https://www.acwing.com/problem/content/133/)

贡献法思想求解，对于每个元素，求出上一个和下一个 更小元素的 index，得出该元素的对答案的贡献的范围，更新答案。


---

<br/>


<br/>


<br/>


<br/>


# 队列

队列是一种"先进先出"的线性数据结构，为了节省开头空间， 一般将其实现为**循环队列**。C++STL 中有队列的实现 `queue` 和 `deque`。


## 单调队列

> 给出一个长度为 n 的数组，输出每 k 个连续的数中的最大值、最小值。

以求最大值为例，**单调队列维护信息的本质是，一个元素入队时将队内比他小的元素踢出**（被踢出元素必然不是当前维护区间的最大值）。

**算法步骤**
- 如果当前元素的值 > 队尾元素， **队尾出队**，直到队尾 > 当前元素。然后将当前元素入队。
- 判断队头元素是否超出范围，如果超出就**队头出队**。
- 此时队头就是答案。

根据题目情况，第一步和第二步的执行顺序可能会调换。


### 相关题目

[**135. 最大子序和 - AcWing题库**](https://www.acwing.com/problem/content/137/)

---


<br/>


<br/>


<br/>


<br/>




# 链表

链表和二叉树主要是在工作面试中考察。下面讨论 C++STL 中链表的使用，和一些相关算法。

## list 和 forward_list

`list `是双向链表。`forward_list` 为单链表，`forward_list` 不提供 `size` 操作，效率接近手写的链表，此外，`forward_list `的插入操作与其他容器很不一样，是在指定位置之后插入。

---

<br/>


<br/>


<br/>


## Floyd 判圈算法

### Floyd 判圈算法

又称**龟兔赛跑算法**(Tortoise and Hare Algorithm)，是一个可以在有限状态机、迭代函数或者链表上判断是否存在环，求出该环的起点与长度的算法。该算法据高德纳称由美国科学家罗伯特-弗洛伊德发明。

该算法可以在不使用常量空间的情况下，使用线性的时间来判断链表是否存在环。主要依赖快慢指针。fast 指针一次走两步，slow 指针一次走一步，如果存在环，两者必定会相遇。

<br/>

### 求环的起点

假设慢指针走了 x 步，则快指针走了 2 x 步，设非环部分长度为 a，环长度为 b，可得：

$$
2x-x=kb,即 \ \ x=kb
$$

所以慢指针在环中走了 $kx-a$ 步，如果**再走 $k$ 步**，就是 $(k+1)b$ 步，此时位于**环的起点**。只需要增加一个指针 p 指向头部，和 slow 指针一起移动直到相遇即可。

### 相关题目 

[**141. 环形链表**](https://leetcode.cn/problems/linked-list-cycle/)

<br/>

[**142. 环形链表 II**](https://leetcode.cn/problems/linked-list-cycle-ii/)

---


<br/>


<br/>


<br/>


<br/>


# 哈希表

C++STL 中有哈希表的实现 `unordered_map`，但是只有少部分内置类型，有哈希函数，所以很多时候需要自己手写哈希函数。

对于 `unordered_map`，需要提供一个类对象，实现 `()` 的重载，返回类型为 `size_t`。

```cpp
// 自定义pair的哈希函数
struct PairHash {
    template<typename T1, typename T2>
    size_t operator() (const pair<T1, T2>& p) const {
        auto h1 = hash<T1>()(p.first);
        auto h2 = hash<T2>()(p.second);
        // 通过位运算将两个哈希值合并
        return h1 ^ (h2 << 1);
    }
};

int main() {
    // 定义一个pair类型的哈希表
    unordered_set<pair<int, int>, PairHash> myset;
    // 向哈希表中插入元素
    myset.insert({1, 2});
    myset.insert({3, 4});

    // 遍历哈希表
    for (auto& p : myset) {
        cout << "(" << p.first << ", " << p.second << ")" << endl;
    }

    return 0;
}
```


**重写哈希函数之后，并不意味着 key 算出来哈希值一样就放入同一个地方，还需判断 key 本身是不是一样的**。如果需要存储多对一的映射关系，可以将 key 值设置为 size_t，使用自己的哈希函数计算哈希值而不是将函数传递给 unordered_map。


### 例题

[**137. 雪花雪花雪花 - AcWing题库**](https://www.acwing.com/problem/content/139/)

---


<br/>


<br/>


<br/>


<br/>


# 二叉堆

二叉堆是一种支持插入、删除、查询最值的数据结构。

## 堆

C++STL 中实现了堆的数据结构—— `priority_queue< >`，默认为大根堆，支持 push、top、pop 三种操作。

### 相关题目

[**145. 超市 - AcWing题库**](https://www.acwing.com/problem/content/147/) 

对于每个时间 t，应该在保证不卖出过期商品的同时，尽量卖出前 t 大的商品。把商品按照过期时间排序，从头扫描每个商品，查看在该日期前最大能买多少利润，使用小根堆进行维护。同时也可以按利润降序排序，优先选择利润高的商品，然后剔除一个在过期日期之前的时间，可以使用并查集优化。

<br/>


[**146. 序列 - AcWing题库**](https://www.acwing.com/problem/content/148/)

将问题进行分解，首先研究前两个序列，得到一个长度为 n 的序列，接下来再进行合并。


<br/>


[**147. 数据备份 - AcWing题库**](https://www.acwing.com/problem/content/149/)

两个配对的办公楼是相邻的，将问题换化为从一个序列中，选出不超过 k 个数，且不能相邻，是他们的和最小。

关键点在于—— ** 要么选 $D_i$ ，要么同时选中 $D_{i-1}$ 和 $D_{i+1}$  ** ，究竟是选中间还是两边，可以先尝试选中中间，将两边剔除，然后 加入新节点 $D_{i-1}+D_{i+1}-D_i$ 。在实现算法时，难点在于如何维护节点的关系，可以使用**下标模拟链表** 。
```cpp
vector<LL> a;
struct cmp
{
	bool operator()(int x, int y)
	{
		return a[x] > a[y];
	}
};

void solve()
{
	int n, k;
	cin >> n >> k;
	a.assign(n + 1, 0);
	cin >> a[1];
	for (int i = 2; i <= n; ++i)
	{
		cin >> a[i];
		a[i - 1] = a[i] - a[i - 1];
	}

	priority_queue<int, vector<int>, cmp> que;

	vector<int> pre(n + 1), nxt(n + 1);
	vector<bool> del(n + 1);
	for (int i = 1; i <= n - 1; ++i)
	{
		pre[i] = i - 1;
		nxt[i] = i + 1;
		que.push(i);
	}

	LL ans = 0;
	for (int i = 0; i < k; ++i)
	{
		int x = que.top();
		que.pop();
		while (del[x])
		{
			x = que.top();
			que.pop();
		}
		ans += a[x];
		del[pre[x]] = true;
		del[nxt[x]] = true;
		if (pre[x] >= 1 && nxt[x] <= n - 1)
		{
			a[x] = a[pre[x]] + a[nxt[x]] - a[x];
			que.push(x);
			pre[x] = pre[pre[x]];
			nxt[x] = nxt[nxt[x]];
			nxt[pre[x]] = x;
			pre[nxt[x]] = x;
		}
		else
		{
			del[x] = true;
			if (pre[x] >= 1)
				nxt[pre[pre[x]]] = n;
			else if (nxt[x] <= n - 1)
				pre[nxt[nxt[x]]] = 0;

		}
	}
	cout << ans;
}
```

---

<br/>


<br/>


<br/>



## Huffman 树

引入问题：给定一颗包含了 n 个叶子节点的 **k 叉树**，其中第 i 个叶子节点带有权值 $w_i$ ，要求最小化 $\sum{w_i\times l_i}$ ，问题的解称为 **k 叉 Huffman 树**。

为了最小化  $\sum{w_i\times l_i}$ ，应该让权值大的节点深度尽可能小，也就是权值小的节点深度尽可能深，对于二叉霍夫曼树：
- 建立小根堆，存储节点权值。
- 从堆中取出权值最小的两个 $w_1$ 和 $w_2$ ，`ans+=w1+w2`。
- 新建一个权值为 $w_1+w_2$ 的节点，加入堆中。
- 重复以上步骤，直到堆中节点数为 1。

**对于 k（k>2）叉霍夫曼树**，这样显然不是最优解，**应该额外添加一些权值为 0 的节点，使得叶子节点总数 n 满足—— $(n-1)\%(k-1)==0$ ** 。

### 相关题目

[**148. 合并果子 - AcWing题库**](https://www.acwing.com/problem/content/150/)

<br/>

[**149. 荷马史诗 - AcWing题库**](https://www.acwing.com/problem/content/151/)

k 叉霍夫曼树，由于要求树的深度最小化，所以**优先合并深度小的节点**。

---