//该模板以维护区间和为例，当用于维护其他信息时，已将需要修改的地方标出
template<typename T>
class SegTree_LazyRangeAdd {
private:
    vector<T> *arr;
    vector<T> tree;
    vector<T> lazy;
    int n=1;
    //相当于push down操作,向下传递影响
    void maintain(int l, int r, int k) {
        int mid = (l + r) / 2;
        if (k < n - 1 && lazy[k]) {
            //######################################
            lazy[2 * k + 1] += lazy[k];
            lazy[2 * k + 2] += lazy[k];
            tree[2 * k + 1] += lazy[k] * (mid - l);
            tree[2 * k + 2] += lazy[k] * (r - mid);
            //######################################
            lazy[k] = 0;
        }
    }
    void range_add(int a, int b, T val, int k, int l, int r) {
        if (r <= a || b <= l) return;
        if (a <= l && b >= r) {
            lazy[k] += val;
            //######################################
            tree[k] += (r - l) * val;
            //######################################

            //懒惰标记以后,不再往下遍历,而是往上更新
            return;
        }
        int mid = (l + r) / 2;
        //遍历的同时,进行持久化,将懒惰标记落实
        maintain(l, r, k);
        range_add(a, b, val, 2 * k + 1, l, mid);
        range_add(a, b, val, 2 * k + 2, mid, r);

        //往上更新
        //######################################
        tree[k] = tree[2 * k + 1] + tree[2 * k + 2];
        //######################################
    }
    T query(int a, int b, int k, int l, int r) {
        if (r <= a || b <= l)
            //######################################
            return 0;
            //######################################
        if (a <= l && b >= r) return tree[k];
        else {
            //遍历的同时,进行持久化,将懒惰标记落实
            maintain(l, r, k);
            int v_l = query(a, b, k * 2 + 1, l, (l + r) / 2);
            int v_r = query(a, b, k * 2 + 2, (l + r) / 2, r);
            //######################################
            return v_l + v_r;
            //######################################
        }
    }
    void build(int k){
        if(k>=n-1){
            //######################################
            tree[k]=k-n+1>=arr->size()?0:(*arr)[k-n+1];
            //这里需要进行节点赋值,还需要注意空节点的处理
            //######################################
            return;
        }
        build(2*k+1);
        build(2*k+2);
        //######################################
        tree[k]=tree[2*k+1]+tree[2*k+2];
        //######################################
    }

public:
    SegTree_LazyRangeAdd<T> () = default;
    explicit SegTree_LazyRangeAdd<T>(vector<T>* arr):arr(arr){
        n = 1;
        //扩大到2的整数次幂方便操作,这样和直接使用4*arr->size()更节省空间,但是需要注意对于空节点的处理,在64行
        while (n < arr->size()) n *= 2;
        tree.resize(2 * n - 1);
        lazy.resize(2 * n - 1);
        build(0);
    }
    //单点修改
    void update(int k, T a) {
        k += n - 1;
        tree[k] = a;
        while (k > 0) {
            k = (k - 1) / 2;
            //######################################
            tree[k] = tree[2 * k + 1] + tree[2 * k + 2];
            //######################################
        }
    }
    T query(int a, int b) {
        return query(a, b, 0, 0, n);
    }
    void range_add(int a, int b, T val) {
        range_add(a, b, val, 0, 0, n);
    }
};