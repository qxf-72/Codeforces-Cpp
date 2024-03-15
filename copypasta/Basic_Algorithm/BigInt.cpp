struct BigInt
{
	vector<int> data;
	explicit BigInt(int n)
	{
		for (; n;)
		{
			data.push_back(n % 10);
			n /= 10;
		}
	}
	explicit BigInt(vector<int> data) : data(std::move(data))
	{
	}
	bool operator<(const BigInt& other) const
	{
		if (data.size() != other.data.size())
			return data.size() < other.data.size();
		for (int i = data.size() - 1; i >= 0; --i)
		{
			if (data[i] < other.data[i])
				return true;
			else if (data[i] > other.data[i])
				return false;
		}
		return false;
	}
	BigInt operator*(const int num) const
	{
		int carry = 0;
		vector<int> c;
		int i = 0;
		for (; carry || i < data.size();)
		{
			if (i < data.size()) carry += data[i] * num;
			c.push_back(carry % 10);
			carry /= 10;
			++i;
		}
		return BigInt(c);
	}
	BigInt operator/(const int num) const
	{
		vector<int> c;
		int r = 0;
		for (int i = data.size() - 1; i >= 0; --i)
		{
			r = r * 10 + data[i];
			c.push_back(r / num);
			r %= num;
		}
		reverse(c.begin(), c.end());
		while (c.size() > 1 && c.back() == 0)
			c.pop_back();
		return BigInt(c);
	}
};