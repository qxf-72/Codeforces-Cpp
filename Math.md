# 质数

## 分解质因数

不必先求出质数集合，再进行分解。

直接从 2（最小的质数）开始试除，直到 `i*i>n`。分解结束之后，如果 余数大于 1，说明 n 有大于 $\sqrt{n}$ 的因数（并且是唯一的）。

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


> C++17 提供了两个模板函数求最小公倍数和最大公约数—— `gcd` 和 `lcm`

## 裴蜀定理

对于不全为零的任意整数 $a$ 和 $b$ ，记 $g=gcd⁡(a, b)$ ，则对于任意整数 $x$ 和 $y$ 都满足 $a\times x+b \times y$ 是 $g$ 的倍数，特别地，存在整数 $x$ 和 $y$ 满足 $a \times x + b \times y = g$ 。

### 例题

[1250. 检查「好数组」 - 力扣（LeetCode）](https://leetcode.cn/problems/check-if-it-is-a-good-array/description/)
从头开始遍历数组，一旦前 i 个数的最大公约数为 1，就提前跳出循环。为什么不枚举子集进行判定？因为数越多，越能使 gcd 向 1 靠近，正好符合题目要求，所以直接遍历整个数组判定。

---