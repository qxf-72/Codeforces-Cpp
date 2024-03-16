# 位运算

灵茶山艾府 [位运算的技巧汇总](https://leetcode.cn/circle/discuss/CaOJ45/)

## lowbit 运算
取出一个数二进制表示形式的最低位的 1 以及之后的位，所表示的数。主要用于树状数组中下标的计算。

```cpp
int lowbit(int x)
{
	return x&-x;
}
```

> GCC 编译器提供了一些位运算的**内建函数**，这些函数并非 C 或 C++语言标准，需**谨慎使用**。下面的内建函数中以 ll 结尾的表示处理 unsigned long long ，否则表示处理 int ：
> 
> - `__builtin_ctz ( ),__buitlin_ctzll ( )`：二进制表示形式中末尾 0 的个数。
> - `__builtin_clz( ),__builtin_clzll( )`：二进制表示形式中前导 0 的个数。
> - `__builtin_popcount( ),__builtin_popcountlll( )`：二进制表示形式中 1 的个数。

---

## 快速幂运算
在常数时间内，计算出来 $base^{p}$ ，通常用于需要取余的场景。

需要注意**将基数 base 和返回值 ret 的类型设置为 long long** ，避免在乘法运算过程中溢出造成结果错误。
```cpp
int fast_power(long long base, long long power)  
{  
    long long ret = 1;  
    for (; power; power >>= 1)  
    {  
       if (power & 1)  
          ret = (ret * base) % mod;  
       base = (base * base) % mod;  
    }  
    return ret;  
}
```



---


<br/>


<br/>



# 前缀和 与 差分

## 前缀和

前缀和是一种重要的预处理方式，能大大降低查询的时间复杂度。

C++ 标准库中实现了前缀和函数 [`std::partial_sum`](https://zh.cppreference.com/w/cpp/algorithm/partial_sum)，定义于头文件 `<numeric>` 中。


**一维前缀和**
一般设置一个开头，便于处理边界问题，下标从 1 开始。

**二维前缀和**
多维前缀和的普通求解方法几乎都是基于容斥原理。

---

## 差分

差分是前缀和运算的逆运算。一般而言 $d[i]=a[i]-a[i-1]$ ，但是差分数组如何构造并不重要，要求差分数组进行前缀和运算能够得到原数组即可。

在差分数组进行标记，可以实现对原数组某一段区间的全体元素加一个数，或减去一个数。

#### 相关题目

[100. 增减序列 - AcWing题库](https://www.acwing.com/problem/content/102/)

---


<br/>


<br/>


# 高精度运算

由于 C++没有大数类，所以需要自己手写实现大数类。


[**BigInt.cpp**](/copypasta/Basic_Algorithm/BigInt.cpp)
只能用于**正数**，并且乘除的对象是普通类型。


---


<br/>


<br/>




# 二分

判定难度小于求解，当问题答案具有某种单调性时，通过二分法把问题求解转化为判定。

## 整数二分
  

---


<br/>


<br/>



# 排序

排序作为最基础的算法，可以引申出很多相关的应用。

## 离散化

当数的取值范围很大，但是数的个数有限时，可以进行离散化操作，进行排序之后去重，然后用下标代替这个数，查找某个数对应的下标，使用二分查找即可。

#### 相关题目

[103. 电影 - AcWing题库](https://www.acwing.com/problem/content/105/) ——本题使用哈希表也可以。

---

## 中位数

求中位数需要用到排序，或排序引申出的算法——快速选择。

**中位数的性质**

对一个序列 $a_0,a_1,a_{n-1}$ ，求 $sum(|a_i-a_k|)$ 的最小值。 $a_k$ 为序列的中位数，可以得到答案。

**动态中位数**

使用两个对顶堆，分别维护左半边和右半边，当两个堆数量不平均时，进行调整。

```cpp
priority_queue<int> l;//大根堆  
priority_queue<int, vector<int>, greater<>> r;//小根堆  
// 动态插入，动态查询
for (int i = 1; i <= m; ++i)  
{  
    int a;   cin >> a;  
    r.push(a);  // 一律插入小根堆，保证中位数在小根堆中，之后再进行调整
    if (!l.empty() && l.top() > r.top())  
    {  
       int x = l.top(), y = r.top();  
       l.pop(), r.pop();  
       l.push(y), r.push(x);  
    }  
    if (r.size() > l.size() + 1)  
    {  
       int x = r.top();  
       r.pop();  
       l.push(x);  
    }  
}
```



#### 相关题目

[104. 货仓选址 - AcWing题库](https://www.acwing.com/problem/content/106/) ——中位数性质

[105. 七夕祭 - AcWing题库](https://www.acwing.com/problem/content/107/) ——**均分纸牌**、**环形纸牌**、中位数性质

[106. 动态中位数 - AcWing题库](https://www.acwing.com/problem/content/108/) ——动态中位数

---

## 快速选择

快速排序模板
```cpp
void quick_sort(vector<int>& a, int left, int right)
{
	if (left >= right)
		return;
	int l = left - 1, r = right + 1, x = a[(left+right)/2];
	while (l < r)
	{
		do ++l; while (a[l] < x);
		do --r; while (a[r] > x);
		if (l < r) swap(a[l], a[r]);
	}
	quick_sort(a, left, r);
	quick_sort(a, r + 1, right);
}
```


从快速排序算法中引申出快速选择算法，可以在 $O(n)$ 时间复杂度选择，选出序列第 k 个数（从小到大）。

```cpp
int quick_select(vector<int>& a, int left, int right, int k)
{
	if (left == right)
		return a[left];
	int l = left - 1, r = right + 1, x = a[(left + right) >> 1];
	while (l < r)
	{
		do ++l; while (a[l] < x);
		do --r; while (a[r] > x);
		if (l < r) swap(a[l], a[r]);
	}
	int num = r - left + 1;
	if (k <= num)
		return quick_select(a, left, r, k);
	else
		return quick_select(a, r + 1, right, k - num);
}
```


#### 相关题目

[LCR 076. 数组中的第 K 个最大元素 - 力扣（LeetCode）](https://leetcode.cn/problems/xx4gT2/description/) ——快速选择

---


## 逆序对

在一个序列中，如果 $i<j$ ，且 $a[i]>a[j]$ ，那么 $a[i],a[j]$ 构成序列中一个逆序对。

可以使用归并排序的方式求逆序对。另外逆序对数等于冒泡排序的总交换次数。

```cpp
ll merge_sort(vector<int>& a, int l, int r)
{
	if (l == r)
		return 0;
	int mid = (l + r) >> 1;
	ll ans = 0;
	ans += merge_sort(a, l, mid);
	ans += merge_sort(a, mid + 1, r);

	int k = 0, i = l, j = mid + 1;
	for (; i <= mid && j <= r;)
	{
		if (a[i] <= a[j])
			tmp[k++] = a[i++];
		else
		{
			tmp[k++] = a[j++];
			ans += mid - i + 1; // 每一步只考虑 以a[j]为右边能构成的逆序对数
		}
	}
	while (i <= mid)
		tmp[k++] = a[i++];

	while (j <= r) tmp[k++] = a[j++];
	for (k = 0; k < r - l + 1; ++k)
		a[l + k] = tmp[k];
	return ans;
}
```

#### 相关题目

[107. 超快速排序 - AcWing题库](https://www.acwing.com/problem/content/109/) ——逆序对

[108. 奇数码问题 - AcWing题库](https://www.acwing.com/problem/content/110/) ——利用逆序对求解**奇数码问题**

---


<br/>


<br/>


# 倍增 

## 倍增算法

倍增（Binary Lifting），即成倍增长。当状态空间很大时，线性扫描效率太低，可以使用倍增，每一次前进的幅度成倍增长。

- 假设当前左端点为 $l$ ，需要知道符合要求的最大的右端点 $r$ 
- 初始有， $r=l,p=1$
	- 当区间 $[l,r+p-1]$ 符合要求时， $r+=p \  , \ p*=2$
	- 否则 $p/=2$
- 当 $p$ 为 0 时，即找到右端点。

在可以使用倍增算法的地方，其实也可以使用二分法；当时，如果当答案很靠近左端点时，二分法的效率很低，甚至不如线性扫描。


#### 相关题目

[109. 天才ACM - AcWing题库](https://www.acwing.com/problem/content/111/) ——倍增、归并优化

---

## ST 算法

ST 表（Sparse Table）稀疏表，是基于倍增思想，在 RMQ 问题的产物。给定一个长度为 N 的序列，ST 算法在经过 **N*logN 时间的预处理**之后，以 **O (1) 复杂度在线查询**某个区间的信息，比如区间最大值。

ST 表能维护的区间信息必须是**可重复贡献**的信息：
- 最大值
- 区间 按位和
- 区间 按位或
- 区间 GCD

[**SparseTable. cpp**](/copypasta/Basic_Algorithm/SparseTable.cpp)
该模板使用了 template，根据数据类型设置 T，同时根据题目设置操作类型 op，op 为 `function<T(const T&,const T&)>` 类型。

---


<br/>


<br/>


# 贪心

贪心是一种每次决策是采取当前的最优解（局部最优解），因此贪心问题的整体最优性可以由局部最优性导出。常见的证明手段：
- 微扰：交换邻项，证明对局部最优解的任何改动都会造成整体结果变差。
- 反证法
- 数学归纳法


#### 相关题目

[1055. 股票买卖 II - AcWing题库](https://www.acwing.com/problem/content/1057/)

[110. 防晒 - AcWing题库](https://www.acwing.com/problem/content/112/)

[111. 畜栏预定 - AcWing题库](https://www.acwing.com/problem/content/113/)

[112. 雷达设备 - AcWing题库](https://www.acwing.com/problem/content/114/) 
和一维的情况有区别，不能线性的扫描 (对于左端点，要求 y 从大到小排列，但是已经确定雷达位置，来跳过雷达的覆盖范围时，要求 y 从小到大排列。)
对于每一个小岛，确定一段雷达能够放置的区间，对于所有区间，有重叠部分，可以合并，问题转化为——将重叠的区间合并之后，有多少个独立的区间。

[114. 国王游戏 - AcWing题库](https://www.acwing.com/problem/content/116/)
本题使用**微扰法**解决。对于两个相邻的大臣 $i$ 和 $i+1$ ，他们获得奖励：

$$
\frac{1}{B\left[ i \right]}\times \prod_{j=0}^{i-1}{A\left[ j \right]}\ ,\ \frac{1}{B\left[ i+1 \right]}\times \prod_{j=0}^i{A\left[ j \right]}
$$

将两个大臣的顺序交换，他们获得的奖励变为：

$$
\frac{1}{B\left[ i+1 \right]}\times \prod_{j=0}^{i-1}{A\left[ j \right]}\ ,\ \frac{1}{B\left[ i \right]}\times \prod_{j=0}^i{A\left[ j \right]}
$$

去除公因子之后，只需要比较以下两个式子：

$$
\max \left( \frac{1}{B\left[ i \right]},\frac{A\left[ i \right]}{B\left[ i+1 \right]} \right) \ \ \ \max \left( \frac{1}{B\left[ i+1 \right]},\frac{A\left[ i+1 \right]}{B\left[ i \right]} \right) 
$$

如果想要交换操作有意义，必须证明上左式大于等于右式，即

$$
\frac{A\left[ i \right]}{B\left[ i+1 \right]}\ge \frac{A\left[ i+1 \right]}{B\left[ i \right]}\ \rightarrow \ A\left[ i \right] \times B\left[ i \right] \ \ge \ A\left[ i+1 \right] \times B\left[ i+1 \right] 
$$

所以可以按照 ab 乘积从小到大排序，得到最优顺序。另外，需要实现**高精度**。


[115. 给树染色 - AcWing题库](https://www.acwing.com/problem/content/117/)
困难题，[题解链接]((https://www.acwing.com/solution/content/1065/))

---