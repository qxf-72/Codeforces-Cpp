#include<bits/stdc++.h>
using namespace std;

// T一般设置为int，并查集较大时可以设置更大的类型
template <typename T>
class DSU
{
private:
    T n;
    vector<T> pa, height, size; // 父节点  树的高度  集合大小

public:
    explicit DSU(T n) : n(n), pa(n), height(n), size(n, 1)
    {
        iota(pa.begin(), pa.end(), 0);
    }
    // 查询父节点
    T find(T x)
    {
        if (pa[x] == x)
            return x;
        return pa[x] = find(pa[x]);
    }
    // 当前所在集合的大小
    T getUnionSize(int x)
    {
        x = find(x);
        return size[x];
    }
    // 合并操作
    void unite(T x, T y)
    {
        x = find(x);
        y = find(y);
        if (x == y)
            return;
        // 合并时，利用树的高度，或者集合的大小，进行启发式合并
        if (height[x] < height[y])
        {
            pa[x] = y;
            size[y] += size[x];
        }
        else
        {
            if (height[x] == height[y])
                ++height[x];
            pa[y] = x;
            size[x] += size[y];
        }
    }
};