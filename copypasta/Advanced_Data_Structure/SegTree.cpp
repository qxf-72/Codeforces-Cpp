const int N = 1e5 + 10;

int a[N];
template<typename T>
class SegTree
{
	T n;
	T data[4 * N]{};

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
	void update(T k, T l, T r, T x, T e)
	{
		if (l == r)
		{
			data[k] += e;
			return;
		}
		T mid = (l + r) >> 1;
		if (x <= mid)
			update(2 * k + 1, l, mid, x, e);
		else
			update(2 * k + 2, mid + 1, r, x, e);
		data[k] = data[2 * k + 1] + data[2 * k + 2];
	}
	T query(T k, T l, T r, T ql, T qr)
	{
		if (l >= ql && r <= qr)
		{
			return data[k];
		}
		T mid = (l + r) >> 1;
		T res = 0;    // 默认为一个不影响答案的数
		if (ql <= mid)
			res += query(2 * k + 1, l, mid, ql, qr);
		if (qr > mid)
			res += query(2 * k + 2, mid + 1, r, ql, qr);
		return res;
	}

 public:
	explicit SegTree(int n)
	{
		this->n = n;
		build(0, 0, n - 1);
	}

	/**
	 * @brief a[x]加上e
	 */
	void update(T x, T e)
	{
		update(0, 0, n - 1, x, e);
	}
	T query(T l, T r)
	{
		return query(0, 0, n - 1, l, r);
	}
};