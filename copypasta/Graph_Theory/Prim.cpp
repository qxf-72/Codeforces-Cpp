#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

const int N = 1000;

int g[N][N]; // 邻接矩阵
int dis[N], n, m, ans;

void prim()
{
    memset(dis, 0x3f, sizeof dis);
    vector<bool> v(N); // 标记节点是否加入MST集合

    dis[1] = 0;
    for (int i = 1; i <= n; ++i) {
        int x = 0; // 选出要加入MST的节点
        for (int j = 1; j <= n; ++j)
            if (!v[j] && (x == 0 || dis[j] < dis[x]))
                x = j;
        ans += dis[x];
        v[x] = true;
        // 更新dis数组
        for (int y = 1; y <= n; ++y)
            if (!v[y])
                dis[y] = min(dis[y], g[x][y]);
    }
}

int main()
{
    return 0;
}
