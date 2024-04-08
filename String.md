# KMP

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


<br/>


<br/>


<br/>


<br/>


# 字符串 Hash

将一个任意长度的字符串映射为非负整数，冲突概率几乎为 0。具体做法——将字符串看作是一个 P 进制数，求出这个数，然后对 M 取余。
- P 通常取 **131** 或 **13331**。
- M 通常取 $2^{64}$ ，直接使用 **unsigned long long** 存储这个数，高位自动对齐，不用取余操作。

除了特殊构造的字符串，该哈希很难产生冲突。为了将冲突的可能性再次降低，可以多取几个不同的 P 和 M，结果都相同时，才认为字符串相等。

字符串 Hash 的主要用处是——进过 O (N) 时间预处理后，可以 **以 O (1) 时间查询任意子字符串的哈希值**。
- $H(S+c)=(H(S)*P+value(c))\  \% \  M$
- $H(T)=(H(S+T)-H(S)^{len(T)}) \  \%  \ M$

为了降低计算复杂度，P 的次方也可以预处理保存到一个数组里面。

### 模板代码

[**StringHash.cpp**](/copypasta/String/StringHash.cpp) 

模板类在初始化时，可以设置 P，方便进行**双哈希**验证。默认 s 下标从 0 开始，并且只有小写字母，默认 query 下标从 1 开始。


### 相关题目

[138. 兔子与兔子 - AcWing题库](https://www.acwing.com/problem/content/140/)

[139. 回文子串的最大长度 - AcWing题库](https://www.acwing.com/problem/content/141/)

---


<br/>


<br/>


<br/>


<br/>


# 前缀树 Tire

Tire 的本质，就是利用字符串之间的公共前缀，将重复的前缀合并在一起。

树中存储着一些单词的所有字母，每个节点代表一个字母，其中可以另外保存一些状态，比如是否有单词以该字母为结尾。可用于高效判断一个字符串是否存在于一组字符串集合中，或者作为字符串集合中某个字符串的前缀。

### 模板代码

[**Tire.cpp**](/copypasta/String/Tire.cpp)

Tire 类是典型的前缀树，实现的功能：判断字符串集合中是否存在一个字符串，prefix 是否是字符串集中某个字符串的前缀，统计字符串集合中有多少个字符串是 str 的前缀。

[**Tire.cpp**](/copypasta/String/TireXor.cpp)

**前缀树拓展应用**，将 32 位整数集合存入树中，用于**求解最大异或对问题**。


### 例题


[142. 前缀统计 - AcWing题库](https://www.acwing.com/problem/content/description/144/)

[143. 最大异或对 - AcWing题库](https://www.acwing.com/problem/content/145/) Tire 的拓展应用。

[144. 最长异或值路径 - AcWing题库](https://www.acwing.com/problem/content/146/) 可以转化为**最大异或对**问题求解。

---


<br/>


<br/>


<br/>


<br/>



# Manacher 算法

对于一个字符串 S ，如果要求其连续回文子串的最长长度，朴素做法是枚举中心，时间复杂度为 $O(N^2)$ 。

Manacher 算法时可以在线性时间复杂度内，求出以每一个字符（或者是两个相邻字符）为中心的最长回文字符串的长度。核心是维护三个关键变量：
- cur （遍历到的当前位置）
- center（当前可以覆盖到 cur 的最长回文串的中心）
- right（最长回文字符串的右边界） 
- dp[ cur ] ：以 cur 为中心，能够往一边能够拓展的步数

对于 cur，求出其关于 center 的镜像位置 cur ' ，则以 dp[cur] 最小值为 ：`min(dp[cur'],right-i)`。确定最小边界之后，需要根据字符情况拓展边界，之后根据情况更新 center 和 right 。

### 模板代码

[**Manacher.cpp**](/copypasta/String/Manacher.cpp)


---


<br/>


<br/>


<br/>


<br/>




# 最小表示法

给定一个字符串 S[1-n] ，如果不断把最后一个字符放在开头，可以得到 n 个字符串——称这 n 个字符串是**循环同构**的。其中字典序最小的字符串成为 S 的**最小表示法**。

要求字符串 S 的最小表示法，朴素的做法是一个一个进行比较，时间复杂度是 $O (N^2)$。

存在时间复杂度 $O(N)$ 的做法——将两个 S 拼接到一起，形成字符串 SS 。设 $B[i] = SS[i~i+n-1]$ ，可以设 $i=1，j=2$ ，从头开始比较，如果字符相等则继续比较下一位，当字符不相等时，**假设 $SS[i+k] > SS[j+k]$ ，则 $B[i] ，B[i+1]，...，B[i+k]$ 都不可能是最小表示法**，因为存在对应的   $B[j] ，B[j+1]，...，B[j+k]$ 比他小。

**算法流程**
-  初始令 $i=1，j=2$
- 从前往后进行扫描，比较 $B[i]$ 和 $B[j]$ ：
	- 如果扫描了 n 个字符都相等，说明 S 只由一个字符构成。
	- 如果 $SS[i+k] > SS[j+k]$ ，令 $i=i+k+1$ ，如果 $i=j$ ，则 $i=i+1$ 。
	- 如果 $SS[i+k] < SS[j+k]$ ，令 $j=j+k+1$ ，如果 $i=j$ ，则 $j=j+1$ 。
- 最后如果 $i>n$ ，则 $B[j]$ 是最小表示法；否则 $B[i]$ 是最小表示法。

```cpp
void minimalist_representation()  
{  
    int n = strlen(s + 1)  
    // 构造SS  
    for (int i = 1; i <= n; ++i)  
       s[i + n] = s[i];  
    int i, j, k;  
    for (i = 1, j = 2, k; i <= n && j <= n;)  
    {  
       for (int k = 0; k <= n && s[i + k] == s[j + k]; ++k);  
       if (k == n)  
          break; // S只由一种字符构成  
       if (s[i + k] > s[j + k])  
       {  
          i = i + k + 1;  
          if (i == j) ++i;  
       }  
       else  
       {  
          j = j + k + 1;  
          if (j == i) ++j;  
       }  
    }  
    ans = min(i, j); //B[ans]是最小表示法  
}
```


---