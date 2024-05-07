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

---

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
- 若 $p|n$ 且 $p^2|n$ ，则 $\varphi \left( n \right) =\varphi \left( \frac{n}{p} \right) \times p$ 。 **$p$ 为质数**。

- 若 $p|n$ 且 $p^2$ 不能给你整除 $n$ ，则 $\varphi \left( n \right) =\varphi \left( \frac{n}{p} \right) \times (p-1)$ 。
- $\sum_{d|n}{\varphi \left ( d \right)}=n$


### 例题


[**201. 可见的点 - AcWing题库**](https://www.acwing.com/problem/content/203/)

除了（1,0）、（0,1）和（1,1）这三个钉子以外，一个钉子（x，y）能被看见当且仅当， $1\le x,y \le N$ 并且 $gcd(x,y)=1$ （否则就会被前面的钉子挡住）。由于对称，只考虑上面部分，对于每个 $y$ ，求出 $\varphi (y)$ 。

利用埃氏筛，在 $O(N\times log(log N))$ 求出 2 到 $N$ 每个数的欧拉函数：
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

同样的，可以利用线性筛和欧拉函数性质，在 $O(n)$ 时间求解：

```cpp
void euler(int n)
{
	memset(v, 0, sizeof v);
    int m = 0;
    for (int i = 2; i <= n; ++i) {
        if (v[i] == 0) {
            v[i] = i;
            prime[++m] = i;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= m; ++j) {
            if (prime[j] > v[i] || prime[j] * i > n)
                break;
            v[i * prime[j]] = prime[j];
            phi[i * prime[j]] = phi[i] * (i % prime[j] ? prime[j] - 1 : prime[j]);
        }
    }
}

```


---


<br/>


<br/>


<br/>


<br/>


# 同余

## 欧拉定理

### 剩余系
- 同余类：模 m 余数相同的一类整数。
- **完全剩余系**：模 m 的 m 个同余类构成完全剩余系。
- **简化剩余系**：1 到 m 中与 m 互质的 $\varphi (N)$ 个数代表的同余类构成简化剩余系。**简化剩余系关于模 m 乘法封闭**。设 n 的简化剩余系为 $\left\{ a_1, a_2,..., a_{\varphi \left ( n \right)} \right\}$ ，则，**当 $a_i \ne a_j$ 并且 $a$ 与 $p$ 互质 时， $aa_i$ 和 $aa_j$ 代表不同的同余类**。


<br/>

### 费马小定理

**$p$ 为质数**，对于任意整数 $a$，有 $a^{p-1}\equiv 1(mod \ p)$ 。


<br/>

### 欧拉定理

**$a$ 与 $n$ 互质**，则 $a^{\varphi (n)} \equiv 1\ (mod\ n)$ 。可以看出，费马小定理是欧拉定理的特殊情况。


<br/>

### 拓展欧拉定理

弱化了欧拉定理条件，不需要 $a$ 和 $n$ 互质，对于任意整数 $b$ 有，

$$
a^b\equiv \left\{ \begin{array}{l}
	a^b\ ,\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ b<\varphi \left( n \right) \ \left( mod\ n \right)\\
	a^{b\ mod\ \varphi \left( n \right) \ +\ \varphi \left( n \right)}\ ,\ b\ge \varphi \left( n \right) \ \left( mod\ n \right)\\
\end{array} \right. 
$$

特别的，如果 $a$ 和 $n$ 互质，则 $a^b\equiv \ a^{b\ mod\ \varphi \left ( n \right)}\ \left ( mod\ n \right)$ 。

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


## 拓展欧几里得算法

### 裴蜀定理

对于不全为零的任意整数 $a$ 和 $b$  ，则对于任意整数 $x$ 和 $y$ 都满足 $a\times x+b \times y$ 是 $gcd(a,b)$ 的倍数。**并且 $a\times x+b \times y$ 的最小正整数为 $gcd(a,b)$  。**

假设 $a\times x+b \times y=s$ ，当 $gcd(a,b)$ 不能整除 $s$ 时，方程无整数解。


<br/>

### 裴蜀定理推广

一定存在一组整数 $x_1,x_2,...,x_n$ ，满足 $\sum_{i=1}^n{a_i\times x_i}=s$ ，其中 $gcd\left ( a_1, a_2,..., a_n \right)|s$ 。 


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

---


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

其中模数 $m_1,m_2,...,m_n$ **两两互质**。求 $x$ 最小非负整数解。

中国剩余定理 CRT 求解步骤如下
- 计算所有模数的积 $M$
- 计算第 $i$ 个方程的 $c_i=\frac{M}{m_i}$
- 计算 $c_i$ 模 $m_i$ 的乘法逆元 $c_i^{-1}$

$x=\sum{c_i\times c_i^{-1}\times r_i}$ 。

```cpp
int exgcd(long long a, long long b, long long &x, long long &y) {
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


<br/>


### 拓展中国剩余定理

当线性同余方程组中的模 $m_i$ 不能保证两两互质时，不能使用 CRT 算法求解。

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

由裴蜀定理，当且仅当 $gcd(m_1,m_2)|r_2-r_1$ 时有解。在有解的情况下，


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




---


<br/>


<br/>


## 高次同余方程


---