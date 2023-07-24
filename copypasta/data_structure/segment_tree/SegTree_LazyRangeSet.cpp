//该模板以维护区间和为例，当用于维护其他信息时，已将需要修改的地方标出
template<typename T>
class SegTree_LazyRangeSet {
private:
    vector<T> *arr;
    vector<T> tree;
    vector<T> lazy;
    int n=1;
    void maintain(int l, int r, int k) {
        int mid = (l + r) / 2;
        if (k < n - 1 && lazy[k]) {
            //######################################
            lazy[2 * k + 1] = lazy[k];
            lazy[2 * k + 2] = lazy[k];
            tree[2 * k + 1] = lazy[k] * (mid - l);
            tree[2 * k + 2] = lazy[k] * (r - mid);
            lazy[k] = 0;
            //######################################
        }
    }

    void range_set(int a, int b, T val, int k, int l, int r) {
        if (r <= a || b <= l) return;
        if (a <= l && b >= r) {
            lazy[k] = val;
            //######################################
            tree[k] = (r - l) * val;
            //######################################
            return;
        }
        int mid = (l + r) / 2;
        maintain(l, r, k);
        range_set(a, b, val, 2 * k + 1, l, mid);
        range_set(a, b, val, 2 * k + 2, mid, r);
        //######################################
        tree[k] = tree[2 * k + 1] + tree[2 * k + 2];
        //######################################
    }

    T query(int a, int b, int k, int l, int r) {
        if (r <= a || b <= l) {
            //######################################
            return 0;
            //######################################
        }   
        if (a <= l && b >= r) return tree[k];
        else {
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
    SegTree_LazyRangeSet<T> () = default;
    explicit SegTree_LazyRangeSet<T>(vector<T>* arr):arr(arr){
            n = 1;
            while (n < arr->size()) n *= 2;
            tree.resize(2 * n - 1);
            lazy.resize(2 * n - 1);
            build(0);
            arr=nullptr;
    }

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

    void range_set(int a,int b ,T val){
        range_set(a,b,val,0,0,n);
    }
};