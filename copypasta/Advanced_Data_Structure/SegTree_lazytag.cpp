const int N = 1e5 + 10;

int a[N];	// 默认下标从0开始
/**
 * @brief 带延迟标记线段树, 以维护区间和为例
 * @tparam T
 */
template<typename T>
class SegTree
{
	T n;
	T data[4 * N]{}, lazy[4 * N]{};

	void build(T k, T l, T r)
	{
		if (l == r)
		{
			data[k] = a[l];
			return;
		}
		int mid = (l + r) / 2;
		build(2 * k + 1, l, mid);
		build(2 * k + 2, mid + 1, r);
		// 从下往上合并信息
		data[k] = data[2 * k + 1] + data[2 * k + 2];
	}
	void spread(T k, T l, T r)
	{
		if (lazy[k] != 0)
		{
			T mid = (l + r) / 2;
			data[2 * k + 1] += lazy[k] * (mid - l + 1);
			data[2 * k + 2] += lazy[k] * (r - mid);
			lazy[2 * k + 1] += lazy[k];
			lazy[2 * k + 2] += lazy[k];
			lazy[k] = 0;
		}
	}
	void update(T k, T l, T r, T ql, T qr, T e)
	{
		if (l >= ql && r <= qr)
		{
			data[k] += (long long)e * (r - l + 1);
			lazy[k] += e;
			return;
		}
		// 往下更新之前必须先向下传递延迟标记
		spread(k, l, r);

		T mid = (l + r) / 2;
		if (ql <= mid)
			update(2 * k + 1, l, mid, ql, qr, e);
		if (qr > mid)
			update(2 * k + 2, mid + 1, r, ql, qr, e);
		// 从下往上合并信息
		data[k] = data[2 * k + 1] + data[2 * k + 2];
	}
	T query(T k, T l, T r, T ql, T qr)
	{
		if (l >= ql && r <= qr)
			return data[k];
		spread(k, l, r);
		int mid = (l + r) / 2;
		T ret = 0;
		// 从下往上合并信息
		if (ql <= mid)
			ret += query(2 * k + 1, l, mid, ql, qr);
		if (qr > mid)
			ret += query(2 * k + 2, mid + 1, r, ql, qr);

		return ret;
	}

 public:
	explicit SegTree(int n)
	{
		this->n = n;
		build(0, 0, n - 1);
	}

	/**
	 * @brief 区间[l,r]都加上e
	 */
	void update(T l, T r, T e)
	{
		update(0, 0, n - 1, l, r, e);
	}
	T query(T l, T r)
	{
		return query(0, 0, n - 1, l, r);
	}
};