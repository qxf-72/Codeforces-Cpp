/**
 * @brief 以维护区间和为例
 * @tparam T
 */
template<typename T>
class BIT
{
	int n;
	vector<T> bit;	// 也可以替换为一个数组
	int lowbit(int x)
	{
		return x & -x;
	}

 public:
	BIT(int n)
	{
		this->n = n;
		bit.assign(n + 1, 0);
	}
	explicit BIT(vector<T>& arr)
	{
		this->n = arr.size();    // 这里默认arr数组下标1开始
		bit.resize(n + 1);
		// O(n)建树
		for (int i = 1; i <= n; ++i)
		{
			bit[i] += arr[i];
			int j = i + lowbit(i);
			if (j <= n)
				bit[j] += bit[i];
		}
	}

	/**
	 * @brief 前缀信息查询
	 */
	T ask(int x)
	{
		T res = 0;
		for (; x; x -= lowbit(x))
			res += bit[x];
		return res;
	}

	/**
	 * @brief 单点修改
	 */
	void add(int x, int y)
	{
		for (; x <= n; x += lowbit(x))
			bit[x] += y;
	}
};
