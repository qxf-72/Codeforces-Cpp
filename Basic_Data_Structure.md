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

[41. 包含min函数的栈 - AcWing题库](https://www.acwing.com/problem/content/90/)


---


## 出栈序列问题

n 个数字依次进栈，进栈之后可以随时出栈，问有多少种出栈序列。

当不仅仅求序列数量，还需列出序列时，使用 dfs 进行搜索，每一次可以选择将数字入栈，或者将栈顶数字出栈，复杂度 O (2^N)。

如果仅仅序列的数量，等价于求 第 N 项 **Catalan 数**

$$
\frac{C_{2n}^{n}}{n+1}
$$

当 N 很大时，需要结合高精度运算，因为是求组合数，并且不存在分母有质因数 k 而分子没有的情况，所以将卡塔兰数进行质因数分解，然后再计算。


### 相关题目

[130. 火车进出栈问题 - AcWing题库](https://www.acwing.com/problem/content/132/)
结合**压位高精度**求解和质因数分解求卡塔兰数。

---

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
- 遇到右括号，不断取栈顶出栈，知道遇到左括号
- 遇到运算符，只要栈顶运算符优先级**大于等于**新运算符（左括号优先级最低，其余按运算优先级排列），不断取栈顶出栈（优先级高的先出栈计算），然后新运算符入栈

---

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

[131. 直方图中最大的矩形 - AcWing题库](https://www.acwing.com/problem/content/133/)
使用贡献法求解，对于每个元素，求出上一个和下一个 更小元素的 index，得出该元素的作用范围，更新答案。


---


<br/>


<br/>


<br/>


<br/>



# 队列

队列是一种"先进先出"的线性数据结构，为了节省开头空间， 一般将其实现为**循环队列**。C++STL 中有队列的实现 `queue` 和 `deque`。


## 单调队列

给出一个长度为 n 的数组，输出每 k 个连续的数中的最大值、最小值。

以求最大值为例，单调队列维护信息的本质是，一个元素入队时将队内比他小的元素踢出（被踢出元素必然不是当前维护区间的最大值）。

算法步骤：
- 如果当前元素的值 > 队尾元素， **队尾出队**，直到队尾 > 当前元素。然后将当前元素入队。
- 判断队头元素是否超出范围，如果超出就**队头出队**。
- 此时队头就是答案。

根据题目情况，第一步和第二步的执行顺序可能会调换。


### 相关题目

[135. 最大子序和 - AcWing题库](https://www.acwing.com/problem/content/137/)

---


<br/>


<br/>


<br/>


<br/>




# 链表

链表和二叉树主要是在工作面试中考察。下面讨论 C++STL 中链表的使用，和一些相关算法。

## list 和 forward_list

list 是双向链表。forward_list 为单链表，forward_list 不提供 size 操作，效率接近手写的链表，此外，forward_list 的插入操作与其他容器很不一样，是在指定位置之后插入。

---

## Floyd 判圈算法

> **Floyd判圈算法**(Floyd Cycle Detection Algorithm)，又称**龟兔赛跑算法**(Tortoise and Hare Algorithm)，是一个可以在有限状态机、迭代函数或者链表上判断是否存在环，求出该环的起点与长度的算法。该算法据高德纳称由美国科学家罗伯特-弗洛伊德发明。

该算法可以在不使用常量空间的情况下，使用线性的时间来判断链表是否存在环。主要依赖快慢指针。fast 指针一次走两步，slow 指针一次走一步，如果存在环，两者必定会相遇。

如何**求环的起点**呢？假设慢指针走了 x 步，则快指针走了 2 x 步，设非环部分长度为 a，环长度为 b，可得：

$$
2x-x=kb,即 \ \ x=kb
$$

所以慢指针在环中走了 $kx-a$ 步，如果**再走 $k$ 步**，就是 $(k+1)b$ 步，此时位于**环的起点**。只需要增加一个指针 p 指向头部，和 slow 指针一起移动直到相遇即可。

### 相关题目 

[141. 环形链表](https://leetcode.cn/problems/linked-list-cycle/)

[142. 环形链表 II](https://leetcode.cn/problems/linked-list-cycle-ii/)

---


<br/>


<br/>


<br/>


<br/>


# Hash

## Hash 表

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


### 相关题目

[137. 雪花雪花雪花 - AcWing题库](https://www.acwing.com/problem/content/139/)

---


## 字符串 Hash

将一个任意长度的字符串映射为非负整数，冲突概率几乎为 0。具体做法——将字符串看作是一个 P 进制数，求出这个数，然后对 M 取余。
- P 通常取 **131** 或 **13331**。
- M 通常取 $2^{64}$ ，直接使用 **unsigned long long** 存储这个数，高位自动对齐，不用取余操作。

除了特殊构造的字符串，该哈希很难产生冲突。为了将冲突的可能性再次降低，可以多取几个不同的 P 和 M，结果都相同时，才认为字符串相等。

字符串 Hash 的主要用处是——进过 O (N) 时间预处理后，可以 **以 O(1) 时间查询任意子字符串的哈希值**。
- $H(S+c)=(H(S)*P+value(c))\  \% \  M$
- $H(T)=(H(S+T)-H(S)^{len(T)}) \  \%  \ M$

为了降低计算复杂度，P 的次方也可以预处理保存到一个数组里面。

### 模板代码

[**StringHash.cpp**](/copypasta/Basic_Data_Structure/StringHash.cpp) 模板类在初始化时，可以设置 P，方便进行**双哈希**验证。默认 s 下标从 0 开始，并且只有小写字母，默认 query 下标从 1 开始。


### 相关题目

[138. 兔子与兔子 - AcWing题库](https://www.acwing.com/problem/content/140/)

[139. 回文子串的最大长度 - AcWing题库](https://www.acwing.com/problem/content/141/)

---


<br/>


<br/>


<br/>


<br/>


# 字符串

主要介绍有关字符串的算法。

## KMP

**字符串模式匹配问题**——判定 A 是否为 B 的字串，并求出 A 在 B 各次出现的位置。

使用字符串 hash 也可以在线性时间内求解。使用 KMP 算法求解更高效，并且可以提供一些额外的信息。KMP 关键在于减少模式串的回退步数，需要维护一个 **next 数组**—— `next[i]` 表示  **以 A[i]结尾的非前缀子串  与  A 的前缀能够匹配的最大长度**。

```cpp
next[1]=0; 
// j代表匹配的长度
for(int i=2,j=0;i<=n;++i){
	while(j>0 && a[i]!=a[j+1]) 
		j=next[j];
	if(a[i]==a[j+1]) ++j;
	next[i]=j;
}
```


维护一个数组 f，`f[i]` 表示——**B 中以 i 结尾的子串  与  A 的前缀能够匹配的最长长度**。

```cpp
for(int i=1,j=0;i<=m;++i){
    while(j>0 && (j==n || b[i]!=a[j+1]))
        j = next[j];
    if(b[i]==a[j+1]) 
        ++j;
    f[i]=j;
    // if(j==n) 说明A在B出现 
}
```


### 相关题目

[141. 周期 - AcWing题库](https://www.acwing.com/problem/content/143/) KMP 算法 next 数组的应用——**最小循环元**

---


## 最小表示法

给定一个字符串 S[1-n] ，如果不断把最后一个字符放在开头，可以得到 n 个字符串——称这 n 个字符串是**循环同构**的。其中字典序最小的字符串成为 S 的**最小表示法**。

要求字符串 S 的最小表示法，朴素的做法是一个一个进行比较，时间复杂度是 O (N^2)。

存在时间复杂度 O (N)的做法——将两个 S 拼接到一起，形成字符串 SS。设$B[i] = SS[i~i+n-1]$ ，可以设 i=1，j=2，从头开始比较，如果字符相等则继续比较下一位，当字符不相等时，**假设 $SS[i+k] > SS[j+k]$，则 $B[i] 、B[i+1]、...、B[i+k]$都不可能是最小表示法**，因为存在对应的   $B[j] 、B[j+1]、...、B[j+k]$比他小。

**算法流程**
-  初始令 $i=1，j=2$
- 从前往后进行扫描，比较 $B[i]$和 $B[j]$ ：
	- 如果扫描了 n 个字符都相等，说明 S 只由一个字符构成。
	- 如果 $SS[i+k] > SS[j+k]$，令 $i=i+k+1$，如果 $i=j$，则$++i$。
	- 如果 $SS[i+k] < SS[j+k]$，令 $j=j+k+1$，如果 $i=j$，则$++j$。
- 最后如果 $i>n$，则 $B[j]$是最小表示法；否则 $B[i]$ 是最小表示法。

```cpp
int n = strlen(s+1)
// 构造SS
for(int i = 1 ; i <= n; ++i)
	s[i+n] = s[i];
int i,j ,k ;
for(i = 1 , j = 2, k ; i <= n && j <= n  ; ){
	for(int k = 0 ; k <= n&&s[i+k]==s[j+k];++k);
	if(k==n)
		break; // S只由一种字符构成
	if(s[i+k]>s[j+k]){
		i=i+k+1;
		if(i==j) ++i;
	}else{
		j=j+k+1;
		if(j==i) ++j;
	}
}
ans=min(i,j); //B[ans]是最小表示法
```


---


<br/>


<br/>


<br/>


<br/>


# 前缀树 Tire

Tire 的本质，就是利用字符串之间的公共前缀，将重复的前缀合并在一起。

树中存储着一些单词的所有字母，每个节点代表一个字母，其中可以另外保存一些状态，比如是否有单词以该字母为结尾。可用于高效判断一个字符串是否存在于一组字符串集合中，或者作为字符串集合中某个字符串的前缀。

### 模板代码

[**Tire.cpp**](/copypasta/Basic_Data_Structure/Tire.cpp)

Tire 类是典型的前缀树，实现的功能：判断字符串集合中是否存在一个字符串，prefix 是否是字符串集中某个字符串的前缀，统计字符串集合中有多少个字符串是 str 的前缀。

Tire_Xor 类是前缀树的拓展应用，将 32 位整数集合存入树中。


### 相关题目


[142. 前缀统计 - AcWing题库](https://www.acwing.com/problem/content/description/144/)

[143. 最大异或对 - AcWing题库](https://www.acwing.com/problem/content/145/) Tire 的拓展应用。

[144. 最长异或值路径 - AcWing题库](https://www.acwing.com/problem/content/146/) 可以转化为**最大异或对**问题求解。

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

[145. 超市 - AcWing题库](https://www.acwing.com/problem/content/147/) 
对于每个时间 t，应该在保证不卖出过期商品的同时，尽量卖出前 t 大的商品。把商品按照过期时间排序，从头扫描每个商品，查看在该日期前最大能买多少利润，使用小根堆进行维护。同时也可以按利润降序排序，优先选择利润高的商品，然后剔除一个在过期日期之前的时间，可以使用并查集优化。

[146. 序列 - AcWing题库](https://www.acwing.com/problem/content/148/)
将问题进行分解，首先研究前两个序列，得到一个长度为 n 的序列，接下来再进行合并。

[147. 数据备份 - AcWing题库](https://www.acwing.com/problem/content/149/)
两个配对的办公楼是相邻的，讲问题换化为从一个序列中，选出不超过 k 个数，且不能相邻，是他们的和最小。关键点在于—— ** 要么选 $D_i$ ，要么同时选中 $D_{i-1}$ 和 $D_{i+1}$  ** ，究竟是选中间还是两边，可以先尝试选中中间，将两边剔除，然后 加入新节点 $D_{i-1}+D_{i+1}-D_i$ 。在实现算法时，难点在于如何维护节点的关系，可以使用下标模拟链表。
```cpp
vector<LL> a;
struct cmp
{
    bool operator()(int x,int y)
    {
        return a[x]>a[y];
    }
};

void solve()
{
    int n, k;
    cin >> n >> k;
    a.assign(n+1,0);
    cin>>a[1];
    for (int i = 2; i <= n; ++i)
    {
        cin>>a[i];
        a[i-1]=a[i]-a[i-1];
    }

    priority_queue<int,vector<int>,cmp> que;

    vector<int> pre(n+1),nxt(n+1);
    vector<bool> del(n+1);
    for(int i=1; i<=n-1; ++i)
    {
        pre[i]=i-1;
        nxt[i]=i+1;
        que.push(i);
    }

    LL ans=0;
    for(int i=0; i<k; ++i)
    {
        int x=que.top();
        que.pop();
        while (del[x])
        {
            x=que.top();
            que.pop();
        }
        ans+=a[x];
        del[pre[x]]=true;
        del[nxt[x]]=true;
        if(pre[x]>=1&&nxt[x]<=n-1)
        {
            a[x]=a[pre[x]]+a[nxt[x]]-a[x];
            que.push(x);
            pre[x]=pre[pre[x]];
            nxt[x]=nxt[nxt[x]];
            nxt[pre[x]]=x;
            pre[nxt[x]]=x;
        }
        else
        {
            del[x]=true;
            if(pre[x]>=1)
                nxt[pre[pre[x]]]=n;
            else if(nxt[x]<=n-1)
                pre[nxt[nxt[x]]]=0;

        }
    }
    cout<<ans;
}
```

---

## Huffman 树

引入问题：给定一颗包含了 n 个叶子节点的 **k 叉树**，其中第 i 个叶子节点带有权值 $w_i$ ，要求最小化 $\sum{w_i\times l_i}$ ，问题的解称为 **k 叉 Huffman 树**。

为了最小化  $\sum{w_i\times l_i}$ ，应该让权值大的节点深度尽可能小，也就是权值小的节点深度尽可能深，对于二叉霍夫曼树：
- 建立小根堆，存储节点权值。
- 从堆中取出权值最小的两个 $w_1$ 和 $w_2$ ，`ans+=w1+w2`。
- 新建一个权值为 $w_1+w_2$ 的节点，加入堆中。
- 重复以上步骤，直到堆中节点数为 1。

对于 k（k>2）霍夫曼树，这样显然不是最优解，**应该额外添加一些权值为 0 的节点，使得叶子节点总数 n 满足—— $(n-1)\%(k-1)==0$** 。

### 相关题目

[148. 合并果子 - AcWing题库](https://www.acwing.com/problem/content/150/)

[149. 荷马史诗 - AcWing题库](https://www.acwing.com/problem/content/151/)
k 叉霍夫曼树，由于要求树的深度最小化，所以**优先合并深度小的节点**。

---