class BigIntZip
{
	vector<int> data;
	const long long M = 1e9;
 public:
	BigIntZip(long long n)
	{
		while (n)
		{
			data.push_back(n % M);
			n /= M;
		}
	}
	BigIntZip& operator*=(int c)
	{
		long long carry = 0;
		for (auto& it : data)
		{
			it = carry + it * (long long)c % M;
			carry = (carry + it * (long long)c) / M;
		}
		while (carry > 0)
		{
			data.push_back(carry % M);
			carry /= M;
		}
		return *this;
	}
	friend std::ostream& operator<<(std::ostream& os, const BigIntZip& bigIntZip)
	{
		os << bigIntZip.data.back();
		for (int i = bigIntZip.data.size() - 2; i >= 0; --i)
		{
			os << setw(9) << setfill('0') << bigIntZip.data[i];
		}
		return os;
	}
};