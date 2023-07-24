template<typename T>
class SegmentTree {
private:
    int n = 1;
    vector<T> tree;
    vector<T> *arr;

    void build(int k) {
        if (k >= n - 1) {
            if (k - n + 1 < arr->size())
                tree[k] = (*arr)[k - n + 1];
            else {
                // do something
                // 由不会影响结果的值填充到空白节点
            }
            return;
        }
        build(2 * k + 1);
        build(2 * k + 2);
        // do something
        //由tree[2*k+1]和tree[2*k+2]的值得到tree[k]
    }

    T query(int a, int b, int k, int l, int r) {
        if (r <= a || b <= l) {
            //return something
            //返回一个不会影响结果的值
        }
        if (a <= l && b >= r) return tree[k];
        T v_l = query(a, b, k * 2 + 1, l, (l + r) / 2);
        T v_r = query(a, b, k * 2 + 2, (l + r) / 2, r);
        //return something
        //返回的值由左右两边得到
    }

public:
    SegmentTree<T>() = default;

    explicit SegmentTree<T>(vector<T> *arr) : arr(arr) {
        while (n < arr->size())
            n *= 2;
        tree.resize(2 * n - 1);
        build(0);
    }

    void update(int k, T a) {
        k += n - 1;
        tree[k] = a;
        while (k > 0) {
            k = (k - 1) / 2;
            // do something
            // 由tree[2*k+1]和tree[2*k+2]的值得到tree[k]
        }
    }

    T query(int a, int b) {
        return query(a, b, 0, 0, n);
    }

    SegmentTree<T> &operator=(const SegmentTree<T> &segmentTree) {
        if (this == &segmentTree)
            return *this;
        n = segmentTree.n;
        arr = segmentTree.arr;
        tree = std::move(segmentTree.tree);
        return *this;
    }
};