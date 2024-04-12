#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

const int N = 1000;
vector<pair<int, int>> g[N + 1];
int dis[N + 1];

void spfa(int s)
{
    memset(dis, 0x3f, sizeof dis);
    dis[s] = 0;
    vector<bool> v(N + 1); // 标记节点当前是否在队列中
    v[s] = true;
    queue<int> que;
    que.push(s);
    while (!que.empty()) {
        int x = que.front();
        v[x] = false;
        que.pop();
        for (auto [y, d] : g[x]) {
            if (dis[x] + d < dis[y]) {
                dis[y] = dis[x] + d;
                if (!v[y])
                    que.push(y), v[y] = true;
            }
        }
    }
}

int main()
{
    return 0;
}
