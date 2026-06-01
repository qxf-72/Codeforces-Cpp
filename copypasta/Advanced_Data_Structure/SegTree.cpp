#include <cassert>
#include <vector>

template <typename T>
class SegTree {
private:
    int n;
    std::vector<T> tree;

    void build(int k, int l, int r, const std::vector<T>& a) {
        if (l == r) {
            tree[k] = a[l];
            return;
        }

        int mid = (l + r) >> 1;
        build(k * 2 + 1, l, mid, a);
        build(k * 2 + 2, mid + 1, r, a);

        tree[k] = tree[k * 2 + 1] + tree[k * 2 + 2];
    }

    void add(int k, int l, int r, int pos, T val) {
        if (l == r) {
            tree[k] += val;
            return;
        }

        int mid = (l + r) >> 1;
        if (pos <= mid) {
            add(k * 2 + 1, l, mid, pos, val);
        } else {
            add(k * 2 + 2, mid + 1, r, pos, val);
        }

        tree[k] = tree[k * 2 + 1] + tree[k * 2 + 2];
    }

    void setValue(int k, int l, int r, int pos, T val) {
        if (l == r) {
            tree[k] = val;
            return;
        }

        int mid = (l + r) >> 1;
        if (pos <= mid) {
            setValue(k * 2 + 1, l, mid, pos, val);
        } else {
            setValue(k * 2 + 2, mid + 1, r, pos, val);
        }

        tree[k] = tree[k * 2 + 1] + tree[k * 2 + 2];
    }

    T query(int k, int l, int r, int ql, int qr) const {
        if (ql <= l && r <= qr) {
            return tree[k];
        }

        int mid = (l + r) >> 1;
        T res = T{};

        if (ql <= mid) {
            res += query(k * 2 + 1, l, mid, ql, qr);
        }
        if (qr > mid) {
            res += query(k * 2 + 2, mid + 1, r, ql, qr);
        }

        return res;
    }

public:
    explicit SegTree(const std::vector<T>& a) {
        n = (int)a.size();
        assert(n > 0);

        tree.assign(4 * n, T{});
        build(0, 0, n - 1, a);
    }

    // a[pos] += val
    void add(int pos, T val) {
        assert(0 <= pos && pos < n);
        add(0, 0, n - 1, pos, val);
    }

    // a[pos] = val
    void setValue(int pos, T val) {
        assert(0 <= pos && pos < n);
        setValue(0, 0, n - 1, pos, val);
    }

    // 查询闭区间 [l, r] 的和
    T query(int l, int r) const {
        assert(0 <= l && l <= r && r < n);
        return query(0, 0, n - 1, l, r);
    }
};