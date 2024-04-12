#include <algorithm>
#include <vector>
#include <iostream>
#include <numeric>
using namespace std;

struct DSU
{
	vector<size_t> fa, size;

	explicit DSU(size_t size_) : fa(size_), size(size_, 1)
	{
		iota(fa.begin(), fa.end(), 0);
	}
	size_t find(size_t x)
	{
		if (x == fa[x])
			return x;
		return fa[x] = find(fa[x]);
	}
	void unite(size_t x, size_t y)
	{
		x = find(x), y = find(y);
		if (x == y) return;
		if (size[x] < size[y]) swap(x, y);
		fa[y] = x;
		size[x] += size[y];
	}
};

int main()
{
	return 0;
}
