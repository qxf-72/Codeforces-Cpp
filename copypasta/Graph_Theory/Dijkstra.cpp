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

struct Node {
    int v, d;
    Node(int v, int d)
        : v(v), d(d){}
    bool operator<(const Node& obj) const
    {
        return d > obj.d;
    }
};
int dis[N + 1];
void dijkstra(int s)
{
    memset(dis, 0x3f, sizeof dis);
    dis[s] = 0;
    vector<bool> v(N + 1); // 标记节点是否被拓展过，节点最多拓展一次
    priority_queue<Node> que;
    que.emplace(s, 0);
    while (!que.empty()) {
        auto cur = que.top();
        que.pop();
        // 节点被拓展过
        if (v[cur.v])
            continue;
        v[cur.v] = true;
        for (auto [nxt, d] : g[cur.v]) {
            if (dis[nxt] > dis[cur.v] + d) {
                dis[nxt] = dis[cur.v] + d;
                que.emplace(nxt, dis[nxt]);
            }
        }
    }
}

int main()
{
    return 0;
}
