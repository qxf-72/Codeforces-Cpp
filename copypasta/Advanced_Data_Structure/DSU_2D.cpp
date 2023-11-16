class DSU
{
private:
    int n;
    vector<vector<int>> height, size;
    vector<vector<pair<int, int>>> pa;
    
public:
    explicit DSU(int n) : n(n), pa(n, vector<pair<int, int>>(n)), height(n, vector<int>(n)), size(n, vector<int>(n, 1))
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                pa[i][j] = {i, j};
            }
        }
    }

    pair<int, int> find(int x, int y)
    {
        if (pa[x][y] == make_pair(x, y))
            return {x, y};
        return pa[x][y] = find(pa[x][y].first, pa[x][y].second);
    }

    int getUnionSize(int x, int y)
    {
        auto [px, py] = find(x, y);
        return size[px][py];
    }

    void unite(int x1, int y1, int x2, int y2)
    {
        auto [px1, py1] = find(x1, y1);
        auto [px2, py2] = find(x2, y2);
        if (px1 == px2 && py1 == py2)
            return;
        if (height[px1][py1] < height[px2][py2])
        {
            pa[px1][py1] = {px2, py2};
            size[px2][py2] += size[px1][py1];
        }
        else
        {
            if (height[px1][py1] == height[px2][py2])
                ++height[px1][py1];
            pa[px2][py2] = {px1, py1};
            size[px1][py1] += size[px2][py2];
        }
    }
};