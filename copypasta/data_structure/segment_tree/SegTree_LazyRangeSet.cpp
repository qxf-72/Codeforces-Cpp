template<typename T>
class SegTree_LazyRangeSet {
private:
    vector<T> &arr;
    vector<T> tree;
    vector<T> lazy;
    int n=1;

    void maintain(int l, int r, int k) {
        int mid = (l + r) / 2;
        if (k < n - 1 && lazy[k]) {
            lazy[2 * k + 1] = lazy[k];
            lazy[2 * k + 2] = lazy[k];
            tree[2 * k + 1] = lazy[k] * (mid - l);
            tree[2 * k + 2] = lazy[k] * (r - mid);
            lazy[k] = 0;
        }
    }

    void range_set(int a, int b, T val, int k, int l, int r) {
        if (r <= a || b <= l) return;
        if (a <= l && b >= r) {
            lazy[k] = val;
            tree[k] = (r - l) * val;
            return;
        }
        int mid = (l + r) / 2;
        maintain(l, r, k);
        range_set(a, b, val, 2 * k + 1, l, mid);
        range_set(a, b, val, 2 * k + 2, mid, r);
        tree[k] = tree[2 * k + 1] + tree[2 * k + 2];
    }

    //查询区间[a,b) : k为当前区间对应的节点的下标,初始设为0;[l,r)为当前区间，初始为[0,n)
    T query(int a, int b, int k, int l, int r) {
        if (r <= a || b <= l) return 0;
        if (a <= l && b >= r) return tree[k];
        else {
            maintain(l, r, k);
            int v_l = query(a, b, k * 2 + 1, l, (l + r) / 2);
            int v_r = query(a, b, k * 2 + 2, (l + r) / 2, r);
            return v_l + v_r;
        }
    }

    void build(int k){
        if(k>=n-1){
            tree[k]=k-n+1>=arr.size()?0:arr[k-n+1];
            return;
        }
        build(2*k+1);
        build(2*k+2);
        tree[k]=tree[2*k+1]+tree[2*k+2];
    }

public:
    SegTree_LazyRangeSet<T> () = default;
    explicit SegTree_LazyRangeSet<T>(vector<T>& arr):arr(arr){
            n = 1;
            while (n < arr.size()) n *= 2;
            tree.resize(2 * n - 1);
            lazy.resize(2 * n - 1);
            build(0);
    }
//    void init(int n_) {
//        //n_为元素数量，但是为了便于处理，将其元素个数扩大到2的幂
//        n = 1;
//        while (n < n_) n *= 2;
//        tree.resize(2 * n - 1);
//        lazy.resize(2 * n - 1);
//        for (int i = 0; i < 2 * n - 1; ++i) tree[i] = 0;
//    }

    //把第k(0开始)个值更新
    void update(int k, T a) {
        k += n - 1;
        tree[k] = a;
        while (k > 0) {
            k = (k - 1) / 2;
            tree[k] = tree[2 * k + 1] + tree[2 * k + 2];
        }
    }

    T query(int a, int b) {
        return query(a, b, 0, 0, n);
    }

    void range_set(int a,int b ,T val){
        range_set(a,b,val,0,0,n);
    }
};