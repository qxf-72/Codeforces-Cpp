#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>

template <typename T>
class SparseTable {
    using func_type = std::function<T(const T &, const T &)>;

private:
    int n;
    std::vector<std::vector<T>>
        st; // st[k][i] 表示从 i 开始，长度为 2^k 的区间结果
    std::vector<int> Log;
    func_type op;

    static T default_func(const T &a, const T &b)
    {
        return std::max(a, b);
    }

public:
    explicit SparseTable(const std::vector<T> &a, func_type func = default_func) :
        n((int)a.size()), op(func)
    {
        assert(n > 0);

        Log.assign(n + 1, 0);
        for (int i = 2; i <= n; ++i) {
            Log[i] = Log[i / 2] + 1;
        }

        int K = Log[n] + 1;
        st.assign(K, std::vector<T>(n));

        for (int i = 0; i < n; ++i) {
            st[0][i] = a[i];
        }

        for (int k = 1; k < K; ++k) {
            for (int i = 0; i + (1 << k) <= n; ++i) {
                st[k][i] = op(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
            }
        }
    }

    // 查询闭区间 [l, r]
    T query(int l, int r) const
    {
        assert(0 <= l && l <= r && r < n);

        int k = Log[r - l + 1];
        return op(st[k][l], st[k][r - (1 << k) + 1]);
    }
};