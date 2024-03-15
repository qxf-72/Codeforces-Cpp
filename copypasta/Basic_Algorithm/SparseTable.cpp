template<typename T>
class SparseTable
{
	using func_type = function<T(const T&, const T&)>;

	vector<vector<T>> ST;	// 稀疏表
	vector<int> log_;		// 预处理k值
	func_type op;			// 对元素的操作，默认为max()
	static T default_func(const T& t1, const T& t2)
	{
		return max(t1, t2);
	}
 public:
	SparseTable(const vector<T>& a, func_type _func = default_func)
	{
		op = _func;
		int len = a.size();
		int l1 = ceil(log2(len)) + 1;
		ST.assign(len, vector<T>(l1, 0));
		
		for (int i = 0; i < len; ++i)
			ST[i][0] = a[i];

		for (int j = 1; j < l1; ++j)
		{
			int pj = (1 << j) - 1;
			for (int i = 0; i + pj < len; ++i)
			{
				ST[i][j] = op(ST[i][j - 1], ST[i + (1 << (j - 1))][j - 1]);
			}
		}

		log_.assign(len + 1, 0);
		for (int i = 2; i <= len; ++i)
			log_[i] = log_[i / 2] + 1;

	}

	T query(int l, int r)
	{
		int k = log_[r - l + 1];
		return op(ST[l][k], ST[r - (1 << k) + 1][k]);
	}

};