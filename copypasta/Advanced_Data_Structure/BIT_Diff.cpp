/**
 * @brief 以维护区间和为例,维护其他信息仅需要进行少量修改
 */
template<typename T>
class BIT_Diff
{
	vector<T> data_a; // 维护 差分数组a[i] 的前缀和,可以替换为一个数组
	vector<T> data_b; // 维护 i*a[i] 的前缀和,可以替换为一个数组
	T n; // 维护1到n的信息	

	inline T lowbit(T i)
	{
		return i & -i;
	}

	void add(vector<T>& data, T i, T x)
	{
		for (; i <= n; i += lowbit(i))
			data[i] += x;
	}

	T sum(vector<T>& data, T i)
	{
		T res = 0;
		for (; i; i -= lowbit(i))
			res += data[i];
		return res;
	}

 public:
	BIT_Diff() = default;
	BIT_Diff(T n)
	{
		this->n = n;
		data_a.resize(n + 1);
		data_b.resize(n + 1);
	}
	BIT_Diff(vector<T>& arr)
	{
		// 默认数组下标从 1 开始
		this->n = arr.size() - 1;
		data_a.resize(n + 1);
		data_b.resize(n + 1);
		// O(n)建树
		for (int i = 1; i <= n; ++i)
		{
			data_a[i] += arr[i] - arr[i - 1];
			data_b[i] += (arr[i] - arr[i - 1]) * i;

			int j = i + lowbit(i);
			if (j <= n)
			{
				data_a[j] += data_a[i];
				data_b[j] += data_b[i];
			}
		}
	}
	/**
	 * @brief 区间修改
	 */
	void range_add(T l, T r, T x)
	{
		add(data_a, l, x);
		add(data_a, r + 1, -x);
		add(data_b, l, l * x);
		add(data_b, r + 1, -(r + 1) * x);
	}
	/**
	 * @brief 区间查询
	 */
	T query(T l, T r)
	{
		return (r + 1) * sum(data_a, r) - sum(data_b, r) - l * sum(data_a, l - 1) + sum(data_b, l - 1);
	}
};