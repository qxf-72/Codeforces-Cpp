#include <iostream>
#include <string>

using namespace std;
using LL = long long;

struct BigInt
{
	int data[300]{};
	int len{};
	BigInt() = default;
	BigInt(const string& s)
	{
		for (int i = s.length() - 1; i >= 0 && s[i] != '-'; --i)
		{
			data[len++] = s[i] - '0';
		}
	}

	bool operator<(const BigInt& a) const
	{
		if (len != a.len)
			return len < a.len;
		for (int i = len - 1; i >= 0; --i)
		{
			if (data[i] != a.data[i])
				return data[i] < a.data[i];
		}
		return false;
	}

	BigInt& operator<<=(int k)
	{
		len += k;
		for (int i = len - 1; i >= k; --i)
			data[i] = data[i - k];
		for (int i = 0; i < k; ++i)
			data[i] = 0;
		return *this;
	}
	BigInt operator*(int a) const
	{
		BigInt ret = *this;
		for (int i = 0; i < ret.len; ++i)
			ret.data[i] *= a;
		int carry = 0;
		for (int i = 0; i < ret.len; ++i)
		{
			ret.data[i] += carry;
			carry = ret.data[i] / 10;
			ret.data[i] %= 10;
		}
		while (carry)
		{
			ret.data[ret.len++] = carry % 10;
			carry /= 10;
		}
		return ret;
	}
	BigInt operator+(const BigInt& a) const
	{
		BigInt c;
		int carry = 0;
		int i;
		for (i = 0; i < len && i < a.len; ++i)
		{
			carry += data[i] + a.data[i];
			c.data[c.len++] = carry % 10;
			carry /= 10;
		}
		for (; i < len; ++i)
		{
			carry += data[i];
			c.data[c.len++] = carry % 10;
			carry /= 10;
		}
		for (; i < a.len; ++i)
		{
			carry += a.data[i];
			c.data[c.len++] = carry % 10;
			carry /= 10;
		}
		for (; carry; carry /= 10)
		{
			c.data[c.len++] = carry % 10;
		}
		return c;
	}
	BigInt& operator+=(const BigInt& a)
	{
		*this = *this + a;
		return *this;
	}
	BigInt operator*(const BigInt& a) const
	{
		BigInt ans;
		for (int i = 0; i < a.len; ++i)
		{
			ans += ((*this * a.data[i]) <<= i);
		}
		return ans;
	}
	BigInt operator-(const BigInt& a) const
	{
		if (*this < a)
			return a - *this;
		BigInt ret;
		int carry = 0;
		for (int i = 0; i < len; ++i)
		{
			carry = data[i] - carry;
			if (i < a.len)
				carry -= a.data[i];
			ret.data[ret.len++] = (carry + 10) % 10;
			if (carry < 0)
				carry = 1;
			else
				carry = 0;
		}
		while (ret.len > 1 && ret.data[ret.len - 1] == 0)
			--ret.len;
		return ret;
	}

};