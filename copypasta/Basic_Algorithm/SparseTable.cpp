template <typename T>
class SparseTable {
    using func_type = function<T(const T &, const T &)>;

    vector<vector<T>> St; // 稀疏表
    vector<int> Log;      // 预处理k值
    func_type op;         // 对元素的操作,默认为max()

    static T default_func(const T &t1, const T &t2) {
        return max(t1, t2);
    }

public:
    SparseTable(const vector<T> &a, func_type _func = default_func) {
        op = _func;
        int len = a.size();
        int len2 = (int)log2(len) + 1;
        St.assign(len, vector<T>(len2, 0));

        for (int i = 0; i < len; ++i)
            St[i][0] = a[i];

        for (int j = 1; j < len2; ++j) {
            int jlen = (1 << j) - 1;
            for (int i = 0; i + jlen < len; ++i) {
                St[i][j] = op(St[i][j - 1], St[i + (1 << (j - 1))][j - 1]);
            }
        }

        Log.assign(len + 1, 0);
        for (int i = 2; i <= len; ++i)
            Log[i] = Log[i / 2] + 1;
    }

    T query(int l, int r) {
        int k = Log[r - l + 1];
        return op(St[l][k], St[r - (1 << k) + 1][k]);
    }
};