class StringHash
{
	const int P;
	vector<unsigned long long> p, f;
 public:
	explicit StringHash(const string& s, int P = 131) : P(P)
	{
		int len = s.length();
		// s下标从0开始，p,f下标从1开始
		p.assign(len + 1, 1);
		f.assign(len + 1, 0);
		for (int i = 1; i <= len; ++i)
		{
			p[i] = p[i - 1] * P;
			f[i] = f[i - 1] * P + (s[i - 1] - 'a' + 1);        //如果是存在大写字母，需要改为‘A’
		}
	}
	// 默认查询下标从1开始
	unsigned long long query(int l, int r)
	{
		return f[r] - f[l - 1] * p[r - l + 1];
	}
};