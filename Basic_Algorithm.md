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

可以通过递推方式得出的基本信息，是一种重要的预处理方式。

**一维前缀和**
一般设置一个开头，便于处理边界问题，下标从 1 开始。

**二维前缀和**
一维的拓展，计算公式稍有不同。

---

## 差分

差分是前缀和运算的逆运算。一般而言 $d[i]=a[i]-a[i-1]$ ，但是差分数组如何构造并不重要，要求差分数组进行前缀和运算能够得到原数组即可。

在差分数组进行标记，可以实现对原数组某一段区间的全体元素加一个数，或减去一个数。

#### 相关题目

[100. 增减序列 - AcWing题库](https://www.acwing.com/problem/content/102/)




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



---