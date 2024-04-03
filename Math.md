# 质数

在整个自然数集合中，质数分布比较稀疏，对于一个足够大的数 N ，不超过 N 的质数大约有 $\frac{N}{\ln\text{\ }N}$ 个。

## 质数判定

对于**单个质数的判定**，使用**试除法**。扫描所有 $[2,\sqrt N]$ 中的整数，以此检验其是否能够整除 N 。
```cpp
bool is_prime(int n)
{
	for(int i=2;i<=sqrt(n);++i)
		if(n%i==0)
			return false;
	return true; 
}
```

此外存在效率更高的随机性算法——Miller-Robbin 算法。

---

## 质数筛选

### 埃氏筛

埃氏筛法时间复杂度为 $O(N\times log(log N))$ ，效率接近于线性。

```cpp
vector<int> primes;
void get_prime(int n)
{
	vector<bool> v(n+1);
	for(int i = 2 ; i <= n ; ++i){
		if(v[i])
			continue;
		primes.push_back(i);
		for(int j = 2*i; j <= n; j+=i )
			v[j] = true;
	}	
}
```

### 线性筛

埃氏筛效率不是线性的根本原因在在于重复标记合数，例如 12 既被 2 标记，又被 3 标记。由此可以思考出线性筛算法——唯一确定合数的组成方式。**让每个合数仅仅被其最小质因数标记一次**。


```cpp
const int MAX_N = 1'000;
int v[MAX_N];        // 记录每个合数的最小质因数
int prime[MAX_N];    // 记录筛出的质数
int m;        // 质数数量
void get_prime(int n)
{
	memset(v, 0, sizeof v);
	m = 0;
	for (int i = 2; i <= n; ++i)
	{
		if (v[i] == 0)
		{
			v[i] = i;    // 质数的最小质因数是其本身
			prime[++m] = i;
		}
		for (int j = 1; j <= m; ++j)
		{
			// 如果 prime[j] > v[i] ，则说明 i*prime[j] 的最小质因数是v[i]，而不是prime[j]
			if (prime[j] > v[i] || i * prime[j] > n)
				break;
			v[i * prime[j]] = prime[j];
		}
	}
}
```

### 区间筛

给定一个区间 $[L,R]$ ，（ $1\le L\le R\le 2\times 10^9\ ,\ R-L\le 10^6$ ）要求出位于该区间中的所有质数，此时使用线性筛也无法在规定时间内求解。

**任何一个合数 n，必然包含一个不超过 $\sqrt N$ 的质因数**。区间筛法——先筛出所有位于 $[2,\sqrt R]$ 中的质数，然后利用这些质数标记区间 $[L,R]$ 中的合数。时间复杂度为 $O(\sqrt R log(log \sqrt R) + (R-L)log(log (R-L)))$ 。
 
---

## 质因数分解

**算术基本定理**

任何一个大于 1 的整数都能被唯一分解成有限个质数的乘积，可以写作 $N=p_1^{c_1}\times p_2^{c_2}\times ... p_m^{c_m}$


**试除法**

从 2（最小的质数）开始试除，直到 `i*i>n`。分解结束之后，如果 余数大于 1，说明 n 有大于 $\sqrt{n}$ 的因数（并且是唯一的）。

```cpp
unordered_map<int, int> prime_fac;  
void divide(int n)  
{  
    for (int i = 2; i * i <= n; ++i)  
    {  
       while (n % i == 0)  
       {  
          ++prime_fac[i];  
          n /= i;  
       }  
    }  
    if (n > 1)  
       ++prime_fac[n];  
}
```


---


<br/>


<br/>


<br/>


<br/>


# 约数

如果整数 n 除以整数 d 的余数为 0，则称 d 能整除 n，记为 $d|n$ 。


## 正约数集合

**算术基本定理推论**

任何一个大于 1 的整数 N 都能被唯一分解成 $p_1^{c_1}\times p_2^{c_2}\times ... p_m^{c_m}$ ，N 的**正约数集合**可以写作

$$
p_1^{b_1}\times p_2^{b_2}\times ... p_m^{b_m}\  , \ 1\le b_i\le c_i
$$

对于每个 $p_i$ 都有 $p^0,p,p^2,...,p^c_i$ 一共 $c_i+1$ 种选择，则 N 的 **正约数个数**为：

$$
\left( c_1+1 \right) \times \left( c_2+1 \right) \times ...\times \left( c_m+1 \right) =\prod_{i=1}^m{\left( c_i+1 \right)}
$$

N **所有正约数的和**为：

$$
\left( 1+p_1+p_{1}^{2}+...+p_{1}^{c_1} \right) \times \left( 1+p_2+p_{2}^{2}+...+p_{2}^{c_2} \right) \times \left( 1+p_m+p_{m}^{2}+...+p_{m}^{c_m} \right) 
$$


### 试除法

对于 N，除了 $\sqrt N$ ，其余约数总是成对出现的。

```cpp
int factor[1000], m = 0;  
void get_factor(int n)  
{  
    for (int i = 1; i * i <= n; ++i)  
    {  
       if (n % i == 0)  
       {  
          factor[++m] = i;  
          if (i * i != n) factor[++m] = n / i;  
       }  
    }  
}
```

### 倍数法

当需要**求 1 到 N 每个数的正约数集合**时，若采用试除法，时间复杂度过高。

可以反过来考虑，1 到 N 中，以 d 为余数的数就是 d 的倍数：

```cpp
vector<int> factor[10000];  
void get_factor(int n)  
{  
    for (int i = 1; i <= n; ++i)  
       for (int j = 1; j * i <= n; ++j)  
          factor[i * j].push_back(i);  
}
```

上述算法的时间复杂度为 $O(N+\frac{N}{2}+\frac{N}{3}+...+\frac{N}{N}=N\log N)$

由此可以推出，**1 到 N 每个数的约数个数总和大约为 $NlogN$ 个**。


### 例题

[198. 反素数 - AcWing题库](https://www.acwing.com/problem/content/200/) ——**反质数**

根据反质数的定义，可以推出几条反质数的性质：
- 1 到 N 中最大的反质数是，1 到 N 中约数最多的数中最小的一个。
- 根据 N 的范围（ $1\le N\le 2\times 10^9$ ），可推出——
	- **1 到 N 中任何一个数的不同质因子不会超过 10 个**（ $2\times 3\times 5\times 7\times 11\times 13\times 17\times 19\times 23\times 29\times 31\ >\ 2\times 10^9$ ）
	- 所有质因子指数总和不会超过 30（ $2^{31}>2\times 10^9$ ）
- $x$ 成为反质数的必要条件是—— $x$ 分解质因数后可以写作

$$
2^{c_1}\times 3^{c_2}\times 5^{c_3}\times ...\times 29^{c_{10}}\ ,\ c_1\ge c_2\ge ...\ge c_{10}
$$

最后一条性质很好证明，如果存在 $c_i<c_{i+1}$ ，可以将两个指数位置互换得到一个约数数量一样，但是更小的数。


[199. 余数之和 - AcWing题库](https://www.acwing.com/problem/content/201/)

对于 $n$ 和 $k$ ，需要求 $k\ mod\ 1+k\ mod\ 2+k\ mod\ 3+...+k\ mod\ n$ ，可以转化为求 $n\times k-\sum_{i=1}^n{\lfloor \frac{k}{i} \rfloor \times i}$ ，对于 $\lfloor \frac{k}{i} \rfloor$ 很不好处理，如果一项一项求显然会超时。

观察函数 $y=\lfloor \frac{k}{x} \rfloor$ 规律，由于向下取整，函数的图像必然是由一段段横线构成，即 $y$ 在 $x$ 属于某个区间是不变的，可以将个区间的运算合并从而降低复杂度。

假设当前位于 $i$ ，函数值恒等于 $\lfloor \frac{k}{i} \rfloor$ 的 $x$ 区间右端点为 $\frac{k}{\lfloor \frac{k}{i} \rfloor}$ ，由于我们的运算对象是整数，所以需要取整，并且是向下取整。
```cpp
void solve()  
{  
    LL n, k;  
    cin >> n >> k;  
    LL l, r;  
    LL ans = n * k;  
    for (l = 1; l <= n; l = r + 1)  
    {  
       LL t = k / l;  
       if (t == 0)  
          break;  
       r = min(n, k / t);  
       ans -= t * (r + l) * (r - l + 1) / 2;  
    }  
    cout << ans;  
}
```

---


## 最大公约数
  
C++17 提供了两个模板函数求最小公倍数和最大公约数—— `gcd` 和 `lcm`

**定理**

$$
\forall a,b\in N\ ,\ \ gcd\left( a,b \right) *lcm\left( a,b \right) =a*b
$$

设 $d=gcd(a,b)$ ， $a_0=a/d,b_0=b/d$ ，则 $lcm(a,b)=a_0\times b_0$ 。


### 更相减损术

$$
\forall a,b\in N\ ,\ a\ge b\ ,\text{则\ }gcd\left( a,b \right) =gcd\left( a,a-b \right) =gcd\left( b,a-b \right) 
$$

假设 $d=gcd(a,b)$ ，则 $d|a$ ， $d|b$ ，所以 $d|(a-b)$ 。

### 欧几里得算法

$$
\forall a,b\in N\ ,\ b !=0  ,\text{则\ }gcd\left( a,b \right) =gcd\left( b,a\ mod\ b \right) 
$$

当 $a>b$ ，命题显然成立。

当 $a\ge b$ 时，设 $a=q\times b+r$ ，显然 $r = a\ mod \ b$ ，因为 $d|a$ ， $d|q\times b$ ，所以 $d|r$ 。

因为高精度除法（取余）不容易实现，需要做高精度运算时，使用更相减损法代替欧几里得算法。



### 裴蜀定理

对于不全为零的任意整数 $a$ 和 $b$ ，记 $g=gcd⁡(a, b)$ ，则对于任意整数 $x$ 和 $y$ 都满足 $a\times x+b \times y$ 是 $g$ 的倍数，特别地，存在整数 $x$ 和 $y$ 满足 $a \times x + b \times y = g$ 。

### 例题

[1250. 检查「好数组」 - 力扣（LeetCode）](https://leetcode.cn/problems/check-if-it-is-a-good-array/description/)

从头开始遍历数组，一旦前 i 个数的最大公约数为 1，就提前跳出循环。为什么不枚举子集进行判定？因为数越多，越能使 gcd 向 1 靠近，正好符合题目要求，所以直接遍历整个数组判定。

---