#include <functional>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <numeric>

template <typename T>
class SparseTable {
    using func_type = std::function<T(const T &, const T &)>;

private:
    int n;
    std::vector<std::vector<T>> st; // st[k][i] 表示从 i 开始，长度为 2^k 的区间结果
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
        // l+(1<<k)-1=r  l=r-(1<<k)+1
        return op(st[k][l], st[k][r - (1 << k) + 1]);
    }
};

// test
int func_min(const int &a, const int &b)
{
    return std::min(a, b);
}
int main()
{
    std::vector<int> a{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    int (*func_min_p)(const int &, const int &) = func_min;
    auto func_gcd = [](const int &a, const int &b) -> int {
        return std::gcd(a, b);
    };
    using namespace std::placeholders;
    auto func_gcd_b = std::bind(std::gcd<int, int>, _1, _2);

    SparseTable<int> st_max(a);
    SparseTable<int> st_min(a, func_min);
    SparseTable<int> st_min_p(a, func_min_p);
    SparseTable<int> st_gcd(a, func_gcd);
    SparseTable<int> st_gcd_b(a, func_gcd_b);

    std::cout << st_max.query(0, 9) << std::endl;
    std::cout << st_min.query(0, 9) << std::endl;
    std::cout << st_min_p.query(0, 9) << std::endl;
    std::cout << st_gcd.query(0, 9) << std::endl;
    std::cout << st_gcd_b.query(0, 9) << std::endl;

    return 0;
}