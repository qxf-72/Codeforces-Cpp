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

<br/>


<br/>


<br/>


## 质数筛

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


<br/>

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


<br/>


### 区间筛

给定一个区间 $[L,R]$ ，（ $1\le L\le R\le 2\times 10^9\ ,\ R-L\le 10^6$ ）要求出位于该区间中的所有质数，此时使用线性筛也无法在规定时间内求解。

**任何一个合数 n，必然包含一个不超过 $\sqrt N$ 的质因数**。区间筛法——先筛出所有位于 $[2,\sqrt R]$ 中的质数，然后利用这些质数标记区间 $[L,R]$ 中的合数。时间复杂度为 $O(\sqrt R log(log \sqrt R) + (R-L)log(log (R-L)))$ 。
 
---


<br/>


<br/>


<br/>



## 质因数分解

### 算术基本定理

任何一个大于 1 的整数都能被唯一分解成有限个质数的乘积，可以写作 $N=p_1^{c_1}\times p_2^{c_2}\times ... p_m^{c_m}$

<br/>


### 试除法

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


算法时间复杂度为 $\sqrt N$ 。如果预处理得到质数表，时间复杂度可以降为 $\sqrt{\frac{N}{\log\text{\ }N}}$ 。

---


<br/>


<br/>


<br/>


<br/>


# 约数

如果整数 n 除以整数 d 的余数为 0，则称 d 能整除 n，记为 $d|n$ 。


## 约数集合

### 算术基本定理推论

任何一个大于 1 的整数 N 都能被唯一分解成 $p_1^{c_1}\times p_2^{c_2}\times ... p_m^{c_m}$ ，N 的**正约数集合**可以写作

$$
p_1^{b_1}\times p_2^{b_2}\times ... p_m^{b_m}\  , \ 1\le b_i\le c_i
$$

对于每个 $p_i$ 都有 $p^0,p,p^2,...,p^c_i$ 一共 $c_i+1$ 种选择，则 N 的 **正约数个数**为

$$
\left( c_1+1 \right) \times \left( c_2+1 \right) \times ...\times \left( c_m+1 \right) =\prod_{i=1}^m{\left( c_i+1 \right)}
$$

**N 所有正约数的和**

$$
\left( 1+p_1+p_{1}^{2}+...+p_{1}^{c_1} \right) \times \left( 1+p_2+p_{2}^{2}+...+p_{2}^{c_2} \right) \times \left( 1+p_m+p_{m}^{2}+...+p_{m}^{c_m} \right) 
$$


<br/>


### 试除法

对于 N，除了 $\sqrt N$ ，其余约数总是成对出现的。试除法的时间复杂度为 $O(\sqrt N)$ ，可以推出——**整数 N 的约数个数上界为 $O(2\times \sqrt N)$** 。

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

存在 **比试除法更高效的算法——预处理出 $1$ 到 $\sqrt {2\times 10^9}$ 中所有质数，然后，用 dfs 搜索组成 n 的所有约数**。



<br/>

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

[**198. 反素数 - AcWing题库**](https://www.acwing.com/problem/content/200/)

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

<br/>

[**199. 余数之和 - AcWing题库**](https://www.acwing.com/problem/content/201/)

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


从本题可以得出结论—— **<span style="background:#fff88f">$\forall i\in \left[ x,\lfloor \frac{a}{\lfloor \frac{a}{x} \rfloor} \rfloor \right]$ ，都有 $\lfloor \frac{a}{i} \rfloor$ 等于同一个值</span>**。

---

<br/>


<br/>


<br/>



## 最大公约数
  
C++17 提供了两个模板函数求最小公倍数和最大公约数—— `gcd` 和 `lcm`

**定理**

$$
\forall a,b\in N\ ,\ \ gcd\left( a,b \right) *lcm\left( a,b \right) =a*b
$$

证明：设 $d=gcd(a,b)$ ， $a_0=a/d,b_0=b/d$ ，则 $lcm(a,b)=a_0\times b_0$ 。


<br/>


### 更相减损术

$$
\forall a,b\in N\ ,\ a\ge b\ ,\text{则\ }gcd\left( a,b \right) =gcd\left( a,a-b \right) =gcd\left( b,a-b \right) 
$$

假设 $d=gcd(a,b)$ ，则 $d|a$ ， $d|b$ ，所以 $d|(a-b)$ 。


<br/>


### 欧几里得算法

$$
\forall a,b\in N\ ,\ b !=0  ,\text{则\ }gcd\left( a,b \right) =gcd\left( b,a\ mod\ b \right) 
$$

当 $a>b$ ，命题显然成立。

当 $a\ge b$ 时，设 $a=q\times b+r$ ，显然 $r = a\ mod \ b$ ，因为 $d|a$ ， $d|q\times b$ ，所以 $d|r$ 。

算法时间复杂度为 $log(min(a,b))$ 。

```cpp
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
```

因为**高精度除法（取余）不容易实现**，需要做高精度运算时，使用更相减损法代替欧几里得算法。






<br/>



### 例题

[**1250. 检查「好数组」 - 力扣（LeetCode**）](https://leetcode.cn/problems/check-if-it-is-a-good-array/description/)

从头开始遍历数组，一旦前 i 个数的最大公约数为 1，就提前跳出循环。为什么不枚举子集进行判定？因为数越多，越能使 gcd 向 1 靠近，正好符合题目要求，所以直接遍历整个数组判定。


<br/>

[**200. Hankson的趣味题 - AcWing题库**](https://www.acwing.com/problem/content/202/)

给定四个自然数 $a,b,c,d$ ，求有多少个 $x$ 满足 $gcd(a,x)=c$ 并且 $lcm(b,x)=d$ 。

**解法一**

从 $lcm(b,x)=d$ 可知， $x$ 一定是 $d$ 的约数。可以求出 $d$ 的所有约数，然后判断两个条件是否满足。虽然 $d$ 的余数的上界大约是 $\sqrt d$ ，但是**通常情况下余数数量远远达不到上界**， $10^9$ 之内的自然数约数最多的自然数仅仅有 1536 个约数。

所以可以预处理出 $1$ 到 $\sqrt {2\times 10^9}$ 中所有质数，然后，用 dfs 搜索组成 d 的所有约数。

**解法二**

$x$ 是 $d$ 的余数，所以 $x$ 的质因子一定是 $d$ 的质因子，对于 $d$ 的每一个质因子 $p$ ，计算 $x$ 可能包含多少个 $p$ 。

因为 $gcd(a,x)=c$ ，所以：
- 若 $m_a > m_c$ ，则 $m_x$ 只能等于 $m_c$
- 若 $m_a = m_c$ ，则 $m_x$ 大于等于 $m_c$
- 若 $m_a < m_c$ ，无解

同理可以根据 $lcm(b,x)=d$ 构造出不等式。综合两组条件，计算 $x$ 能含有的每个质因子的数量，使用乘法原理计算 $x$ 的个数。

---

<br/>


<br/>


<br/>


## 欧拉函数

**互质**

两个数互质，即 $gcd(a,b)=1$ ，可以推广到多个数的情况，**多个数互质 $\ne$ 两两互质**。


<br/>


### 欧拉函数

$1$ 到 $N$ 中与 $N$ 互质的数的个数称为欧拉函数，记作 $\varphi \left( N \right)$

由算术基本定理， $N=p_1^{c_1}\times p_2^{c_2}\times ... p_m^{c_m}$ ，则

$$
\varphi \left( N \right) =N\times \frac{p_1-1}{p_1}\times \frac{p_2-1}{p_2}\times ...=N\times \prod{\left( 1-\frac{1}{p} \right)}
$$

以上公式可以使用容斥原理推导出来。根据公式，只需要分解质因数就可以，求出欧拉函数

```cpp
int phi(int n) {
    int ans = n;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            ans = ans / i * (i - 1);
            while (n % i == 0)
                n /= i;
        }
    }
    if (n > 1)
        ans = ans / n * (n - 1);
    return ans;
}
```


<br/>


### 积性函数

若 $a,b$ **互质**，则 $f (ab)= f (a)\times f (b)$ 。这样的函数称为积性函数。


<br/>


### 欧拉函数与积性函数性质

- $\forall n>1$ ， $1-n$ 中与 $n$ 互质的数之和为 $n\times \varphi (n)/2$ 。

	$gcd(n,x)=gcd(n,n-x)$ ，所以与 $n$ 互质的数成对出现—— $x,n-x$ 并且平均值为 $\frac{n}{2}$ 。

- 若 $a,b$ **互质**，则 $\varphi (ab)= \varphi (a)\times \varphi (b)$ 。

	根据欧拉公式的计算式，分解质因数后，可以容易证出。

- 若 $f$ 为积性函数，在算术基本定理中 $n=\prod{p_i^{c_i}}$ ，则 $f\left( n \right) =\prod{f\left( p_i^{c_i} \right)}$ 。
- <span style="background:#fff88f">若 $p|n$ 且 $p^2|n$ ，则 $\varphi \left( n \right) =\varphi \left( \frac{n}{p} \right) \times p$ 。 **其中 $p$ 为质数**。</span>

- <span style="background:#fff88f">若 $p|n$ 且 $p^2$ 不能整除 $n$ ，则 $\varphi \left( n \right) =\varphi \left( \frac{n}{p} \right) \times (p-1)$ 。</span>
- $\sum_{d|n}{\varphi \left ( d \right)}=n$

利用埃氏筛，在 $O(N\times log(log N))$ **<span style="background:#fff88f">求出 2 到 $N$ 每个数的欧拉函数</span>**：
```cpp
void euler(int n)
{
	for (int i = 2; i <= n; ++i)
        phi[i] = i;
    for (int i = 2; i <= n; ++i) {
        if (phi[i] == i) {
            for (int j = i; j <= n; j += i) {
                phi[j] = phi[j] / i * (i - 1);
            }
        }
    }
}
```

同样的，可以利用线性筛和欧拉函数性质，**<span style="background:#fff88f">在 $O(n)$ 时间求解</span>**：

```cpp
const int N = 1e6 + 1;
int v[N];     // 记录每个数的最小质因子
int prime[N]; // 记录质数
int phi[N];   // 欧拉函数

void euler(int n) {
    memset(v, 0, sizeof v);
    int m = 0; // 质数数量
    for (int i = 2; i <= n; ++i) {
        // 未被筛过，则为质数
        if (v[i] == 0) {
            v[i] = i;
            prime[++m] = i;
            phi[i] = i - 1; // 可以直接得出质数的欧拉函数
        }
        for (int j = 1; j <= m; ++j) {
            // i的最小质因子更小 或 超出范围，则break
            if (prime[j] > v[i] || prime[j] * i > n)
                break;
            v[i * prime[j]] = prime[j]; // 更新最小质因子
            // 根据欧拉函数性质，递推
            phi[i * prime[j]] = phi[i] * (i % prime[j] ? prime[j] - 1 : prime[j]);
        }
    }
}
```



<br/>


### 例题


[**201. 可见的点 - AcWing题库**](https://www.acwing.com/problem/content/203/)

除了（1,0）、（0,1）和（1,1）这三个钉子以外，一个钉子（x，y）能被看见当且仅当， $1\le x,y \le N$ 并且 $gcd(x,y)=1$ （否则就会被前面的钉子挡住）。由于对称，只考虑上面部分，对于每个 $y$ ，求出 $\varphi (y)$ 。


<br/>


[**220. 最大公约数 - AcWing题库**](https://www.acwing.com/problem/content/description/222/)

可以枚举以每一个质数作为最大公约数的数对有多少，需要计算欧拉函数。

由于本题数量范围较大，所以在计算 2 到 N 的欧拉函数时，必须使用 $O(N)$ 的算法。


<br/>

[**221. 龙哥的问题 - AcWing题库**](https://www.acwing.com/problem/content/223/)



---


<br/>


<br/>


<br/>


<br/>


# 同余

## 同余基本性质

**性质一**

$$
\text{如果}a\equiv b\left( mod\ m \right) \ ,\ \text{并且}x\equiv y\left( mod\ m \right) \ ,\text{则}a+x\equiv b+y\left( mod\ m \right) 
$$

**性质二**

$$
\text{如果}a\equiv b\left( mod\ m \right) \ ,\ \text{并且}x\equiv y\left( mod\ m \right) \ ,\text{则}a\times x\equiv b\times y\left( mod\ m \right) 
$$

**性质三**

$$
\text{如果}a\times c\equiv b\times c\left( mod\ m \right) \ ,\ \text{并且}c,m\text{互质\ ,则}a\equiv b\left( mod\ m \right) 
$$


---


<br/>


<br/>


<br/>



## 欧拉定理

### 剩余系
- 同余类：模 m 余数相同的一类整数。
- **完全剩余系**：模 m 的 m 个同余类构成完全剩余系。
- **简化剩余系**：1 到 m 中与 m 互质的 $\varphi (N)$ 个数代表的同余类构成简化剩余系。**简化剩余系关于模 m 乘法封闭**。设 n 的简化剩余系为 $\left\{ a_1, a_2,..., a_{\varphi \left ( n \right)} \right\}$ ，则，**当 $a_i \ne a_j$ 并且 $a$ 与 $p$ 互质 时， $aa_i$ 和 $aa_j$ 代表不同的同余类**。

----

<br/>

### 费马小定理

**$p$ 为质数**，对于任意整数 $a$，有 $a^{p-1}\equiv 1(mod \ p)$ 。

---

<br/>

### 欧拉定理

**$a$ 与 $n$ 互质**，则 $a^{\varphi (n)} \equiv 1\ (mod\ n)$ 。可以看出，费马小定理是欧拉定理的特殊情况。

---

<br/>

### 拓展欧拉定理

弱化了欧拉定理条件，不需要 $a$ 和 $n$ 互质，对于任意整数 $b$ 有，

$$
a^b\equiv \left\{ \begin{array}{l}
	a^b\ ,\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ b<\varphi \left( n \right) \ \left( mod\ n \right)\\
	a^{b\ mod\ \varphi \left( n \right) \ +\ \varphi \left( n \right)}\ ,\ b\ge \varphi \left( n \right) \ \left( mod\ n \right)\\
\end{array} \right. 
$$

<span style="background:#fff88f">特别的，如果 $a$ 和 $n$ 互质，则 $a^b\equiv \ a^{b\ mod\ \varphi \left ( n \right)}\ \left ( mod\ n \right)$ 。</span>

当需要求解 $a^b$ 取模的结果时，并且 $b$ 非常大（字符串表示的大整数），可以**使用拓展欧拉定理降幂**，再使用快速幂。

```cpp
int depow(string &b, int phi) {
    bool f = false;
    int ret = 0;
    for (int i = 0; i < b.size(); ++i) {
        ret *= 10;
        ret += b[i] - '0';
        if (ret >= phi) {
            f = true;   // 判断是否属于第二种情况，即b>=phi
            ret %= phi;
        }
    }
    if (f)
        ret += phi;
    return ret;
}


```

---

<br/>



### 例题

[**202. 最幸运的数字 - AcWing题库**](https://www.acwing.com/problem/content/204/)

$x$ 个 8 连在一起的整数可以表示为 $8\times \left( 10^0+10^1+...+10^{x-1} \right) =\frac{8\left( 10^x-1 \right)}{9}$

$$
L|\frac{8\left( 10^x-1 \right)}{9}\Longleftrightarrow 9L|8\left( 10^x-1 \right) \Longleftrightarrow \frac{9L}{d}|10^x-1\Longleftrightarrow 10^x\equiv 1\left( mod\ \frac{9L}{d} \right) ,\ \text{其中}d=gcd\left( L,8 \right) 
$$

**引理：若 $a,n$ 互质，则满足 $a^x\equiv 1(mod\ n)$ 的最小整数 $x_0$ 是 $\varphi (n)$ 的约数**。

令 $c=\frac{9L}{d}$ ，由于 $10^x\equiv 1\left( mod\ c \right)$ ，则 $10，c$ 必然互质，可以使用上述引理，求出欧拉函数，对其余数进行逐个使用快速幂判断。



<br/>

[**P5091 【模板】扩展欧拉定理 - 洛谷**](https://www.luogu.com.cn/problem/P5091)

使用拓展欧拉定理降幂，然后快速幂计算。


---


<br/>


<br/>


<br/>


## 拓展欧几里得算法

### 裴蜀定理

对于不全为零的任意整数 $a$ 和 $b$  ，则对于任意整数 $x$ 和 $y$ 都满足 $a\times x+b \times y$ 是 $gcd(a,b)$ 的倍数。**并且 $a\times x+b \times y$ 的最小正整数为 $gcd(a,b)$  。**

假设 $a\times x+b \times y=s$ ，当 $gcd(a,b)$ 不能整除 $s$ 时，方程无整数解。

---

<br/>


### 裴蜀定理推广

一定存在一组整数 $x_1,x_2,...,x_n$ ，满足 $\sum_{i=1}^n{a_i\times x_i}=s$ ，其中 $gcd\left ( a_1, a_2,..., a_n \right)|s$ 。 

---


<br/>

### 拓展欧几里德算法

用于求解裴蜀定理的一组特解。在欧几里得算法中:
- 当 $b=0$ 时，存在特解 $x=1,y=0$ ，使得 $a\times b+b\times y=gcd(a,b)$
- 当 $b\ne 0$ 时， $gcd(a,b)=gcd(b,a\%b)$

$gcd(a,b)=ax+by$
	
$$
gcd(b,a\%b)=b\times x_1+(a\%b)\times y_1
$$

$$
=b\times x_1+\left( a-\lfloor \frac{a}{b} \rfloor \times b \right) \times y_1
$$

$$
=a\times y_1+b\times \left( x_1-\lfloor \frac{a}{b} \rfloor \times y_1 \right) 
$$

所以可以采用递归算法，求出下一层的特解 $x_1,y_1$ ，然后利用 $x_1,y_1$ 计算本层的特解。

```cpp
int exgcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    int d, x1, y1;
    d = exgcd(b, a % b, x1, y1);
    x = y1, y = x1 - a / b * y1;
    return d;
}
```


**拓展欧几里得算法构造通解**

利用拓展欧几里得算法求出一组特解 $x_0,y_0$ ，利用以下形式构造通解：

$$
\left\{ \begin{array}{l}
	x=x_0+\frac{b}{gcd\left( a,b \right)}\times k\\
	y=y_0-\frac{a}{gcd\left( a,b \right)}\times k\\
\end{array} \right. 
$$

$k$ 取值不同，对应不同的解，除以 $gcd$ 保证解一定是整数。

---

<br/>



### 乘法逆元

**当 $a,m$ 互质**，如果有 $ax\equiv 1(mod\ m)$ ，那么 $x$ 就成为 $a$ 模 $m$ 的乘法逆元（ $0 < x< m$ ）。

- 当 $m$ 为质数时，根据**费马小定理**， $a\times a^{m-2} \equiv 1(mod\ m)$ ， $a^{m-2}$ 就是 $a$ 模 $m$ 的乘法逆元。
- 同理，在任意情况下，根据**欧拉定理**， $a^{\varphi (n)-1}$ 为 $a$ 模 $m$ 的乘法逆元。

求出乘法逆元的一个特解之后，加上任意整数倍的 $m$ 依然是乘法逆元。

**乘法逆元的应用**——**当需要进行取余的式子存在分式，可以利用乘法逆元，将除法转化为乘法**。

$$
\frac{a}{b}\equiv a\times x\left( mod\ m \right) \ ,\ x\text{为}b\text{模}m\text{乘法逆元}
$$


---

<br/>


### 例题

[**P4549 【模板】裴蜀定理 - 洛谷**](https://www.luogu.com.cn/problem/P4549)

有裴蜀定理推广可知，满足 $\sum_{i=1}^n{a_i\times x_i}=s$ ， $s$ 的最小正整数值为 $gcd\left ( a_1, a_2,..., a_n \right)$ 。

本题中， $a_i$ 可能取得负值，**自己手写实现的欧几里得算法当存在负值时，返回的结果可能为负数**，需要加绝对值。C++17 提供的 `gcd` 函数则不需要特殊处理。


<br/>


[**97. 约数之和 - AcWing题库**](https://www.acwing.com/problem/content/99/)

把 $A$ 进行质因数分解，得到 $p_1^{c_1}\times p_2^{c_2}\times ... p_n^{c_n}$ 。 $A^B$ 的约数之和为
$$
\left( 1+p_1+p_{1}^{2}+...+p_{1}^{c_1\times B} \right) \times \left( 1+p_2+p_{2}^{2}+...+p_{2}^{c_2\times B} \right) \times \left( 1+p_m+p_{m}^{2}+...+p_{m}^{c_m\times B} \right) 
$$

本题在基本算法部分已经解决过，对于每一项等比数列的求和，采用分治的方法求解。

现在，使用等比数列求和式求解，对于每一项，其和为 $\frac{p^{B\times c}-1}{p-1}$ ，先使用快速幂计算出分子 mod 9901 的值：
- **当分母 $p-1$ 为 9901 的倍数时（即，不互质），不存在乘法逆元**。但是此时有 $p\equiv p^2 \equiv ,,, \equiv 1(mod 9901)$ ，所以 $\left( 1+p+p^{2}+...+p^{c\times B} \right) \equiv (1+ 1+ 1^2 +1^3+...+1^{B\times c}) \equiv B\times c+1(mod \ 9901)$ 。
- 当分母 $p-1$ 不是 9901 的倍数时，9901 为质数，所以分母和 9901 互质，使用费马小定理计算出乘法逆元 $inv$ ，替代处理分母。


<br/>


[**222. 青蛙的约会 - AcWing题库**](https://www.acwing.com/problem/content/224/)

根据题意有

$$
x+t\times m\equiv y+t\times n\ \left( mod\ L \right) 
$$

可以化为
$$
\left( m-n \right) \times t\equiv y-x\ \left( mod\ L \right) 
$$

显然这是一个一次同余方程可以使用拓展欧几里得算法求解。

需要注意的是，**<span style="background:#fff88f">拓展欧几里得算法中输入的参数应该为正数，否则会出错</span>**。




---


<br/>


<br/>


<br/>




## 线性同余方程

### 一次同余方程

求一个整数 $x$ ，满足 $a\times x\equiv b(mod \ m)$ ，或者无解。

使用拓展欧几里得算法求解线性同余方程： 由 $a\times x\equiv b(mod \ m)$ ，可得

$$
a\times x=m\times -y+b
$$

即，

$$
a\times x+m\times y=b
$$

由裴蜀定理可知，当且仅当 $gcd(a,m)|b$ 时方程有解。当方程有解时，先求出方程 $a\times x+m\times y=gcd(a,m)$ 的解 $x_0$ ，然后 $x=x_0\times \frac{b}{gcd\left( a,m \right)}$ 得到同余方程的解。

乘法逆元是 $b$ 等于 1 的特殊情况，也可以使用拓展欧几里得算法求解。

---

<br/>

### 中国剩余定理

用于求解线性同余方程组。

$$
\left\{ \begin{array}{l}
	x\equiv r_1\left( mod\ m_1 \right)\\
	...\\
	x=r_n\left( mod\ m_n \right)\\
\end{array} \right. 
$$

其中模数 $m_1,m_2,...,m_n$ **两两互质**。求 $x$ **最小非负整数解**。

中国剩余定理 CRT 求解步骤如下
- 计算所有模数的积 $M$
- 计算第 $i$ 个方程的 $c_i=\frac{M}{m_i}$
- 计算 $c_i$ 模 $m_i$ 的乘法逆元 $c_i^{-1}$

$x=\sum{c_i\times c_i^{-1}\times r_i}(mod\ M)$ 。

```cpp
long long exgcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    long long d, x1, y1;
    d = exgcd(b, a % b, x1, y1);
    x = y1, y = x1 - a / b * y1;
    return d;
}

long long CRT(vector<long long> &m, vector<long long> &r) {
    int n = m.size();
    long long M = 1;
    long long ans = 0;
    for (int i = 0; i < n; ++i)
        M *= m[i];
    for (int i = 0; i < n; ++i) {
        long long c = M / m[i];
        long long x, y;
        exgcd(c, m[i], x, y);
        ans = (ans + c * x * r[i] % M) % M; //这一步乘法有溢出的可能，需要根据数据范围采取合适的方式
    }
    return (ans%M+M)%M; // 计算乘法逆元时可能出现负数
}
```


---

<br/>


### 拓展中国剩余定理

当线性同余方程组中的模 $m_i$ **不能**保证两两互质时，不能使用 CRT 算法求解。

使用数学归纳法求解，首先考虑前两个方程

$$
\left\{ \begin{array}{l}
	x\equiv r_1\left( mod\ m_1 \right)\\
	x\equiv r_1\left( mod\ m_2 \right)\\
\end{array} \right. 
$$

转化为不定方程

$$
x=pm_1+r_1=-qm_2+r_2
$$
$$
pm_1+qm_2=r_2-r_1
$$

由裴蜀定理，当且仅当 $gcd(m_1,m_2)|r_2-r_1$ 时有解。在有解的情况下，通过拓展欧几里得算法求出 $p$ ，得到特解 $p=p\times \frac{r_2-r_1}{gcd\left( m_1,m_2 \right)}$

可以构造出通解

$$
P=p+\frac{m_2}{gcd\left( m_1,m_2 \right)}\times k
$$

将通解代入不定方程：

$$
x=m_1\times P+r_1=m_1p+\frac{m_1m_2}{gcd\left( m_1,m_2 \right)}\times k+r_1
$$
$$
x\equiv m_1p+r_1\ \left( mod\ lcm\left( m_1,m_2 \right) \right) 
$$


```cpp
using int64 = long long;
using int128 = __int128_t;

int128 exgcd(int128 a, int128 b, int128 &x, int128 &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    int128 x1, y1, d;
    d = exgcd(b, a % b, x1, y1);
    x = y1, y = x1 - a / b * y1;
    return d;
}

void solve() {
    int64 n;
    cin >> n;
    vector<int64> m(n), r(n);
    for (int i = 0; i < n; ++i)
        cin >> m[i] >> r[i];

    int128 m1, m2, r1, r2, p, q;
    m1 = m[0], r1 = r[0];
    for (int i = 1; i < n; ++i) {
        m2 = m[i], r2 = r[i];

        int128 d = exgcd(m1, m2, p, q);
        if ((r2 - r1) % d) {
            cout << "-1\n";
            return;
        }

        p = p * (r2 - r1) / d;                  // 一个特解
        p = (p % (m2 / d) + m2 / d) % (m2 / d); // 根据通解公式，获得一个最小非负的特解

        r1 = m1 * p + r1;
        m1 = m1 / d * m2;
    }
    cout << (int64)((r1 % m1 + m1) % m1);
}
```

---



<br/>


### 例题

[**203. 同余方程 - AcWing题库**](https://www.acwing.com/problem/content/205/)

题目本质上是求 $a$ 模 $b$ 的乘法逆元。

使用拓展欧几里得算法求解得到特解 $x$ ， $x$ 为负数或者 $\ge b$ ，所以需要 `（ x % b + b ）% b` 保证得到的解是最小的正整数。


<br/>

[**P1495 【模板】中国剩余定理（CRT）/ 曹冲养猪 - 洛谷**](https://www.luogu.com.cn/problem/P1495)

中国剩余定理模板题，本题中由于只保证 $M\le 10^{18}$ ，**long long 类型表示的最大整数约为 $9.2\times 10^{18}$** ， 所以在进行乘法运算时，即使使用 long long 也有可能溢出。

在进行乘法运算时可以自己编写函数，边取模，边计算，确保不会溢出
```cpp
long long qmul(long long a, long long b, long long c) {
    long long res = 0;
    while (b) {
        if (b & 1) res = (res + a) % c;
        a = (a + a) % c;
        b >>= 1;
    }
    return res;
}
```

或者使用 **GCC 和 Clang 编译器**提供的 `__int128_t` 类型。


<br/>

[**P4777 【模板】扩展中国剩余定理（EXCRT） - 洛谷**](https://www.luogu.com.cn/problem/P4777)

拓展中国剩余定理模板题，由于题目中数据可以达到 $10^{12}$ ，所以需要使用 `__int128_t` 类型。



<br/>

[**204. 表达整数的奇怪方式 - AcWing题库**](https://www.acwing.com/problem/content/206/)

题目不保证有解，需要判断无解情况。

---


<br/>


<br/>


<br/>




## 高次同余方程

对于高次同余方程，我们主要讨论 $a^x\equiv b(mod \ p)$ 这种类型。

### BSGS 算法

对于高次同余方程 $a^x\equiv b(mod \ p)$ ，**当 $a,p$ 互质时**，使用 Baby Step Gaint Step 算法求解 $x$ 。

由拓展欧拉算法，得 $a^x\equiv a^{x\  mod \  \varphi (p)}\equiv b(mod\ p)$

所以 ** $x$ 的取值范围肯定在 $0$ 到 $p-1$ 之间**，如果直接枚举，时间复杂度为 $O(p)$ ，可以对取值的区间进行分块，令每一块的长度 $m=\ \lceil \sqrt{p} \rceil$ ，则有

$$
x=i\times m-j
$$

则 $(a^m)^i\equiv b\times a^j(mod \ m)$ （从这一步看出 $a,p$ 必然是互质的，否则无法从这一步倒退会前一步。 ）

显然有，$i\in \left[ 1, m \right] ,\ j\in \left[ 0, m-1 \right]$

- 枚举 $j$ ，算出对应的 $b\times a^j (mod \ m)$ ，存入哈希表中
- 枚举 $i$ ，算出 $(a^m)^i(mod \ m)$ ，在哈希表查找，如果找到，算法结束

```cpp
using LL = long long;

LL bsgs(LL a, LL b, LL p) {
    // 要求a,p互质
    a %= p, b %= p; // 不影响结果
    // 特判
    if (b == 1)
        return 0;
    LL m = ceil(sqrt(p)); // 分块
    unordered_map<LL, LL> hash;
    LL t = b;
    hash[t] = 0;
    for (int j = 1; j < m; ++j) {
        t = t * a % p;
        hash[t] = j;
    }
    LL mi = 1;
    for (int i = 1; i <= m; ++i)
        mi = mi * a % p;
    t = 1;
    for (int i = 1; i <= m; ++i) {
        t = t * mi % p;
        if (hash.find(t) != hash.end())
            return i * m - hash[t]; // 找到解
    }
    return -1; // 无解
}
```


---


<br/>


### 拓展 BSGS 算法

在 BSGS 算法中，要求 $a,p$ 是互质的

当 $a,p$ 不互质时，无法求解，需要设法将方程进行变换得到 $a,p$ 互质的形式。

原方程等价于 $a\times a^{x-1}+p\times y=b$

设 $d_1=gcd(a,p)$ ，如果 $d_1$ 不能整除 $b$ ，则无解。

方程两边同时除以 $d_1$ ，得

$$
\frac{a}{d_1}a^{x-1}\equiv \frac{b}{d_1}\left( mod\ \frac{p}{d_1} \right) 
$$

如果 $a$ 和 $\frac{p}{d_1}$ 不互质，需要重复上面的步骤，直到重复 $k$ 次之后，有 $a\bot \frac{p}{d_1...d_k}$ ，令 $D=d_1...d_k$ ，有

$$
\frac{a^k}{D}a^{x-k}\equiv \frac{b}{D}\left( mod\ \frac{p}{D} \right) 
$$

可以使用 BSGS 算法求解。

```cpp
using LL  = long long;
LL exbsgs(LL a, LL b, LL p) {
    a %= p, b %= p;
    if (b == 1 || p == 1)
        return 0;

    LL d, k = 0, A = 1;
    for (;;) {
        d = std::gcd(a, p);
        if (d == 1)
            break; // 互质，可以使用bsgs
        if (b % d)
            return -1; // 无解
        ++k, b /= d, p /= d;
        A = A * (a / d) % p;
        if (A == b)
            return k;
    }
    LL m = std::ceil(sqrt(p));
    LL t = b;
    unordered_map<LL, LL> hash;
    hash[b] = 0;
    for (int j = 1; j < m; ++j) {
        t = t * a % p;
        hash[t] = j;
    }
    LL mi = 1;
    for (int i = 1; i <= m; ++i)
        mi = mi * a % p;
    t = A; // 需要多一个系数
    for (int i = 1; i <= m; ++i) {
        t = t * mi % p;
        if (hash.find(t) != hash.end())
            return i * m - hash[t] + k;
    }
    return -1;
}
```


----

<br/>




### 例题


[**P3846 [TJOI2007] 可爱的质数/【模板】BSGS - 洛谷**]( https://www.luogu.com.cn/problem/P3846 )

BSGS 模板题

<br/>

[**P4195 【模板】扩展 BSGS/exBSGS - 洛谷**](https://www.luogu.com.cn/problem/P4195)

exBSGS 模板题

---


<br/>


<br/>


<br/>


<br/>


# 矩阵快速幂

矩阵的快速幂运算，跟整数的快速幂运算类似，模板代码如下：

```cpp
const int N = 100;
const int mod = 10000;

struct matrix {
    int data[N + 1][N + 1]{};
    matrix operator*(const matrix &b) const {
        matrix c;
        for (int i = 1; i <= N; ++i)
            for (int j = 1; j <= N; ++j)
                for (int k = 1; k <= N; ++k)
                    c.data[i][j] = (c.data[i][j] + data[i][k] * b.data[k][j] % mod) % mod;
        return c;
    }
};

matrix matrix_qpow(matrix a, long long b) {
    matrix res;
    for (int i = 1; i <= N; ++i)
        res.data[i][i] = 1;
    for (; b; b >>= 1) {
        if (b & 1)
            res = res * a;
        a = a * a;
    }
    return res;
}
```

矩阵快速幂可以用于**加快状态的递推**。当一类问题具有以下特点时，可以考虑使用矩阵快速幂优化：

- 可以抽象出一个长度为 $n$ 的向量
- 变化的形式是线性递推（若干个加法或乘以一个系数）
- 递推式本身保持不变
- 向量递推的轮数很大，但是向量长度 $n$ 不大

时间复杂度为 $O(n^3\times log \ T)$ 其中 $n^3$ 为一次矩阵乘法的时间代价。



### 例题

[**205. 斐波那契 - AcWing题库**](https://www.acwing.com/problem/content/207/)

由于斐波那契数列的每一项都是由前两项递推而来，可以写出递推关系，

$$
\left[ \begin{matrix}
	F_n&		F_{n-1}\\
\end{matrix} \right] =\left[ \begin{matrix}
	F_{n-1}&		F_{n-2}\\
\end{matrix} \right] \left[ \begin{matrix}
	1&		1\\
	1&		0\\
\end{matrix} \right] 
$$

所以有，

$$
\left[ \begin{matrix}
	F_n&		F_{n-1}\\
\end{matrix} \right] =\left[ \begin{matrix}
	F_1&		F_0\\
\end{matrix} \right] \left[ \begin{matrix}
	1&		1\\
	1&		0\\
\end{matrix} \right] ^{n-1}
$$

而$\left[ \begin{matrix}
	1&		1\\
	1&		0\\
\end{matrix} \right] ^{n-1}$可以使用矩阵的快速幂运算加速计算。


<br/>


[**206. 石头游戏 - AcWing题库**](https://www.acwing.com/problem/content/description/208/)

**在使用矩阵计算加速递推时，需要将初始状态设置为一个一维的向量 $F_0$ 。**

在本题中，可以将二维数组一维化，一维向量中每个数字代表一个格子的石头数量，初始全为 0。

接下来考虑状态转移矩阵，在本题中，转移矩阵会随着指令序列变化，但是**执行序列存在周期性变化**，由于指令序列长度最长为 6，1 到 6 的最小公倍数为 60，则有 $A_i=A_{k\times 60+i}$ ，设

$$
A=\prod_{i=1}^{60}{A_i}
$$

将 $A$ 一整块看作是一个转移矩阵，进行快速幂。设 $t=p\times 60 +r$ ，则 $Ft=F_0\times A^p\times \prod_{i=1}^r{A_i}$ 。

对于状态转移矩阵的设置也很有技巧，对于第 $k$ 个转移矩阵：
- $A_k[0][0]=1$
- 如果在格子 $(i,j)$ 放上 $x$ 个石头，则 $A_k[0][num(i,j)]=x$ ， $num$ 是下标转换函数，另外本来格子的石头数量不变， $A_k[num(i,j)][num(i,j)]=1$
- 如果将格子 $(a,b)$ 的石头移动到 $(c,d)$ ，则 $A_k[num(a,b)][num(c,d)]=1$ 

---


<br/>


<br/>


<br/>


<br/>


# 高斯消元 & 线性空间

## 高斯消元法

高斯消元法是一种求解**线性方程组**的方法，另外可以其思想求解**异或方程组**。

求解方法为，先写出方程组对应的增广矩阵（系数矩阵+等号右边的常数）。对于增广矩阵，可以通过初等行变换进行求解。**高斯-约旦消元法**先将系数矩阵消成主对角矩阵，然后除以主元得到解，步骤如下：
- 枚举主元（即， $a[i][i]$ ），如果主元为零，则向下找到一个 $a[k][i],k\ge i$ 非零的行，与当前行交换。
	- 接下来实行对角化，从 $1$ 到 $n$ 行（除了当前行本身），通过行变换使当前主元对应的列全为零（除了单前行本身）
- 最后对应行常数除以主元得到解。

以上为有唯一解的情况。在不是唯一解的情况下，还需要判断是否无解还是有无穷多解。

```cpp
const double eps = 1e-8;

/**
 * @brief 高斯-约旦消元法
 *
 * @return int 自由元个数, -1表示无解
 */
int Gauess_Jordan(vector<vector<double>> &a, int n) {
    int row = 1, col = 1;
    for (; row <= n && col <= n; ++col) {
        int r = row;
        for (int k = row; k <= n; ++k)
            if (fabs(a[k][col]) > eps) {
                r = k;
                break;
            }
        if (r != row)
            swap(a[row], a[r]);
        if (fabs(a[row][col]) < eps) {
            continue;
        }

        // 消去其余行col列的系数
        for (int k = 1; k <= n; ++k) {
            if (k == row)
                continue;
            double t = a[k][col] / a[row][col];
            for (int j = 1; j <= n + 1; ++j)
                a[k][j] -= t * a[row][j];
        }
        ++row;
    }
    // 无解 或者 无穷多解
    if (row <= n) {
        for (int i = row; i <= n; ++i)
            if (fabs(a[i][n + 1]) > eps)
                return -1;
        return n - row + 1; // 自由元的个数
    }
    for (int i = 1; i <= n; ++i)
        a[i][n + 1] /= a[i][i];
    return 0;
}
```


### 例题

[**P3389 【模板】高斯消元法 - 洛谷**](https://www.luogu.com.cn/problem/P3389)

高斯消元法模板题，需要四舍五入保留两位小数，输出时应使用 
```cpp
cout << fixed << setprecision(2) << round(a[i][n + 1] * 100) / 100 << '\n';
```

当输入类型为 `long double` 使用 `roundl` 函数。


<br/>

[**207. 球形空间产生器 - AcWing题库**](https://www.acwing.com/problem/content/209/)

球面上所有点到球心的距离相等，所以需要求出一个点满足

$$
\sum_{j=1}^n{\left( a_{i,j}-x_j \right) ^2=C}
$$

可以列出 $n+1$ 个 $n$ 元二次方程，并非线性方程，但是可以相邻两个方程作差消去平方项，得到线性方程组，然后使用高斯消元求解。

本题中需要注意，由于输出保留三位小数，当答案是一个很小的负数时，可能会出现 `-0.000` 的情况，为了规避这样的情况可以，进行以下处理：

```cpp
double a = -0.0001;
cout<< (long long)(a*1000)/1000.0;
```


<br/>


[**208. 开关问题 - AcWing题库**](https://www.acwing.com/problem/content/210/)

一个开关受到多个开关（当然包括自己本身）影响时，将这个开关集合称为 $S$ ， 只要其中一个发生变化，该开关的状态就会发生变化，当一个开关的初始和结束状态一样时， $S$ 中一定有偶数个开关被按下。

所以可以列出**异或方程组**， $a_{i,j}=1$ 表示第 $i$ 个开关会受到第 $j$ 个开关的影响， $x_i=1$ 表示第 $i$ 个开关被按动。

$$
\left\{ \begin{array}{l}
	a_{1,1}x_1\,\,xor\,\,a_{1,2}x_2\,\,xor\,\,...\,\,a_{1,n}x_n\,\,=\,\,src_1\,\,xor\,\,dst_1\\
	...\\
	a_{n,1}x_1\,\,xor\,\,a_{n,2}x_2\,\,xor\,\,...\,\,a_{n,n}x_n\,\,=\,\,src_n\,\,xor\,\,dst_n\\
\end{array} \right. 
$$

本题求的是方案数量，可以统计出自由元的数量 $cnt$ ，每个 $x$ 的取值只有 $0,1$ ，所以总方案数为 $2^{cnt}$ 。


---


<br/>


<br/>


<br/>



## 线性空间

线性空间是关于下面运算封闭的向量集合：
- 向量加法
- 标量乘法

一个向量能被若干个向量通过向量加法和标量乘法得到，则称向量可以被这若干个向量**表出**。能被这若干个向量标出的所有向量构成一个线性空间，这若干个向量就是该线性空间的**生成子集**。

在若个向量中，如果其中一个向量能被其他向量表出，则这些向量**线性相关**。线性无关的子集称为线性空间的**基**，基底包含向量个数称为**维数**。

对于一个 $n$ 行 $m$ 列的矩阵，可以看作 $n$ 个行向量，这 $n$ 个向量构成的线性空间的维数称为矩阵的**行秩**，矩阵的行秩等于列秩。

把矩阵进行高斯消元（行变换的运算本质上就是向量加法和标量乘法，不改变线性空间），**简化阶梯矩阵所有非零行向量线性无关**。



<br/>


线性空间可以推广得到<span style="background:#fff88f">**异或空间**</span>：
- 关于异或运算封闭


将一个数字看作是一个向量，每一个二进制为为分量。同样可以推导出生成子集、线性无关等概念。

可以通过高斯消元得到异或空间的基底：

```cpp
for (int i = 1; i <= n; ++i) {
    for (int j = i + 1; j <= n; ++j)
        if (a[j] > a[i])
            swap(a[i], a[j]);

    if (a[i] == 0) {
        break;
    }
    for (int k = 63; k >= 0; --k) {
        if (a[i] >> k & 1) {
            for (int j = 1; j <= n; ++j) {
                if (i != j && (a[j] >> k & 1))
                    a[j] ^= a[i];
            }
            break; // 只消去当前列
        }
    }
}
```


假设一个异或空间有 $t$ 个基底，分别是 $b_0 > b_1 > ..> b_{t-1}$ ，其对应的最高位 $c_0 > c_1> ... > c_{t-1}$ 。该异或空间中的所有数字都是选出若干个基底得到的，所以， **<span style="background:#fff88f">$t$ 维异或空间，一共有    $2^t$ 个整数</span>**。

<span style="background:#fff88f">该异或空间中所有数字，按从小到大排序，**第 $i$ 个数字（从 $0$ 开始），对应的二进制数和 $b_0 > b_1 > ..> b_{t-1}$ ，有一一对应的关系**</span>。例如求第 $1$ 小的数字，二进制拆分为 $...0001$ ，只有第 $0$ 位为 1，所以选出 $b_0$ 进行异或操作。


<br/>


### 例题


[**209. 装备购买 - AcWing题库**](https://www.acwing.com/problem/content/211/)

题目意思等价于求一个线性空间的基底，同时有最小花费大要求，随意在进行高斯消元时，有多个行可供选择时，优先权费用最小的。

<br/>


[**210. 异或运算 - AcWing题库**](https://www.acwing.com/problem/content/212/)

求解异或空间第 $k$ 小的数字，先进行高斯消去得到基底，然后对 $k$ 进行二进制拆分得到答案。

本题不同之处在于，是选不同的数字进行异或，在异或空间中，可以选择两个 0 进行异或，所以如果高斯消元之后没有全为 0 的行，那么最小不可能得到 0 。另外需要注意的是，**异或空间中第 $i$ 数字是从 $0$ 开始编号的。**


---


<br/>


<br/>


<br/>


<br/>


# 组合计数

## 组合数性质

**排列数**： $A_n^m=\frac{n!}{\left( n-m \right) !}$

**组合数**： $C_n^m=\frac{n!}{m!\times \left( n-m \right) !}$

**性质**
- $C_n^m=C_{n-1}^m+C_{n-1}^{m-1}$ ，递推可以得出
- $C_n^0+C_n^1+C_n^2+...+C_n^n=2^n$ ， $n$ 选出任意个得到的排列数，对于每个数有选与不选两种可能
- **二项式定理**： $\left( a+b \right) ^n=\sum_{k=0}^n{C_n^ka^kb^{n-k}}$

---


<br/>


<br/>


<br/>



## 求组合数

### 递推法

根据 $C_n^m=C_{n-1}^m+C_{n-1}^{m-1}$ 进行递推，时间复杂度为 $O(n^2)$

---

<br/>


### 乘法逆元法

如果求的是**组合数 $C_n^m$ 对 $p$ 取模的结果**，并且 <span style="background:#fff88f">**$1$ 到 $m$ 都与 $p$ 互质**</span>，即可以求乘法逆元（一般 $p$ 都是一个质数，只要保证分母不是 $p$ 的倍数即可 ）。可以求出分子、分母对 $p$ 取模的结果，再分子乘以分母的乘法逆元。

当需要频繁求组合数时，可以预处理出 $k,0\le k\le n$ 的阶乘及其逆元。预处理时间复杂度为 $O(n\times log P)$

```cpp
using LL = long long;
const int N = 10000;

LL f[N], inv[N];

LL qpow(LL a, LL b, LL mod) {
    LL res = 1;
    for (; b; b >>= 1) {
        if (b & 1)
            res = res * a % mod;
        a = a * a % mod;
    }
    return res;
}

void init(LL mod) {
    f[0] = inv[0] = 1;
    for (LL i = 1; i < N; ++i) {
        f[i] = f[i - 1] * i % mod;
        inv[i] = inv[i - 1] * qpow(i, mod - 2, mod) % mod;
    }
}

LL C(LL n, LL m, LL mod) {
    return f[n] * inv[m] % mod * inv[n - m] % mod;
}
```

---

<br/>


### 卢卡斯定理

<span style="background:#fff88f">**如果 $p$ 是质数**</span>，则对于任意整数 $1\le m\le n$ ，有

$$
C_n^m\equiv C_{n\ mod\ p}^{m\ mod\ p}\times C_{n\ /\ p}^{m\ /\ p}\left( mod\ p \right) 
$$

卢卡斯定理用于处理**大组合数取模问题**——当 $n$ 取值非常大时，而 $p$ 的取值相对较小。

在代码实现时， $n \ mod \ p$ 一定是小于 $p$ 的，可以直接计算组合数， $\frac{n}{p}$ 的数量级可能还是很大，可以进行递归处理。

<span style="background:#fff88f">**在代码实现时，因为进行了取模处理，所以在计算组合数的函数中，可能会出现 $m > n$ 的情况，需要特殊处理**。</span>

```cpp
LL C(LL n, LL m, LL p) {
    if (m > n)  //很重要的条件判断
        return 0;
    return f(n, p) * inv(m, p) % p * inv(n - m, p);
}

LL lucas(LL n, LL m, LL mod) {
    if (m == 1)
        return 1;
    return lucas(n / mod, m / mod, mod) * C(n % mod, m % mod, mod) % mod;
}
```

**当 $n,p$ 都非常大时，可以考虑对 $p$ 进行质因数分解**，计算组合数对每个因数分别取模的结果，然后使用中国剩余定理计算出答案，如例题古代朱文。

---


<br/>


### 例题

[**211. 计算系数 - AcWing题库**](https://www.acwing.com/problem/content/213/)

二项式定理求组合数即可，由于 $n$ 小于 $p$ ，所以可用逆元转化为乘法运算。

<br/>



[**P3807 【模板】卢卡斯定理/Lucas 定理 - 洛谷**](https://www.luogu.com.cn/problem/P3807)

本题咋一看可以直接使用乘法逆元求组合数，但是从本题的数据范围来看， $n$ 可能是 $p$ 的倍数，即不满足 $n,p$ 互质的条件，无法求乘法逆元。

使用卢卡斯定理，由于进行了取模运算，取模之后 $n$ 必定小于 $p$ ，可以使用乘法逆元代替除法。


<br/>


[**212. 计数交换 - AcWing题库**](https://www.acwing.com/problem/content/description/214/)

本题是一道相当困难的推理题，需要从本题中学习几个结论：
- <span style="background:#fff88f">**把一个长度为 $n$ 的环变成 $n$ 个自环，最少需要 $n-1$ 次交换操作**</span>。可以是使用归纳法证明。
- <span style="background:#fff88f">**$F_n$ 表示把一个长度为 $n$ 的环变成 $n$ 个自环，共有多少种操作方法。 $F_n=n^{n-2}$ 。**</span>


<br/>


[**213. 古代猪文 - AcWing题库**](https://www.acwing.com/problem/content/215/)

本题需要计算 $q^{\sum_{d|n}{C_{n}^{d}}}\ mod\ 999911659$ ，显然 $\varphi(999911659)=999911658$ ， 由欧拉定理推论可知，关键在于求出

$$
\sum_{d|n}{C_{n}^{d}}\ mod\ 999911658
$$

由于 $n，d$ 的范围都很大，所以无法直接使用卢卡斯定理。**<span style="background:#fff88f">令 $P=999911658$ 进行质因数分解，得到 $P=2\times 3\times 4679 \times 35617$ ，可以使用卢卡斯定理，分别求出 $\sum_{d|n}{C_{n}^{d}}$ 对这四个数取模的结果，然后利用中国成语定理建立同余方程组，求解出 $\sum_{d|n}{C_{n}^{d}}\ mod \ P$ 。</span>**



---

<br/>


<br/>


<br/>



## 多重集的计数

**多重集的排列数**

假设多重集中有 $k$ 类元素，集合大小为 $n$ ， 每类元素数量分别为 $n_1,n_2,n_3,..,n_k$ ，则集合的全排列数：

$$
\frac{n!}{n_1!\times n_2!\times ...\times n_k!}
$$

**多重集的组合数**

对于集合 $S=\left\{ n_1\times a_1, n_2\times a_2,..., n_k\times a_k \right\}$ ，求从 $S$ 中取出 $r$ 个元素组成的多重集的数量

**先考虑 $r\le n_i, i\in \left[ 1, k \right]$ 的特殊情况**——此时问题等价于 $k-1$ 个 $1$ 把 $r$ 个 $0$ 分为 $k$ 组，每组的数量对应 从该组取出的元素数量。求 $r$ 个 $0$ ， $k-1$ 个 $1$ 组成的全排列：

$$
\frac{\left( r+k-1 \right) !}{r!\times \left( k-1 \right) !}=C_{r+k-1}^{k-1}
$$


**对于普遍的情况**，先不考虑 $n_i$ 的限制，相当于从集合 $\left\{ \infty a_1,\infty a_2,...,\infty a_k \right\}$ 中取出 $r$ 个元素，有 $C_{r+k-1}^{k-1}$ 种方法。

接下来剔除非法情况，对于 $a_i$ ，先选出 $n_i+1$ 个 $a_i$ ，再任选的 $r-n_i-1$ ，有 $C_{r+k-n_i-2}^{k-1}$ ，接下来根据容斥原理进行推导。最终合法的多重集数为：

$$
C_{r+k-1}^{k-1}-\sum_{i=1}^k{C_{r+k-n_i-2}^{k-1}}+\sum_{1\le i<j\le k}{C_{r+k-n_i-n_j-3}^{k-1}-....+\left( -1 \right) ^kC_{r+k-\sum_{i=1}^k{n_i-\left( k+1 \right)}}^{k-1}}
$$


---


<br/>


<br/>


<br/>


## Catalan 数列

给定 $n$ 个 $0$ 和 $n$ 个 $1$ ，按照某种顺序排成长度为 $2n$ 的序列，满足任意前缀中 $0$ 的个数不少于 $1$ 的个数的序列数量为：

$$
Cat_n=\frac{C_{2n}^{n}}{n+1}
$$

---


<br/>


<br/>


<br/>


<br/>


# 容斥原理 & Mobius 函数

## 容斥原理

设 $S_1,S_2,...,S_n$ 为有限集合，则

$$
|\underset{i=1}{\overset{n}{\cup S_i}}|=\sum_{i=1}^n{|S_i|-\sum_{i\le i<j\le n}{|S_i\cap S_j|}+...+\left( -1 \right) ^{n+1}|S_1\cap S_2\cap ...\cap S_n|}
$$


组合计数中多重集合的组合数的求法，就是使用容斥原理求出不合法的求法的数量。

### 例题

[**214. Devu和鲜花 - AcWing题库**](https://www.acwing.com/problem/content/216/)


本题是经典的多重集组合计数问题。由于本题中 $k+r-1$ 的数量级达到 $10^{14}$ ，同时 $p$ 的数量级为 $10^9$ ，但是 $k-1$ 的数量级很小，所以计算组合数时，采用以下公式：

$$
C_{n}^{m}=\frac{n\times \left( n-1 \right) \times ...\times \left( n-m+1 \right)}{n!}
$$

同时可以使用卢卡斯定理，避免在计算组合数的分子时 64 位整数溢出。

在实现容斥原理时，可以**进行二进制枚举** $x\in [0,2^n-1]$ 。


---


<br/>


<br/>


<br/>


## 莫比乌斯函数

将正整数 $N$ 按照算术基本定理分解质因数 $N=p_1^{c_1}\times p_2^{t_2}\times...\times p_m^{t_m}$ ，莫比乌斯函数定义为：

$$
\mu \left( N \right) =\left\{ \begin{array}{l}
	0\ ,\ \exists i\in \left[ 1,m \right] \ c_i>1\\
	1\ ,\ m\equiv 0\left( mod\ 2 \right)\\
	-1,\ m\equiv 1\left( mod\ 2 \right)\\
\end{array} \right. 
$$

计算一个数的莫比乌斯函数时，直接分解质因数即可。

当需要计算 $1$ 到 $N$ 中每一个数的莫比乌斯函数，使用埃氏筛进行计算：
- 初始化所有 $\mu$ 值为 $1$ 。
- 筛出每一个质数 $p$ ，对于 $p$ ，令 $x=2p,3p,...\lfloor \frac{n}{p} \rfloor \times p$ ，**<span style="background:#fff88f">检查 $x$ 能否被 $p^2$ 整除</span>**，如果能令 $\mu(x)=0$ ，否则令 $\mu(x)=-\mu(x)$ 。



### 例题

[**215. 破译密码 - AcWing题库**](https://www.acwing.com/problem/content/217/)

本题可以转化为 **<span style="background:#fff88f">$x\le a/d$ ， $y\le b/d$ ，有多少对 $x,y$ 互质</span>**。

设 $D[a,b,k]$ 表示 $a\le a,y\le b$ 中有多少对 $x,y$ 满足 $gcd(x,y)$ 是 $k$ 的倍数，显然只要 $x,y$ 都是 $k$ 的倍数即可，一共有 $\lfloor \frac{a}{k} \rfloor \times \lfloor \frac{b}{k} \rfloor$ 对。

设 $F[a,b]$ 表示 $x\le a$ ， $y\le b$ ，有多少对 $x,y$ 互质。由容斥原理可以得：

$$
F\left[ a,b \right] =\sum_{i=1}^{\min \left( a,b \right)}{\mu \left( i \right) \times D\left[ a,b,i \right]}
$$

对上式子的解释，当没有任何限制时，二元组对数为 $D[a,b,1]$ ，接下来需要剔除 $gcd(x,y)$ 是 $2,3,5,7,11,13,...$ 倍数的情况，这样会重复剔除 $gcd(x,y)$ 既是 2 的倍数，又是 3 的倍数的情况，所以需要加回来，可以看出 $D[a,b,i]$ 的系数正好是莫比乌斯函数。

在实现时，由于 $\forall i\ \in \ \left[ x\ ,\ \min \left ( \lfloor \frac{a}{\lfloor \frac{a}{x} \rfloor} \rfloor ,\lfloor \frac{b}{\lfloor \frac{b}{x} \rfloor} \rfloor \right) \right]$ ， $D[a,b,i]$ 的值是相等的，所以可以先预处理出莫比乌斯函数的前缀和，直接累加这一段答案。

----


<br/>


<br/>


<br/>


<br/>


# 概率与数学期望

概率和数学期望的定义不再赘述。

数学期望是线性函数，满足 $E\left ( aX+bY \right) =aE\left ( X \right) +bE\left ( Y \right)$ 。

### 例题

[**216. Rainbow的信号 - AcWing题库**](https://www.acwing.com/problem/content/218/)

根据题目中的选法，对于 $l = r$ 的情况，被选中的概率为 $\frac{1}{n^2}$ ，其余情况为 $\frac{2}{n^2}$ ，如果直接枚举区间进行计算的话，时间复杂度为 $O(N^2)$ 。

<span style="background:#fff88f">**位运算是不进位的，所以可以单独考虑每一个位对答案的贡献** </span>。对于 and 和 or 运算，记录上一次出现 1 或 0 的位置，可以分方便的统计出符合要求的左端点的数量。对于 xor 运算，根据异或运算的性质，可以计算一个前缀和，同时统计前缀和为 1 或者为 0 的数量。

```cpp
// 计算第k位对答案贡献
void cal(int k) {
    int last[2]{0, 0};
    double w = (double)(1 << k) / n / n;

    int x = 0;
    int last0 = 0 ,c0 = 1;  // 注意此处赋值
    int last1 = -1,c1 = 0;

    for (int i = 1; i <= n; ++i) {
        int b = (a[i] >> k) & 1;
        // ....省略其余计算内容

        x ^= b;
        if (x) {
			// 剔除区间长度为1的情况（前面已经计算过）
            ansxor += w * 2 * (last0 == i - 1 ? c0 - 1 : c0);
            ++c1;
            last1 = i;
        } else {
            ansxor += w * 2 * (last1 == i - 1 ? c1 - 1 : c1);
            ++c0;
            last0 = i;
        }
    }
}
```


如果是求**最大子区间异或和**问题，可以使用 xor 的前缀树解决。



<br/>


[**217. 绿豆蛙的归宿 - AcWing题库**](https://www.acwing.com/problem/content/219/)

设 $F[x]$ 为节点 $x$ 走到终点所经过路径的期望长度，假设从 $x$ 出发有 $k$ 条路径，则有

$$
F\left[ x \right] =\frac{1}{k}\sum_{i=1}^k{\left( F\left[ y_i \right] +z_i \right)}
$$

显然，要想计算 $x$ 必须先计算所有在 $x$ 之后的节点，所以可以建立反向图，进行拓扑排序。一边拓扑排序，一边更新答案。


<br/>


[**218. 扑克牌 - AcWing题库**](https://www.acwing.com/problem/content/220/)

数学期望结合动态规划的题目。

设 $F[a,b,c,d,x,y]$ 表示已经翻开 $a$ 张黑桃、 $b$ 张红桃、 $c$ 张梅花
$d$ 张方块， $x$ 表示用小王代替哪一张牌 ，还需要翻开的牌数的期望。

边界状态为翻开的牌数已经符合要求，目标状态是求 $F[0,0,0,0,4,4]$ 。在数学期望递推、数学期望动态规划中，通常把终止状态作为初值（边界），把起始状态作为目标（要计算的）。

另外本题使用记忆化搜索解决，有以下技巧：
- 当状态数量较大，但是每一个维度的尺度较小时，适合使用数组存储结果。
- 当状态数量不太多，但是每一个维度的尺度很大，并且分布很广泛时，适合使用哈希表记录结果。

---


<br/>


<br/>


<br/>


<br/>


# 0/1 分数规划

0/1 分数规划模型——给定 $n$ 对整数 $a_i,b_i$ ，从中选出若干对，使得选出数对的 $a$ 之和和 $b$ 之和的商最大。


如果存在一组解使得 $\sum_{i=1}^n{\left( a_i-L\times b_i \right)}\times x_i\ge 0\ \ \ ,(x_i=0\text{或}1)$ ，那么有

$$
\frac{\sum_{i=1}^n{a_i\times x_i}}{\sum_{i=1}^n{b_i\times x_i}}\ge L
$$


所以可以进行实数的二分寻找答案。

### 例题

[**234. 放弃测试 - AcWing题库**](https://www.acwing.com/problem/content/236/)

0/1 分数规划题目的基础上限制了最少需要选取的数的对数。

在进行判断时，对 $a_i-L\times b_i$ 进行排序，优先选择数值最大的。


----



<br/>


<br/>


<br/>


<br/>


# SG 函数

**NIM 博弈**

给定 $n$ 堆物品，第 $i$ 堆物品有 $A_i$ 个。两名玩家轮流行动，每次可以任选一堆，取走任意多的物品（但是不能不取）。取走最后一件物品的玩家获胜。

尼姆博弈不存在平局，只有先手必胜和先手必败的情况。

**尼姆博弈先手必胜，当且仅当 $A_1\ xor\ A_2\ xor\ ...\ xor\ A_n\ \ne \ 0$** 。当所有物品都被取走时，此时必败，所有 $A_i$ 都是 $0$ ，异或的结果为 $0$ 。 当 $A_1\ xor\ A_2\ xor\ ...\ xor\ A_n\  =x \ \ne \ 0$ 时，可以在最大的一堆中选出若干个物品，使得该堆剩余 $A_i\ xor \ x$ 个物品，下一个局面则必败。


<br/>


**公平组合游戏 ICG**

- 两名玩家交替行动
- 任意时刻，可以执行的合法动作与轮到哪一个玩家无关
- 不能行动的玩家判负

NIM 博弈俗语公平组合游戏。


<br/>


**有向图游戏**

任何一个公平组合游戏都可以转化为有向图游戏。把每个局面看作是图中的一个节点。


<br/>


**Mex 运算**

$mex(S)$ 为不属于集合 $S$ 的最小非负整数。


<br/>


**SG 函数**

在有向图游戏中，对于节点 $x$ ，设从 $x$ 出发有 $k$ 条边，分别到达 $y_1,y_2,...,y_k$ ，则

$$
SG\left( x \right) =mex\left\{ SG\left( y_1 \right) ,SG\left( y_2 \right) ,...,SG\left( y_k \right) \right\} 
$$

有向图游戏的 $SG$ 值定义为游戏起点的 $SG$ 函数值。

对于多个有向图游戏，他们的和的 $SG$ 函数值定义为各个子游戏的 $SG$ 函数值的异或和。


- 有向图游戏某个局面 $x$ 必胜，当且仅当 $SG(x)>0$ 。
- 有向图游戏某个局面 $x$ 必败，当且仅当 $SG(x)=0$ 。


<br/>

### 例题

[**219. 剪纸游戏 - AcWing题库**](https://www.acwing.com/problem/content/221/)

剪纸游戏盒有向图游戏有些不同，需要重新定义不能行动的局面。在本题中，必胜局面是出现 $1\times X$ 或 $X\times 1$ 规格的剪纸，采取最优策略行动，所以两人必定不会剪出这样的规格给对手。

所以， $1\times X$ 或 $X\times 1$ 规格的剪纸只能从 $2\times 2,2\times 3,3\times 2$ 这三种规格中得到，可以将其定义为必败局面，即 $sg$ 函数值为 $0$ 。

可以枚举剪的位置（哪一行或者哪一列），不同的减法可以转移到不同的局面，对所有可以转移到局面组成的集合进行 $mex$ 运算，而对于一个特定的剪法（特定的一个局面），会分为两个部分，两个部分视为子游戏，执行 $xor$ 运算。

---