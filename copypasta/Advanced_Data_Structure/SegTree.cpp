#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class SegTree {
    int n;
    vector<long long> data, lazy;
    vector<int>* arr;

    void build(int k, int a, int b)
    {
        if (a == b) {
            data[k] = (*arr)[a];
            return;
        }
        int mid = (a + b) / 2;
        build(2 * k + 1, a, mid);
        build(2 * k + 2, mid + 1, b);
        // 从下往上合并信息
        data[k] = data[2 * k + 1] + data[2 * k + 2];
    }
    void spread(int k, int a, int b)
    {
        if (lazy[k] != 0) {
            int mid = (a + b) / 2;
            data[2 * k + 1] += lazy[k] * (mid - a + 1);
            data[2 * k + 2] += lazy[k] * (b - mid);
            lazy[2 * k + 1] += lazy[k];
            lazy[2 * k + 2] += lazy[k];
            lazy[k] = 0;
        }
    }
    void update(int k, int a, int b, int l, int r, int e)
    {
        if (a >= l && b <= r) {
            data[k] += (long long)e * (b - a + 1);
            lazy[k] += e;
            return;
        }
        // 往下更新之前必须先向下传递延迟标记
        spread(k, a, b);
        int mid = (a + b) / 2;
        if (l <= mid)
            update(2 * k + 1, a, mid, l, r, e);
        if (r > mid)
            update(2 * k + 2, mid + 1, b, l, r, e);
        // // 返回一个不影响合并的数
        data[k] = data[2 * k + 1] + data[2 * k + 2];
    }
    long long query(int k, int a, int b, int l, int r)
    {
        if (a >= l && b <= r)
            return data[k];
        spread(k, a, b);
        int mid = (a + b) / 2;
        long long ret = 0;
        if (l <= mid)
            ret += query(2 * k + 1, a, mid, l, r);
        if (r > mid)
            ret += query(2 * k + 2, mid + 1, b, l, r);
        // 从下往上合并信息
        return ret;
    }

public:
    explicit SegTree(vector<int>* a)
        : arr(a)
    {
        n = (*a).size();
        data.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
        build(0, 0, n - 1);
    }

    void update(int l, int r, int e)
    {
        update(0, 0, n - 1, l, r, e);
    }
    long long query(int l, int r)
    {
        return query(0, 0, n - 1, l, r);
    }
};

int main()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    SegTree segTree = SegTree(&a);

    return 0;
}
