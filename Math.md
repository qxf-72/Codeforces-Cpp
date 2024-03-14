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