#include <algorithm>
#include <iostream>
using namespace std;

const int N = 1000;

struct Edge {
    int u, v, w;
    Edge() = default;
    Edge(int u, int v, int w)
        : u(u), v(v), w(w){ }
    bool operator<(const Edge& obj) const
    {
        return w < obj.w;
    }
};

Edge edges[N];
// 并查集
int fa[N], sz[N];
int find(int x)
{
    if (x == fa[x])
        return x;
    return fa[x] = find(fa[x]);
}
void unite(int x, int y)
{
    x = find(x);
    y = find(y);
    if (x == y)
        return;
    if (sz[x] < sz[y]) {
        sz[y] += sz[x];
        fa[x] = y;
    } else {
        sz[x] += sz[y];
        fa[y] = x;
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; ++i)
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        
    // 边按权值排序
    sort(edges + 1, edges + m + 1);
    for (int i = 1; i <= n; ++i) {
        fa[i] = i;
        sz[i] = 1;
    }
    int ans = 0;
    // 从小到大选择边
    for (int i = 1; i <= m; ++i) {
        int x = find(edges[i].u);
        int y = find(edges[i].v);
        if (x == y)
            continue;
        ans += edges[i].w;
        unite(x, y);
    }
    return 0;
}
