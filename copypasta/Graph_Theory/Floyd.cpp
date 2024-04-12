#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

const int N = 1000;
vector<pair<int, int>> g[N + 1];
int dis[N + 1][N + 1];

void folyd()
{
    memset(dis, 0x3f, sizeof dis);
    for (int i = 1; i <= N; ++i)
        dis[i][i] = 0;
    for (int i = 1; i <= N; ++i)
        for (auto [j, d] : g[i])
            dis[i][j] = min(dis[i][j], d); // 可能存在平行边

    for (int k = 1; k <= N; ++k) {
        for (int i = 1; i <= N; ++i)
            for (int j = 1; j <= N; ++j)
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
    }
}

int main()
{
    return 0;
}
