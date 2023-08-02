//T一般设置为int,并查集较大时可以设置为size_t
template<typename T>
class DSU {
private:
    vector<T> pa, height, size;
    //父节点  树的高度  集合大小
    T n;
public:
    explicit DSU(T n) : n(n), pa(n), height(n), size(n, 1) {
        iota(pa.begin(), pa.end(), 0);
    }

    T find(T x) {
        if (pa[x] == x)
            return x;
        return pa[x] = find(pa[x]);
    }

    T getUnionSize(int x) {
        x = find(x);
        return size[x];
    }

    void unite(T x, T y) {
        x = find(x);
        y = find(y);
        if (x == y) return;
        //合并时,即可用树的高度,也可以用集合的大小进行 启发式合并
        if (height[x] < height[y]) {
            pa[x] = y;
            size[y] += size[x];
        } else {
            if (height[x] == height[y])
                ++height[x];
            pa[y] = x;
            size[x] += size[y];
        }
    }
};